# insdate2 — Rust 移植プロジェクト（引き継ぎノート）

> このファイルは macOS 側の Claude Code セッションから引き継ぎのために書かれています。
> Windows(Parallels/ARM) 側でこの `insdate2` フォルダを開いて作業を再開する際、
> まずこれを読んでから着手してください。ユーザーへの応答は日本語で行うこと。
> 移植に必要な元ファイルは全て `reference/` 内にコピー済み（親フォルダに依存しない）。

---

## 0. これは何か / ゴール

- `insdate` は **秀丸エディター用のマクロ DLL**。カーソル位置に日付文字列を挿入する。
- オリジナルは **C++Builder（VCL 依存）** 製。ソースは `reference/File1.cpp`、エクスポート定義は `reference/insdate.def`、呼び出し側マクロは `reference/mac/InsertDateList.mac`。
- **今回のゴール: これを Rust で「ランタイム完全非依存の単体ネイティブ DLL」として移築する。**
- 出力 DLL 名は `insdate.dll`（既存マクロが `loaddll("insdate.dll")` で読むため名前は変えない）。プロジェクト置き場は新規フォルダ `insdate2`。

## 1. 確定済みの方針（macOS 側で合意済み）

| 項目 | 決定 |
|---|---|
| 言語 | **Rust** （ユーザーは Rust 初挑戦。学習も兼ねる。丁寧に説明しながら進めること） |
| 出力形態 | **単体ネイティブ DLL・ランタイム依存ゼロ**（`crate-type = ["cdylib"]`） |
| ビット数 | **32bit (x86)** = ターゲット `i686-pc-windows-msvc`（※32bit 秀丸互換のため。最終確認は下記「要確認」） |
| 呼び出し規約 | **cdecl**（元 `.def` が leading-underscore = cdecl のため） |
| エクスポート名 | 元 DLL と**完全互換**（下記8関数名をそのまま）。→ 既存 `.mac` を1文字も変えずに DLL 差し替え可能にする |
| 文字列 | **ANSI（char\*）**。日本語 Windows は CP932(Shift-JIS)。戻り値は固定バッファへ書く（元コード同様） |

**なぜ Rust で 32bit 単体なのか（背景）:** C# は 32bit の非依存単体 DLL を作れない（Native AOT は x86 非対応、DllExport は CLR 依存）。「単体 DLL + 32bit + C++回避」を全部満たす現実解が Rust。

## 2. 開発環境（Windows 11 ARM / Parallels）のセットアップ

ARM ホスト上で **x86(32bit) をターゲット**にクロスビルドする形になる。

1. **Rust** を rustup で導入（https://rustup.rs の `rustup-init` を実行）
2. **Visual Studio Build Tools 2022** を導入。「C++ によるデスクトップ開発」ワークロード＋**x86 用の MSVC ビルドツールと Windows SDK** を必ず含める（x86 の `link.exe`・ライブラリが要る）
3. 32bit ターゲットを追加:
   ```
   rustup target add i686-pc-windows-msvc
   ```
4. ビルド:
   ```
   cargo build --release --target i686-pc-windows-msvc
   ```
   出力 → `target/i686-pc-windows-msvc/release/insdate.dll`
5. 確認: `dumpbin /exports insdate.dll` で下記8つの**装飾なしの名前**が並ぶことを確認（VS 開発者コマンドプロンプトで実行）

## 3. 実装する8つのエクスポート関数（`reference/File1.cpp` が仕様の正）

全て cdecl。`format`/`filepath` は ANSI `char*`、他は `int`、戻り値は `char*`（固定バッファ）。

```
GetDateString(char* format, int Year,int Month,int Day,int Hour,int Minute,int Second)
GetDateStringEn(char* format, ...同上...)
GetCreateDateString(char* filepath, char* format, int Year,...,int Second)
GetCreateDateStringEn(char* filepath, char* format, ...)
GetLastWriteDateString(char* filepath, char* format, ...)
GetLastWriteDateStringEn(char* filepath, char* format, ...)
GetAccessDateString(char* filepath, char* format, ...)
GetAccessDateStringEn(char* filepath, char* format, ...)
```

- `～En` は英語(U.S.)ロケール表記、無印は既定ロケール（日本語 Windows なら日本語）。
- `Create/LastWrite/Access` はそれぞれファイルの 作成/更新/アクセス 日時を基点にする。無印の `GetDateString` は現在日時が基点。

### エクスポート名を正確に出す方法（重要な落とし穴）
Rust の i686-msvc では cdecl シンボルに `_` が付いたり装飾されることがある。**各関数に `#[export_name = "GetDateString"]` を付けて**、エクスポートテーブルに載る名前を明示的に固定する。`#[no_mangle]` だけだと `_GetDateString` になり得るので注意。最後は必ず `dumpbin /exports` で検証。

## 4. 挙動仕様（`reference/File1.cpp` の `CreateDateTimeString` を移植）

1. `filepath` が渡され、かつファイルが存在 → そのファイルのタイムスタンプを基点日時にする（関数種別で作成/更新/アクセスを選択）。タイムスタンプが 0 なら現在日時にフォールバック。`filepath` 無し/不在なら現在日時。
2. **年月日時分秒の各引数は「絶対値ではなく増減（delta）」**。基点日時に対して加算する。例: `.mac` の「明日」は `Day=+1`、「昨日」は `Day=-1`。
   - 適用順は元コード通り: 先に Hour→Minute→Second、次に Year→Month→Day を加算。
   - 未指定引数は 0 扱い（元コードは `x == NULL ? 0 : x`）。
3. ロケール: 無印=既定ロケール、`～En`=英語(U.S.)。元コードは `TFormatSettings`＋`FormatDateTime` を使用。
4. **ampm 特例（日本語ロケール時のみ）**: `format` に `"ampm"` を含み、かつ `Hour==12` または `Hour==0` の場合、書式内の `"hh"→"00"`、`"h"→"0"` に置換してから整形（12時間制の「12時→0時」対策）。元コードの `strchg` 参照。

## 5. 最大の難所 — 書式文字列は「Delphi の FormatDateTime 形式」

`.mac` が渡す書式（例: `"yyyy/mm/dd"`, `"yyyy/mm/dd(ddd)"`, 先頭に Shift-JIS の元号/リテラル付き）は **Delphi 形式**であり、.NET でも strftime でも chrono でもない。Rust に既製の Delphi フォーマッタは無いので**自前で最小実装**する。

Delphi トークン（今回必要な範囲＋注意点）:
- `yyyy`=4桁年 / `yy`=2桁年
- `mm`=2桁月 / `m`=月 … **注意: Delphi では `hh` の直後の `mm` は「分」になる文脈規則がある**。`nn`=分（明示）, `ss`=秒。今回の既知書式は月用途のみだが、時刻書式を足すときは要注意。
- `dd`=2桁日 / `d`=日 / `ddd`=曜日短縮名 / `dddd`=曜日長名
- `hh`/`h`=時, `ss`/`s`=秒, `ampm`/`am/pm`/`a/p`=午前午後
- **上記トークン以外の文字はすべてリテラルとしてそのまま出力**（先頭の `.` や Shift-JIS の元号文字列などはバイト列のまま通す。CP932 バイトを壊さないこと）

**推奨アプローチ:** 曜日名・月名などロケール依存部分は **Win32 API（`GetDateFormat`/`GetTimeFormat` を `windows` クレート経由）** で出すと、元の VCL 挙動（日本語曜日「月火水…」等）を忠実に再現できる。全 Delphi 仕様を再現しようとせず、**実際に使われるトークンだけ**を対象にした小さな変換で十分。新しい書式が追加されたらトークン表を拡張する方針を残すこと。

## 6. ファイルタイムスタンプ取得

元コードは `CreateFileW` + `GetFileTime` + `FileTimeToLocalFileTime` + `FileTimeToSystemTime`。**Rust でも Win32 API（`windows` クレート）で同じ手順**を踏むのが最も忠実（`std::fs` の created/accessed は環境差があるため）。ローカル時刻へ変換する点も元コード通り。

## 7. 文字列の戻し方・エンコード

- 戻り値は **thread-local な固定バッファ**（元 `MAX_OUPUT_TEXT = 256`）へ書いて `*const c_char` を返す（秀丸マクロは固定アドレスを要求するため。元コードのコメント参照）。
- 最終文字列を **CP932(=CP_ACP) の ANSI に変換**して格納（`WideCharToMultiByte(CP_ACP, ...)`）。秀丸の `dllfuncstr` はマルチバイトを読む。
- Unicode 化（秀丸の `dllfuncstrw` / `～W` 関数）は今回は**やらない**。ドロップイン互換のため ANSI 維持。

## 8. Cargo.toml の骨子

```toml
[package]
name = "insdate"
version = "0.1.0"
edition = "2021"

[lib]
name = "insdate"          # → insdate.dll
crate-type = ["cdylib"]

[dependencies]
windows = { version = "*", features = [ /* Win32_Globalization, Win32_System_Time, Win32_Storage_FileSystem, Win32_Foundation など */ ] }

[profile.release]
opt-level = "z"
lto = true
panic = "abort"           # ランタイム依存とサイズを最小化。extern 関数は catch_unwind でパニックが FFI 境界を越えないようにする
```

## 9. テストの回し方（実機 = Windows の秀丸）

1. ビルドした `insdate.dll` を、マクロが `loaddll("insdate.dll")` で見つける場所に置く。
2. `reference/mac/InsertDateList.mac`（Shift-JIS 保存）を秀丸で実行 → メニューが出て日付が挿入されるか確認。
3. 確認項目: 通常の日付、`(ddd)` の曜日が日本語で出るか、作成日時/更新日時（ファイルのタイムスタンプ）、明日/昨日（±1日）、`～En` の英語表記、ampm を使う書式があれば午前/午後。

## 10. 要確認・未決事項（ユーザーに聞くこと）

1. **ビット数の最終確認**: 32bit(x86) 前提で進めているが、配布先に 32bit 秀丸ユーザーがいる想定でよいか。64bit でよいなら `x86_64-pc-windows-msvc` に切替（その場合は名前装飾の落とし穴が減る）。
2. **秀丸 dllfunc の引数渡し**: 秀丸は「マクロで渡した引数だけ」をスタックに積む。元コードは7 int を delta として扱い未指定を 0 前提にしている。cdecl で未指定引数が本当に 0 になるか、**実機で挙動確認**が必要（.mac は関数により渡す引数数が異なる）。
3. 書式文字列に含まれる Shift-JIS リテラル（元号など）の正確な中身。`reference/mac/InsertDateList.mac` を Shift-JIS で開いて確認する。

## 11. 参照ファイル一覧（`reference/` にコピー済み）

- `reference/File1.cpp` … **挙動の正**。8関数＋`CreateDateTimeString`＋`strchg`＋`GetFromFileTimestamp`＋`GetLocaleLangType`
- `reference/insdate.def` … 元のエクスポート名（`GetDateString=_GetDateString` …）
- `reference/mac/InsertDateList.mac` … 呼び出し側。実際の書式文字列と引数の渡し方の実例（**Shift-JIS 保存**）
- `reference/mac/*.mac` … 別バリエーションの呼び出し例（Archive 由来）

## 12. 進め方メモ

- ユーザーは Rust 初挑戦。まず環境構築（§2）→ 最小の1関数（`GetDateString` で現在日時を固定書式）で「秀丸に文字列が返る」ところまで通してから、書式変換・ファイルタイムスタンプ・ロケールへ拡張していくのが安全。
- 各ステップで何をしているか説明しながら進めること。

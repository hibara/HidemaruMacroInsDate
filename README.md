# 秀丸エディタ用・日付時刻挿入マクロ（insdate）

> Date and Time Insertion Macro for Hidemaru Editor

カーソル位置に、現在の日付・時刻を**好きな書式で**挿入する秀丸エディタ用マクロです。
本体は Rust で書かれた**ランタイム非依存の単体ネイティブ DLL**（`insdate32.dll` / `insdate64.dll`）で、
秀丸マクロ（`.mac`）から呼び出して使います。

- 対応: 32bit 版／64bit 版の秀丸（両方の DLL を同梱し、マクロ側で自動判別）
- 和暦（令和・平成…）、曜日名、英語表記、ファイルのタイムスタンプ、相対日時（明日・昨日など）に対応

---

## 特徴

- **単体ネイティブ DLL・ランタイム依存ゼロ** — .NET や VC++ ランタイムのインストール不要。DLL 単体で動作します。
- **32bit / 64bit 両対応** — `insdate32.dll` と `insdate64.dll` を同じフォルダに同居させ、マクロが秀丸のビット数を判定して自動で正しい方を読み込みます。
- **柔軟な書式指定** — `yyyy/mm/dd(ddd)`、`gge年m月d日` のような書式文字列で自由に整形。
- **和暦対応** — `gg`（元号名）/`e`・`ee`（元号年）で「令和8年」などを出力（Windows の和暦カレンダーに委譲）。
- **ファイルのタイムスタンプ** — 編集中ファイルの作成／更新／アクセス日時を取得して挿入。
- **相対日時** — 基準日時に対する年・月・日・時・分・秒の増減指定で「明日」「1週間後」「3時間後」なども生成。
- **英語表記版** — 各関数に `～En` 版があり、`Mon` / `July` などの英語ロケール表記に対応。

---

## インストール

### インストーラーを使う場合（推奨）

配布パッケージ（`HidemaruInsDateMacro***.exe`）を実行すると、秀丸のマクロフォルダへ
DLL とマクロが配置されます。

### 手動で導入する場合

1. `insdate32.dll` と `insdate64.dll` を、**両方とも**秀丸のマクロフォルダに置きます。
   （通常は `%APPDATA%\Hidemaruo\Hidemaru\Macro`）
2. 使いたい `.mac`（`InsertDate.mac` など）を、**同じフォルダ**に置きます。
3. 秀丸の「マクロ」→「マクロの実行」から `.mac` を実行します。

> DLL とマクロは必ず同じフォルダに置いてください。マクロは自分のあるフォルダから
> DLL を探します。

> インストーラー版では、ヘルプ（`Help.txt`）とライセンス（`LICENSE`）はマクロ置き場ではなく
> `%LOCALAPPDATA%\HiBARA_Software\HidemaruInsDateMacro\` に配置されます。
> （このパスはエクスプローラーのアドレス欄に貼り付けて開けます）

---

## 使い方（同梱マクロ）

| マクロ | 内容 |
|---|---|
| `InsertDate.mac` | 日付を1つ、その場に挿入する最小構成。書式を1行変えるだけで使える入門用。 |
| `InsertDateList.mac` | メニューから選んで挿入する実用版。 |
| `InsertDateListSample01.mac` | サンプル(1) 基本メニュー（和暦・英語・昨日/明日）。 |
| `InsertDateListSample02.mac` | サンプル(2) 書式カタログ（使える書式の一覧）。 |
| `InsertDateListSample03.mac` | サンプル(3) ファイルの作成／更新／アクセス日時。 |
| `InsertDateListSample04.mac` | サンプル(4) 応用（相対日時・午前午後・和暦）。 |

書式トークンや関数の詳しい仕様は、同梱の **[Help.txt](Help.txt)** を参照してください。

### 書式の例（`2026/07/06(月) 22:08:07` を基準にした場合）

| 書式 | 出力例 |
|---|---|
| `yyyy/mm/dd` | `2026/07/06` |
| `yyyy/mm/dd(ddd)` | `2026/07/06(月)` |
| `gge年m月d日(dddd)` | `令和8年7月6日(月曜日)` |
| `hh:nn:ss` | `22:08:07` |
| `ampm h時n分s秒` | `午後 0時8分7秒` |
| `yyyy/mm/dd(ddd)`（英語版） | `2026/07/06(Mon)` |

---

## ソースからのビルド

本 DLL は Rust 製で、`i686-pc-windows-msvc`（32bit）と `x86_64-pc-windows-msvc`（64bit）を
ターゲットにビルドします。Windows on ARM（Parallels 等）からのクロスビルドにも対応しています。

### 必要なもの

- [Rust](https://rustup.rs/)（rustup で導入）
- Visual Studio Build Tools 2022（「C++ によるデスクトップ開発」＋ **x86／x64 の MSVC ビルドツールと Windows SDK**）
- ビルドターゲットの追加:

  ```
  rustup target add i686-pc-windows-msvc
  rustup target add x86_64-pc-windows-msvc
  ```

### ビルド

同梱の PowerShell スクリプトを使います（vcvars の取り込み・エクスポート名の確認・成果物のコピーまで自動）。

```powershell
.\build.ps1 both     # 32bit と 64bit の両方をビルド
.\build.ps1 x86      # 32bit だけ
.\build.ps1 x64      # 64bit だけ
```

成果物は `dist\` に出力されます。

```
dist\insdate32.dll   # 32bit (i686)
dist\insdate64.dll   # 64bit (x86_64)
```

---

## リポジトリ構成

```
insdate2/
├─ src/lib.rs        … DLL 本体（Rust）
├─ Cargo.toml
├─ build.ps1         … 32/64bit ビルド → dist\
├─ mac/              … 秀丸マクロ（.mac）
├─ dist/             … ビルド成果物（insdate32.dll / insdate64.dll）
├─ reference/        … 移植元（C++Builder 版）の参照ファイル
├─ _installer/       … Inno Setup による配布パッケージ一式
├─ README.md         … このファイル
├─ Help.txt          … 同梱の利用者向けマニュアル
└─ LICENSE
```

エクスポートする DLL 関数（すべて cdecl・ANSI 文字列）:

```
GetDateString / GetDateStringEn
GetCreateDateString / GetCreateDateStringEn
GetLastWriteDateString / GetLastWriteDateStringEn
GetAccessDateString / GetAccessDateStringEn
```

---

## 変更履歴

[history.txt](history.txt) を参照してください。

---

## ライセンス

MIT License

Copyright (c) 2011-2026 Mitsuhiro Hibara / HiBARA Software, LLC

詳細は [LICENSE](LICENSE) を参照してください。

「<a href="https://hide.maruo.co.jp/software/hidemaru.html" target="_blank" rel="noopener noreferrer">秀丸エディタ</a>」
は有限会社サイトー企画の製品です。本ソフトウェアは HiBARA Software, LLC が
独自に配布するものであり、有限会社サイトー企画の公式製品ではありません。

---

## リンク

- 製品ページ: https://hibara.jp/software/hidemarumacroinsdate/
- HiBARA Software: https://hibara.jp
- リポジトリ: https://github.com/hibara/hidemarumacroinsdate

//! insdate.dll — 秀丸エディター用「日付挿入」マクロ DLL の Rust 移植。
//!
//! この段階（マイルストーン2）:
//!   エクスポート関数 `GetDateString` が、渡された **Delphi 形式の書式文字列** を
//!   自前パーサで解釈して「現在のローカル日時」を整形して返す。
//!   対応トークン: yyyy/yy, mm/m, dd/d, hh/h, nn/n, ss/s（数字）と
//!                 ddd/dddd（曜日名）, mmm/mmmm（月名）は Win32 GetDateFormat に委譲。
//!
//! まだ未実装（今後のステップ）:
//!   - 年月日時分秒の delta 加算（未指定=0、順序は 時→分→秒→年→月→日）
//!   - ファイルタイムスタンプ基点（GetCreate/LastWrite/AccessDateString）
//!   - 英語ロケール版（～En）
//!   - ampm 特例・和暦（gg/ee）
//!   - 最終文字列の CP932 変換（現状は数字と GetDateFormatA の CP932 出力のみなので不要）

use std::cell::UnsafeCell;
use std::os::raw::{c_char, c_void};

// --- Win32 API の直接宣言（外部クレート不使用）------------------------------
// 元 C++ が使っていた Win32 構造体／関数を、そのまま Rust 側で宣言して呼ぶ。
// #[repr(C)] は「C と同じメモリ配置にせよ」の指示。フィールドの順番・型は
// Windows の SYSTEMTIME 定義に厳密に合わせること（1 つでもずれると値が壊れる）。
#[repr(C)]
#[derive(Clone, Copy)]
#[allow(non_snake_case)] // Win32 の命名（大文字始まり）に合わせるため警告を止める
struct SYSTEMTIME {
    wYear: u16,
    wMonth: u16,
    wDayOfWeek: u16,
    wDay: u16,
    wHour: u16,
    wMinute: u16,
    wSecond: u16,
    wMilliseconds: u16,
}

// FILETIME は 1601-01-01 からの 100ns 単位を 64bit（下位/上位 32bit に分割）で持つ。
// 時・分・秒・日の増減は、これに変換して足し引きすると桁上げ・曜日再計算まで一括で済む。
#[repr(C)]
#[derive(Clone, Copy)]
#[allow(non_snake_case)]
struct FILETIME {
    dwLowDateTime: u32,
    dwHighDateTime: u32,
}

// kernel32.dll の関数を呼べるように宣言する。
// extern "system" は Win32 API の呼び出し規約（stdcall/x64 既定）を意味する。
#[link(name = "kernel32")]
extern "system" {
    fn GetLocalTime(lpSystemTime: *mut SYSTEMTIME);

    // SYSTEMTIME <-> FILETIME 変換（時分秒日の増減と曜日再計算に使う）。
    fn SystemTimeToFileTime(lpSystemTime: *const SYSTEMTIME, lpFileTime: *mut FILETIME) -> i32;
    fn FileTimeToSystemTime(lpFileTime: *const FILETIME, lpSystemTime: *mut SYSTEMTIME) -> i32;

    // ロケール依存の日付部品（曜日名・月名など）を得るために使う。
    // A サフィックス版なので、日本語 Windows では戻り値が CP932(ANSI) バイトになる。
    fn GetDateFormatA(
        Locale: u32,
        dwFlags: u32,
        lpDate: *const SYSTEMTIME,
        lpFormat: *const c_char, // Windows の「ピクチャ」書式（ASCII, NUL 終端）
        lpDateStr: *mut c_char,
        cchDate: i32,
    ) -> i32;

    // 時刻部（午前/午後の表記など）の取得に使う。ampm トークン用。
    fn GetTimeFormatA(
        Locale: u32,
        dwFlags: u32,
        lpTime: *const SYSTEMTIME,
        lpFormat: *const c_char,
        lpTimeStr: *mut c_char,
        cchTime: i32,
    ) -> i32;

    // ユーザー既定ロケールの LCID（ampm 特例の「日本語判定」に使う）。
    fn GetUserDefaultLCID() -> u32;

    // --- ファイルのタイムスタンプ取得（作成/更新/アクセス日時）---------------
    // filepath は ANSI(CP932) で渡ってくるので CreateFileA をそのまま使う。
    fn CreateFileA(
        lpFileName: *const c_char,
        dwDesiredAccess: u32,
        dwShareMode: u32,
        lpSecurityAttributes: *mut c_void,
        dwCreationDisposition: u32,
        dwFlagsAndAttributes: u32,
        hTemplateFile: HANDLE,
    ) -> HANDLE;
    fn GetFileTime(
        hFile: HANDLE,
        lpCreationTime: *mut FILETIME,
        lpLastAccessTime: *mut FILETIME,
        lpLastWriteTime: *mut FILETIME,
    ) -> i32;
    fn FileTimeToLocalFileTime(lpFileTime: *const FILETIME, lpLocalFileTime: *mut FILETIME) -> i32;
    fn CloseHandle(hObject: HANDLE) -> i32;

    // --- DLL ハイジャック対策 ---------------------------------------------------
    // プロセス全体の DLL 検索範囲を System32 のみに制限する。
    // 本 DLL 自身は LoadLibrary を呼ばないが、将来コードが増えたときの保険と、
    // 追加で読み込まれる可能性のある依存 DLL（Rust ランタイム等）を守るために
    // DllMain の PROCESS_ATTACH で 1 回だけ呼ぶ。
    // Windows 8+ で利用可能（Win7 も KB2533623 が入っていれば可）。
    fn SetDefaultDllDirectories(DirectoryFlags: u32) -> i32;
}

/// Win32 の HANDLE 型（不透明ポインタ）。
type HANDLE = *mut c_void;

/// ユーザーの既定ロケール（無印関数が使う）。元コードの LOCALE_USER_DEFAULT。
const LOCALE_USER_DEFAULT: u32 = 0x0400;
/// 英語(U.S.) 版（～En が使う）: MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))。
const LOCALE_EN_US: u32 = 0x0409;

// --- ファイルタイムスタンプ関連の定数 ---------------------------------------
const FILE_TS_CREATE: i32 = 1; // 作成日時
const FILE_TS_LASTWRITE: i32 = 2; // 更新日時
const FILE_TS_ACCESS: i32 = 3; // アクセス日時

const FILE_SHARE_ALL: u32 = 0x0000_0007; // READ|WRITE|DELETE（編集中ファイルでも開けるよう広めに）
const OPEN_EXISTING: u32 = 3;
const FILE_ATTRIBUTE_NORMAL: u32 = 0x0000_0080;

/// GetDateFormat に渡すと「代替カレンダー」（日本語ロケールでは和暦）で整形する。
const DATE_USE_ALT_CALENDAR: u32 = 0x0000_0004;
/// LANG_JAPANESE のプライマリ言語 ID（LCID の下位 10bit と比較）。
const LANG_JAPANESE: u32 = 0x11;

/// 出力バッファのサイズ（元 C コードの MAX_OUPUT_TEXT = 256 に合わせる）。
const MAX_OUTPUT_TEXT: usize = 256;

// --- 固定アドレスの出力バッファ ---------------------------------------------
// 秀丸マクロの dllfuncstr は「関数が返したポインタの指す固定メモリ」を読む。
// 元 C コードは関数内の `static char output[256]` を使っていた。その Rust 版。
//
// Rust では「static（グローバル変数）は基本イミュータブル」なので、中身を書き換える
// には UnsafeCell で包む必要がある。さらに static は Sync でなければ置けないので、
// 「秀丸からの呼び出しは単一スレッド」という前提のもと手動で Sync を約束する。
struct OutputBuffer(UnsafeCell<[u8; MAX_OUTPUT_TEXT]>);
unsafe impl Sync for OutputBuffer {}
static OUTPUT: OutputBuffer = OutputBuffer(UnsafeCell::new([0u8; MAX_OUTPUT_TEXT]));

/// バイト列を固定バッファへコピーし、NUL 終端して先頭ポインタを返す。
///
/// 返すのは常に同じアドレス（OUTPUT の中）なので、秀丸側の要求を満たす。
fn store_and_return(bytes: &[u8]) -> *const c_char {
    // SAFETY: 単一スレッド前提。バッファ長を超えないよう切り詰めてから書く。
    unsafe {
        let buf = &mut *OUTPUT.0.get();
        let n = bytes.len().min(MAX_OUTPUT_TEXT - 1); // 末尾 NUL 用に 1 バイト残す
        buf[..n].copy_from_slice(&bytes[..n]);
        buf[n] = 0; // C 文字列の終端
        buf.as_ptr() as *const c_char
    }
}

// --- 日時の増減（delta 加算）-----------------------------------------------
// 元コード CreateDateTimeString の IncHour/…/IncDay 相当。
// 適用順は元コード通り: 時→分→秒→年→月→日。未指定引数は 0（呼び出し側で 0 が渡る前提）。

/// SYSTEMTIME を FILETIME の 100ns 通し値（i64）へ。
fn st_to_ticks(st: &SYSTEMTIME) -> i64 {
    let mut ft = FILETIME { dwLowDateTime: 0, dwHighDateTime: 0 };
    unsafe { SystemTimeToFileTime(st, &mut ft) };
    ((ft.dwHighDateTime as i64) << 32) | (ft.dwLowDateTime as i64)
}

/// 100ns 通し値から SYSTEMTIME へ（wDayOfWeek もここで正しく再計算される）。
fn ticks_to_st(ticks: i64) -> SYSTEMTIME {
    let ft = FILETIME {
        dwLowDateTime: (ticks & 0xFFFF_FFFF) as u32,
        dwHighDateTime: ((ticks >> 32) & 0xFFFF_FFFF) as u32,
    };
    let mut st: SYSTEMTIME = unsafe { std::mem::zeroed() };
    unsafe { FileTimeToSystemTime(&ft, &mut st) };
    st
}

/// 秒数を加算（FILETIME 経由）。曜日も自動で正しくなる。日の加算にも使う。
fn add_seconds(st: &SYSTEMTIME, secs: i64) -> SYSTEMTIME {
    ticks_to_st(st_to_ticks(st) + secs * 10_000_000)
}

/// その年月の日数（うるう年対応）。
fn days_in_month(year: i32, month: i32) -> i32 {
    match month {
        1 | 3 | 5 | 7 | 8 | 10 | 12 => 31,
        4 | 6 | 9 | 11 => 30,
        2 => {
            if (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 {
                29
            } else {
                28
            }
        }
        _ => 30,
    }
}

/// 年を加算。2/29 → 非うるう年なら 2/28 に丸める。
fn add_years(st: &SYSTEMTIME, delta: i32) -> SYSTEMTIME {
    let ny = st.wYear as i32 + delta;
    let nd = (st.wDay as i32).min(days_in_month(ny, st.wMonth as i32));
    SYSTEMTIME {
        wYear: ny as u16,
        wDay: nd as u16,
        ..*st // wDayOfWeek はこの時点で古いが、最後の add_seconds で正常化される
    }
}

/// 月を加算。桁上げ（12月+1→翌年1月）と月末クランプ（1/31+1月→2/28）を処理。
fn add_months(st: &SYSTEMTIME, delta: i32) -> SYSTEMTIME {
    // 「西暦*12 + (月-1)」の 0 始まり通し月で計算すると桁上げが素直。
    let total = (st.wYear as i32) * 12 + (st.wMonth as i32 - 1) + delta;
    let ny = total.div_euclid(12);
    let nm = total.rem_euclid(12) + 1;
    let nd = (st.wDay as i32).min(days_in_month(ny, nm));
    SYSTEMTIME {
        wYear: ny as u16,
        wMonth: nm as u16,
        wDay: nd as u16,
        ..*st
    }
}

/// 全 delta を元コードの順序（時→分→秒→年→月→日）で適用する。
fn apply_deltas(
    base: &SYSTEMTIME,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> SYSTEMTIME {
    // 時・分・秒はまとめて秒数で加算（FILETIME 経由）。
    let mut cur = add_seconds(base, hour as i64 * 3600 + minute as i64 * 60 + second as i64);
    cur = add_years(&cur, year);
    cur = add_months(&cur, month);
    // 日は秒数加算で。day==0 でも FILETIME 往復で wDayOfWeek が正常化される。
    add_seconds(&cur, day as i64 * 86400)
}

// --- Delphi(C++Builder) 形式の書式文字列パーサ ------------------------------------------

/// 数値を最小桁数 `min_width` でゼロ埋めして追記する。
/// min_width=1 なら詰めない（例: 単独の `d`）。2/4 は 0 埋め。
fn push_num(out: &mut Vec<u8>, val: u32, min_width: usize) {
    let s = match min_width {
        4 => format!("{:04}", val),
        2 => format!("{:02}", val),
        _ => format!("{}", val),
    };
    out.extend_from_slice(s.as_bytes());
}

/// ロケール依存の日付部品を Win32 GetDateFormatA で取得する（フラグ指定版）。
/// `picture` は Windows のピクチャ書式（例: `b"ddd\0"` = 曜日短縮、`b"gg\0"` = 元号名）。
/// `flags` に DATE_USE_ALT_CALENDAR を渡すと和暦になる。失敗時は空。
fn locale_date_part_flags(lcid: u32, flags: u32, picture: &[u8], st: &SYSTEMTIME) -> Vec<u8> {
    let mut buf = [0u8; 128];
    let written = unsafe {
        GetDateFormatA(
            lcid,
            flags,
            st as *const SYSTEMTIME,
            picture.as_ptr() as *const c_char,
            buf.as_mut_ptr() as *mut c_char,
            buf.len() as i32,
        )
    };
    if written <= 0 {
        return Vec::new();
    }
    // GetDateFormat の戻り値は「終端 NUL を含む」書き込み文字数。本体は written-1 バイト。
    buf[..(written as usize - 1)].to_vec()
}

/// フラグ無し（グレゴリオ暦・通常ロケール）の日付部品。
fn locale_date_part(lcid: u32, picture: &[u8], st: &SYSTEMTIME) -> Vec<u8> {
    locale_date_part_flags(lcid, 0, picture, st)
}

/// ロケール依存の時刻部品（午前/午後など）を Win32 GetTimeFormatA で取得する。
fn locale_time_part(lcid: u32, picture: &[u8], st: &SYSTEMTIME) -> Vec<u8> {
    let mut buf = [0u8; 128];
    let written = unsafe {
        GetTimeFormatA(
            lcid,
            0,
            st as *const SYSTEMTIME,
            picture.as_ptr() as *const c_char,
            buf.as_mut_ptr() as *mut c_char,
            buf.len() as i32,
        )
    };
    if written <= 0 {
        return Vec::new();
    }
    buf[..(written as usize - 1)].to_vec()
}

// --- 小さな文字列ユーティリティ（ampm 判定・strchg 相当）--------------------

/// ASCII の大小無視で 1 バイト比較。
fn eq_ci(a: u8, b: u8) -> bool {
    a.to_ascii_lowercase() == b.to_ascii_lowercase()
}

/// `hay` が位置 0 で `needle`（ASCII, 大小無視）に一致するか。
fn starts_with_ci(hay: &[u8], needle: &[u8]) -> bool {
    hay.len() >= needle.len() && hay.iter().zip(needle).all(|(x, y)| eq_ci(*x, *y))
}

/// `hay` が `needle`（大小無視）を含むか。
fn contains_ci(hay: &[u8], needle: &[u8]) -> bool {
    !needle.is_empty()
        && hay.len() >= needle.len()
        && hay.windows(needle.len()).any(|w| starts_with_ci(w, needle))
}

/// `hay` が `needle`（バイト完全一致）を含むか。元コード strstr 相当。
fn contains(hay: &[u8], needle: &[u8]) -> bool {
    !needle.is_empty()
        && hay.len() >= needle.len()
        && hay.windows(needle.len()).any(|w| w == needle)
}

/// `buf` 中の `needle`（完全一致）を全て `repl` に置換する。元コード strchg 相当。
fn replace_all(buf: &mut Vec<u8>, needle: &[u8], repl: &[u8]) {
    if needle.is_empty() {
        return;
    }
    let mut i = 0;
    while i + needle.len() <= buf.len() {
        if &buf[i..i + needle.len()] == needle {
            buf.splice(i..i + needle.len(), repl.iter().copied());
            i += repl.len();
        } else {
            i += 1;
        }
    }
}

/// ユーザー既定ロケールが日本語かどうか（ampm 特例の判定に使う）。
fn is_japanese_locale() -> bool {
    (unsafe { GetUserDefaultLCID() } & 0x3ff) == LANG_JAPANESE
}

/// 1 つの書式トークン（同じ英字が `run` 個連続）を整形して追記する。
///
/// Delphi のルール（今回対応する範囲）:
///   y: yyyy→4桁年 / yy→2桁年
///   m: m→月 / mm→2桁月 / mmm→月短縮名 / mmmm→月フル名（名前はロケール委譲）
///   d: d→日 / dd→2桁日 / ddd→曜日短縮 / dddd→曜日フル（名前はロケール委譲）
///   h: h→時 / hh→2桁時（ampm 併用時は 12 時間制）   n: n/nn→分   s: s/ss→秒
///   g: gg→元号名（和暦, ロケール委譲）   e: e/ee→元号年（和暦, ロケール委譲）
///
/// `use_12h`: format に ampm 系トークンがあり、時刻を 12 時間制にすべきとき true。
fn emit_token(out: &mut Vec<u8>, letter: u8, run: usize, st: &SYSTEMTIME, lcid: u32, use_12h: bool) {
    match letter {
        b'y' => {
            if run >= 3 {
                push_num(out, st.wYear as u32, 4);
            } else {
                push_num(out, (st.wYear % 100) as u32, 2);
            }
        }
        b'm' => match run {
            1 => push_num(out, st.wMonth as u32, 1),
            2 => push_num(out, st.wMonth as u32, 2),
            3 => out.extend_from_slice(&locale_date_part(lcid, b"MMM\0", st)),
            _ => out.extend_from_slice(&locale_date_part(lcid, b"MMMM\0", st)),
        },
        b'd' => match run {
            1 => push_num(out, st.wDay as u32, 1),
            2 => push_num(out, st.wDay as u32, 2),
            3 => out.extend_from_slice(&locale_date_part(lcid, b"ddd\0", st)),
            _ => out.extend_from_slice(&locale_date_part(lcid, b"dddd\0", st)),
        },
        b'h' => {
            let mut hv = st.wHour as u32;
            if use_12h {
                hv %= 12;
                if hv == 0 {
                    hv = 12; // 12 時間制では 0/12 時は "12"
                }
            }
            push_num(out, hv, if run >= 2 { 2 } else { 1 });
        }
        b'n' => push_num(out, st.wMinute as u32, if run >= 2 { 2 } else { 1 }),
        b's' => push_num(out, st.wSecond as u32, if run >= 2 { 2 } else { 1 }),
        // 元号名（令和/平成…）。run に関わらずピクチャ "gg"。和暦カレンダーに委譲。
        b'g' => out.extend_from_slice(&locale_date_part_flags(lcid, DATE_USE_ALT_CALENDAR, b"gg\0", st)),
        // 元号年。ee→2桁 "yy" / e→詰めなし "y"。和暦カレンダーに委譲。
        b'e' => {
            let picture: &[u8] = if run >= 2 { b"yy\0" } else { b"y\0" };
            out.extend_from_slice(&locale_date_part_flags(lcid, DATE_USE_ALT_CALENDAR, picture, st));
        }
        _ => {}
    }
}

/// Delphi 形式の書式文字列 `fmt`（CP932 バイト列）を `st` の日時で整形する。
fn format_delphi(fmt: &[u8], st: &SYSTEMTIME, lcid: u32) -> Vec<u8> {
    // ampm 系トークンがあると Delphi では時刻が 12 時間制になる。
    let use_12h =
        contains_ci(fmt, b"ampm") || contains_ci(fmt, b"am/pm") || contains_ci(fmt, b"a/p");

    let mut out = Vec::with_capacity(fmt.len() + 16);
    let mut i = 0;
    while i < fmt.len() {
        let b = fmt[i];

        // --- Shift-JIS(CP932) の2バイト文字は丸ごとリテラルとして通す ---
        // SJIS の2バイト目には英字（'d' 等）と同じバイトが来ることがあり、
        // 1バイトずつ走査すると書式トークンと誤認するため、ここで先に食い切る。
        if (0x81..=0x9F).contains(&b) || (0xE0..=0xFC).contains(&b) {
            out.push(b);
            if i + 1 < fmt.len() {
                out.push(fmt[i + 1]);
                i += 2;
            } else {
                i += 1; // 壊れた末尾（1バイトだけ）はそのまま通す
            }
            continue;
        }

        // --- am/pm 系トークン（複数バイト・'/' を含むので run 判定の前に処理）---
        let rest = &fmt[i..];
        if starts_with_ci(rest, b"ampm") || starts_with_ci(rest, b"am/pm") {
            // ロケールの午前/午後（日本語なら「午前」「午後」）。
            out.extend_from_slice(&locale_time_part(lcid, b"tt\0", st));
            i += if starts_with_ci(rest, b"ampm") { 4 } else { 5 };
            continue;
        }
        if starts_with_ci(rest, b"a/p") {
            out.push(if st.wHour < 12 { b'a' } else { b'p' });
            i += 3;
            continue;
        }

        // --- 書式トークン（英字）は「同じ文字の連続数」で意味が決まる ---
        let lower = b.to_ascii_lowercase();
        if matches!(lower, b'y' | b'm' | b'd' | b'h' | b'n' | b's' | b'g' | b'e') {
            let mut run = 1;
            while i + run < fmt.len() && fmt[i + run].to_ascii_lowercase() == lower {
                run += 1;
            }
            emit_token(&mut out, lower, run, st, lcid, use_12h);
            i += run;
            continue;
        }

        // --- それ以外（区切りの '/' ':'、'(' ')'、'.' など）は 1 バイトのリテラル ---
        // 注: Delphi は本来 '/' を日付区切り、':' を時刻区切りに置換するが、
        //     今回の対象ロケール（日本語 / 英語US）ではどちらも '/' ':' なので素通しで一致する。
        out.push(b);
        i += 1;
    }
    out
}

/// 書式ポインタを安全にバイトスライスへ。NULL は空スライス扱い。
fn format_bytes<'a>(format: *const c_char) -> &'a [u8] {
    if format.is_null() {
        b""
    } else {
        // SAFETY: 秀丸から渡される NUL 終端の C 文字列。呼び出し中は有効。
        unsafe { std::ffi::CStr::from_ptr(format).to_bytes() }
    }
}

// --- 基点日時の取得 ---------------------------------------------------------

/// 現在のローカル日時。
fn now_st() -> SYSTEMTIME {
    let mut st: SYSTEMTIME = unsafe { std::mem::zeroed() };
    unsafe { GetLocalTime(&mut st) };
    st
}

/// filepath のタイムスタンプ（作成/更新/アクセスを foption で選択）をローカル日時で返す。
/// 開けない・タイムスタンプ 0・変換失敗のときは None（呼び出し側で現在日時にフォールバック）。
/// 元コード GetFromFileTimestamp 相当。
fn file_base_time(filepath: *const c_char, foption: i32) -> Option<SYSTEMTIME> {
    // 空/NULL は「ファイル指定なし」。
    if filepath.is_null() || unsafe { *filepath } == 0 {
        return None;
    }

    // access=0（メタデータのみ）, share=広め, OPEN_EXISTING。
    let handle = unsafe {
        CreateFileA(
            filepath,
            0,
            FILE_SHARE_ALL,
            core::ptr::null_mut(),
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            core::ptr::null_mut(),
        )
    };
    // INVALID_HANDLE_VALUE == (HANDLE)-1
    if handle as isize == -1 {
        return None;
    }

    let mut ft_create: FILETIME = unsafe { std::mem::zeroed() };
    let mut ft_access: FILETIME = unsafe { std::mem::zeroed() };
    let mut ft_write: FILETIME = unsafe { std::mem::zeroed() };
    let ok = unsafe { GetFileTime(handle, &mut ft_create, &mut ft_access, &mut ft_write) };
    unsafe { CloseHandle(handle) };
    if ok == 0 {
        return None;
    }

    let ft = match foption {
        FILE_TS_CREATE => ft_create,
        FILE_TS_ACCESS => ft_access,
        _ => ft_write, // FILE_TS_LASTWRITE（既定）
    };
    // タイムスタンプ 0（未設定）はフォールバックさせる。
    if ft.dwLowDateTime == 0 && ft.dwHighDateTime == 0 {
        return None;
    }

    // UTC → ローカルへ変換してから SYSTEMTIME に。
    let mut lft: FILETIME = unsafe { std::mem::zeroed() };
    unsafe { FileTimeToLocalFileTime(&ft, &mut lft) };
    let mut st: SYSTEMTIME = unsafe { std::mem::zeroed() };
    if unsafe { FileTimeToSystemTime(&lft, &mut st) } == 0 {
        return None;
    }
    Some(st)
}

// --- 全関数の共通処理 -------------------------------------------------------

/// 基点日時に delta を適用し、書式で整形して固定バッファへ格納・返す。
/// 8 つのエクスポート関数はすべてこれを呼ぶだけ。
fn make_output(
    format: *const c_char,
    base: &SYSTEMTIME,
    lcid: u32,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    let st = apply_deltas(base, year, month, day, hour, minute, second);

    // 書式のコピーを作る（ampm 特例で書き換える可能性があるため）。
    let mut fmt = format_bytes(format).to_vec();

    // --- ampm 特例（元コード CreateDateTimeString 準拠）------------------------
    // 日本語ロケール かつ format に "ampm" を含み かつ Hour 引数==0/12 のとき、
    // 書式内の "hh"→"00", "h"→"0" に置換する（12時間制の「12時」を「0時」表示にする細工）。
    // ※元コードのこのクセをそのまま再現（§4.4）。適用順は "hh"→"h" の順（元 strchg と同じ）。
    if is_japanese_locale() && contains(&fmt, b"ampm") && (hour == 12 || hour == 0) {
        replace_all(&mut fmt, b"hh", b"00");
        replace_all(&mut fmt, b"h", b"0");
    }

    let out = format_delphi(&fmt, &st, lcid);
    store_and_return(&out)
}

/// ファイルタイムスタンプ基点の共通処理（6 つの Get*DateString{,En} 用）。
fn file_date_string(
    filepath: *const c_char,
    format: *const c_char,
    lcid: u32,
    foption: i32,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    let base = file_base_time(filepath, foption).unwrap_or_else(now_st);
    make_output(format, &base, lcid, year, month, day, hour, minute, second)
}

// ===========================================================================
// エクスポート関数（8 つ）
//
// - すべて `#[export_name = "..."]` で公開名を固定（i686 cdecl の `_` 装飾対策, §3）。
// - `extern "C"` = 32bit では cdecl。元 .def と一致。
// - 年月日時分秒は基点日時への delta（増減）。未指定は 0 で渡る（§10.2 実機確認済み）。
// ===========================================================================

/// 現在日時・デフォルトロケール。
#[export_name = "GetDateString"]
pub extern "C" fn get_date_string(
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    make_output(
        format,
        &now_st(),
        LOCALE_USER_DEFAULT,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

/// 現在日時・英語(U.S.)表記。
#[export_name = "GetDateStringEn"]
pub extern "C" fn get_date_string_en(
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    make_output(
        format,
        &now_st(),
        LOCALE_EN_US,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

/// ファイル作成日時・デフォルトロケール。
#[export_name = "GetCreateDateString"]
pub extern "C" fn get_create_date_string(
    filepath: *const c_char,
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    file_date_string(
        filepath,
        format,
        LOCALE_USER_DEFAULT,
        FILE_TS_CREATE,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

/// ファイル作成日時・英語(U.S.)表記。
#[export_name = "GetCreateDateStringEn"]
pub extern "C" fn get_create_date_string_en(
    filepath: *const c_char,
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    file_date_string(
        filepath,
        format,
        LOCALE_EN_US,
        FILE_TS_CREATE,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

/// ファイル更新日時・デフォルトロケール。
#[export_name = "GetLastWriteDateString"]
pub extern "C" fn get_last_write_date_string(
    filepath: *const c_char,
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    file_date_string(
        filepath,
        format,
        LOCALE_USER_DEFAULT,
        FILE_TS_LASTWRITE,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

/// ファイル更新日時・英語(U.S.)表記。
#[export_name = "GetLastWriteDateStringEn"]
pub extern "C" fn get_last_write_date_string_en(
    filepath: *const c_char,
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    file_date_string(
        filepath,
        format,
        LOCALE_EN_US,
        FILE_TS_LASTWRITE,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

/// ファイルアクセス日時・デフォルトロケール。
#[export_name = "GetAccessDateString"]
pub extern "C" fn get_access_date_string(
    filepath: *const c_char,
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    file_date_string(
        filepath,
        format,
        LOCALE_USER_DEFAULT,
        FILE_TS_ACCESS,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

/// ファイルアクセス日時・英語(U.S.)表記。
#[export_name = "GetAccessDateStringEn"]
pub extern "C" fn get_access_date_string_en(
    filepath: *const c_char,
    format: *const c_char,
    year: i32,
    month: i32,
    day: i32,
    hour: i32,
    minute: i32,
    second: i32,
) -> *const c_char {
    file_date_string(
        filepath,
        format,
        LOCALE_EN_US,
        FILE_TS_ACCESS,
        year,
        month,
        day,
        hour,
        minute,
        second,
    )
}

// ============================================================================
// DllMain — DLL ハイジャック対策のため、ロード時に検索パスを System32 のみに制限
// ============================================================================
//
// SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32) を DLL_PROCESS_ATTACH で
// 1 回だけ呼ぶ。これにより、この DLL 以降（本 DLL 内・依存ランタイム経由問わず）の
// LoadLibrary 系呼び出しは System32 以外のディレクトリを検索対象にしない。
//
// - 本 DLL のコード自体は LoadLibrary を呼ばないので現状の直接的な効果はゼロだが、
//   将来コードが増えたときの安全網 & CRT 側で万が一動的ロードが発生した場合の保険。
// - 呼び出しが失敗しても DLL ロード自体は続行させる（return TRUE）。
//   古い Windows で API が無い等の場合でも DLL 自体は使えるようにするため。
// - Rust の cdylib は既定で内蔵の DllMain を持たないので、自分で定義する。
//   `extern "system"` で stdcall（x86）/ x64 既定呼び出し規約を指定する。

const DLL_PROCESS_ATTACH: u32 = 1;
const LOAD_LIBRARY_SEARCH_SYSTEM32: u32 = 0x0000_0800;

#[allow(non_snake_case)]
#[no_mangle]
pub extern "system" fn DllMain(
    _hinst: *mut c_void,
    fdwReason: u32,
    _lpvReserved: *mut c_void,
) -> i32 {
    if fdwReason == DLL_PROCESS_ATTACH {
        // 戻り値は無視。API 非対応等で失敗しても DLL ロードは続行させる。
        unsafe {
            let _ = SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32);
        }
    }
    1 // TRUE: ロード成功
}

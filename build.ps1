# insdate.dll ビルドヘルパー
#
# 使い方:
#   .\build.ps1 x64     … 64bit (x86_64) をビルド
#   .\build.ps1 x86     … 32bit (i686)  をビルド
#   .\build.ps1 both    … 両方（既定）
#
# やっていること:
#   1. ARM ホスト用の vcvars 環境（対象アーキ別）を取り込む
#   2. rc.exe で VERSIONINFO(.res) を作り、DLL に埋め込む準備をする
#   3. cargo build --release --target <対応ターゲット>
#   4. dumpbin /exports で公開エクスポート名を確認、ファイルバージョンを確認
#   5. 出来た insdate.dll を X:\insdate2\dist\ に、ビット数付きの名前へ
#      リネームしてコピー（x86 -> insdate32.dll / x64 -> insdate64.dll）
#
#   ※ 32bit / 64bit を場合分けして片方だけ入れるのではなく、両方を同じ
#     マクロフォルダに同居させ、どちらを使うかはマクロ側で判定する方針。
#     そのため dist\ 直下に insdate32.dll と insdate64.dll を並べて出す。
#
# ※ ビルド出力先(target)は .cargo/config.toml で C: に固定済み（X: は Parallels 共有フォルダで不可）。

param(
    [ValidateSet('x86', 'x64', 'both')]
    [string]$Arch = 'both'
)

$ErrorActionPreference = 'Stop'

# ▼ DLL に埋め込むバージョン（Windows 形式の 4 桁 a.b.c.d）。
#   リリース時はここ 1 か所を変更する。この値を rc.exe で VERSIONINFO にして
#   insdate32.dll / insdate64.dll に埋め込み、インストーラ(insdate2.iss)は
#   その DLL のファイルバージョンを読んで採用する。
$Version = '2.0.0.0'

# vcvarsall.bat の場所を vswhere で自動検出（BuildTools / Community / Professional / Enterprise 等どれでも可）。
# vswhere.exe は Visual Studio Installer と一緒に必ずこの固定パスに入る（Microsoft 保証パス）。
function Find-VcVarsAll {
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        # C++ ツール群を持つ最新の VS を探す
        $vsRoot = & $vswhere -latest -products '*' `
            -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
            -property installationPath 2>$null
        if ($vsRoot) {
            $cand = Join-Path $vsRoot 'VC\Auxiliary\Build\vcvarsall.bat'
            if (Test-Path $cand) { return $cand }
        }
    }
    # フォールバック: よくある固定パスを順に試す
    $fallbacks = @(
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
        "${env:ProgramFiles}\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat",
        "${env:ProgramFiles}\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat",
        "${env:ProgramFiles}\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat",
        "${env:ProgramFiles}\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"
    )
    foreach ($f in $fallbacks) { if (Test-Path $f) { return $f } }
    throw "vcvarsall.bat が見つかりません。Visual Studio 2022 の C++ ビルドツールをインストールしてください。"
}
$vc = Find-VcVarsAll
Write-Host "vcvarsall: $vc" -ForegroundColor DarkGray

$targetDir = "C:\Users\hibara\insdate2-build"
$projRoot = Split-Path -Parent $MyInvocation.MyCommand.Path

$dist = Join-Path $projRoot 'dist'

function Invoke-Build([string]$a, [string]$ver) {
    if ($a -eq 'x64') { $vcArch = 'arm64_amd64'; $rustTarget = 'x86_64-pc-windows-msvc'; $outName = 'insdate64.dll' }
    else              { $vcArch = 'arm64_x86';   $rustTarget = 'i686-pc-windows-msvc';   $outName = 'insdate32.dll' }

    Write-Host "=== Building $a ($rustTarget)  version $ver ===" -ForegroundColor Cyan

    # vcvars の環境変数をこのプロセスに取り込む
    cmd /c "`"$vc`" $vcArch >nul 2>&1 && set" | ForEach-Object {
        if ($_ -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($matches[1])" -Value $matches[2] }
    }
    $env:Path = "$(Join-Path $env:USERPROFILE '.cargo\bin');$env:Path"

    # --- DLL にバージョン情報(VERSIONINFO)を埋め込む -----------------------
    #  ビルドスクリプト(build.rs)は使わない。ARM ホストからのクロスビルドでは
    #  build.rs がホスト(aarch64)向けにリンクされ、ターゲット用 vcvars の
    #  link.exe(x86/x64)と衝突して壊れるため。代わりにここで rc.exe で .res を
    #  作り、リンカ引数(RUSTFLAGS)でターゲット DLL へ直接埋め込む。
    #  .res はアーキ非依存なので x86/x64 どちらにも同じものが使える。
    $nums = @($ver -split '\.') + @('0', '0', '0', '0')
    $comma = "$($nums[0]),$($nums[1]),$($nums[2]),$($nums[3])"
    $dot = "$($nums[0]).$($nums[1]).$($nums[2]).$($nums[3])"

    $resDir = Join-Path $targetDir 'versioninfo'
    New-Item -ItemType Directory -Force -Path $resDir | Out-Null
    $rcPath = Join-Path $resDir 'version.rc'
    # .res 名にバージョンを含める。こうすると $Version を変えたとき RUSTFLAGS が
    # 変わり、ソース未変更でも cargo が確実に再リンクして新しい版を埋め込む。
    $resPath = Join-Path $resDir "version-$dot.res"

    # .rc の中身を1行ずつ配列で組む（here-string は使わない）。
    $rcLines = @(
        '#include <winver.h>'
        'VS_VERSION_INFO VERSIONINFO'
        "FILEVERSION $comma"
        "PRODUCTVERSION $comma"
        'FILEFLAGSMASK 0x3fL'
        'FILEFLAGS 0x0L'
        'FILEOS VOS__WINDOWS32'
        'FILETYPE VFT_DLL'
        'FILESUBTYPE VFT2_UNKNOWN'
        'BEGIN'
        '    BLOCK "StringFileInfo"'
        '    BEGIN'
        '        BLOCK "040904b0"'
        '        BEGIN'
        '            VALUE "CompanyName", "HiBARA Software, LLC"'
        '            VALUE "FileDescription", "Date and Time Insertion Macro for Hidemaru Editor"'
        "            VALUE ""FileVersion"", ""$dot"""
        '            VALUE "InternalName", "insdate"'
        '            VALUE "LegalCopyright", "Copyright (C) 2011-2026 Mitsuhiro Hibara"'
        '            VALUE "OriginalFilename", "insdate.dll"'
        '            VALUE "ProductName", "insdate"'
        "            VALUE ""ProductVersion"", ""$dot"""
        '        END'
        '    END'
        '    BLOCK "VarFileInfo"'
        '    BEGIN'
        '        VALUE "Translation", 0x409, 1200'
        '    END'
        'END'
    )
    Set-Content -Path $rcPath -Value $rcLines -Encoding Ascii

    # rc.exe のフルパスを解決（vcvars で PATH に入らないことがあるため）
    # 1) vcvars がセットする WindowsSdkVerBinPath を優先
    # 2) 無ければ WindowsSdkDir + WindowsSDKVersion から組み立て
    # 3) それも無ければ既定インストール先の最新版 SDK を走査
    $sdkBinCandidates = @()
    if ($env:WindowsSdkVerBinPath) {
        $sdkBinCandidates += $env:WindowsSdkVerBinPath
    }
    if ($env:WindowsSdkDir -and $env:WindowsSDKVersion) {
        $sdkBinCandidates += (Join-Path $env:WindowsSdkDir "bin\$($env:WindowsSDKVersion)")
    }
    $defaultSdkBin = 'C:\Program Files (x86)\Windows Kits\10\bin'
    if (Test-Path $defaultSdkBin) {
        $verDirs = Get-ChildItem $defaultSdkBin -Directory -ErrorAction SilentlyContinue |
            Where-Object { $_.Name -match '^10\.' } | Sort-Object Name -Descending
        foreach ($vd in $verDirs) { $sdkBinCandidates += $vd.FullName }
    }

    # ARM Windows 上では特定 SDK 版の arm64 rc.exe が "not a valid application" で
    # 実行拒否されることがあるため、まず x64 rc.exe（ARM 上でもエミュ実行可）を試す。
    $rcExe = $null
    foreach ($bin in $sdkBinCandidates) {
        foreach ($sub in @('x64','arm64','x86')) {
            $cand = Join-Path $bin "$sub\rc.exe"
            if (Test-Path $cand) { $rcExe = $cand; break }
        }
        if ($rcExe) { break }
    }
    if (-not $rcExe) { throw "rc.exe が見つからない (試行: $($sdkBinCandidates -join '; '))" }
    Write-Host "Using rc.exe: $rcExe" -ForegroundColor DarkGray

    & $rcExe /nologo /fo $resPath $rcPath | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "rc.exe failed for $a" }
    # RUSTFLAGS:
    #   -Clink-arg=<res>            … VERSIONINFO(.res) をターゲット DLL にリンクで埋め込む
    #   -C target-feature=+crt-static … CRT(vcruntime140/ucrtbase)を DLL 内に静的リンク
    #                                    → 外部依存を KnownDLLs 対象のシステム DLL のみに
    #                                      限定し、DLL ハイジャック耐性を高める
    # ※ 環境変数 RUSTFLAGS がセットされていると .cargo/config.toml の
    #   target.<triple>.rustflags は無視されるため、必要な指定は全部ここに集約する。
    $env:RUSTFLAGS = "-Clink-arg=$resPath -C target-feature=+crt-static"

    cargo build --release --target $rustTarget
    if ($LASTEXITCODE -ne 0) { throw "cargo build failed for $a" }

    $dll = Join-Path $targetDir "$rustTarget\release\insdate.dll"

    # dumpbin.exe を解決（vcvars で PATH に入らないことがあるため）
    # 1) PATH 上を探す
    # 2) 無ければ VS の VC\Tools\MSVC\<ver>\bin\Host<host>\<target>\ を走査
    $dumpbin = (Get-Command dumpbin.exe -ErrorAction SilentlyContinue).Source
    if (-not $dumpbin) {
        # $vc = ...\VC\Auxiliary\Build\vcvarsall.bat → 4階層上が VS ルート
        $vsRoot = Split-Path -Parent (Split-Path -Parent (Split-Path -Parent (Split-Path -Parent $vc)))
        $msvcRoot = Join-Path $vsRoot 'VC\Tools\MSVC'
        if (Test-Path $msvcRoot) {
            $hostArch = if ($env:PROCESSOR_ARCHITECTURE -eq 'ARM64') { 'arm64' } else { 'x64' }
            $targetArch = if ($a -eq 'x64') { 'x64' } else { 'x86' }
            $verDirs = Get-ChildItem $msvcRoot -Directory | Sort-Object Name -Descending
            foreach ($vd in $verDirs) {
                # まずは host/target 組み合わせ、次にホストの汎用
                foreach ($h in @($hostArch, 'x64', 'arm64')) {
                    foreach ($t in @($targetArch, 'x64', 'x86', 'arm64')) {
                        $cand = Join-Path $vd.FullName "bin\Host$h\$t\dumpbin.exe"
                        if (Test-Path $cand) { $dumpbin = $cand; break }
                    }
                    if ($dumpbin) { break }
                }
                if ($dumpbin) { break }
            }
        }
    }

    if ($dumpbin) {
        Write-Host "--- exports ($a) ---" -ForegroundColor Yellow
        & $dumpbin /exports $dll | Select-String -Pattern 'GetDateString|GetCreateDateString|GetLastWriteDateString|GetAccessDateString'
    } else {
        Write-Host "dumpbin.exe not found; skipping export verification for $a" -ForegroundColor DarkYellow
    }

    # 埋め込まれたファイルバージョンを確認表示（空なら埋め込み失敗）
    $fv = (Get-Item $dll).VersionInfo.FileVersion
    Write-Host "File version ($a): $fv" -ForegroundColor Yellow

    # dist\ 直下へ、ビット数付きの名前でコピー（32/64 を同居させる）
    New-Item -ItemType Directory -Force -Path $dist | Out-Null
    $outPath = Join-Path $dist $outName
    Copy-Item $dll $outPath -Force
    Write-Host "Copied -> $outPath" -ForegroundColor Green
}

if ($Arch -eq 'both') { Invoke-Build 'x64' $Version; Invoke-Build 'x86' $Version }
else { Invoke-Build $Arch $Version }

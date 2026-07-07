// ---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#include <locale.h>
#include <locale>

#include "DateUtils.hpp"

#define MAX_OUPUT_TEXT 256

#define FILE_TIMESTAMP_NONE 0            //タイムスタンプは取得しない
#define FILE_TIMESTAMP_CREATE_DATE 1     //作成日時
#define FILE_TIMESTAMP_LASTWRITE_DATE 2  //更新日時
#define FILE_TIMESTAMP_ACCESS_DATE 3     //アクセス日時

#ifdef __cplusplus

/* C++ 言語の場合 */
#define HIDEMARU_MACRO_DLL extern "C" __declspec(dllexport)

#else /* __cplusplus */

/* C 言語の場合 */
#define HIDEMARU_MACRO_DLL __declspec(dllexport)

#endif /* __cplusplus */

//===================================
//外部関数
//===================================
HIDEMARU_MACRO_DLL char* GetDateString(
	char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);

HIDEMARU_MACRO_DLL char* GetDateStringEn(
	char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);

//作成日時
HIDEMARU_MACRO_DLL char* GetCreateDateString(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);
HIDEMARU_MACRO_DLL char* GetCreateDateStringEn(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);

//更新日時
HIDEMARU_MACRO_DLL char* GetLastWriteDateString(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);
HIDEMARU_MACRO_DLL char* GetLastWriteDateStringEn(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);

//アクセス日時
HIDEMARU_MACRO_DLL char* GetAccessDateString(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);
HIDEMARU_MACRO_DLL char* GetAccessDateStringEn(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second);

//===================================
//内部関数
//===================================
String CreateDateTimeString(
	char*format, char*filepath, int Lang, int fOption,
	int Year, int Month, int Day, int Hour, int Minute, int Second);

TDateTime GetFromFileTimestamp(String FilePath, int fOption);

String GetLocaleLangType(void);

//文字列置換
void strchg(char *buf, const char *str1, const char *str2);

// extern "C" __declspec(dllexport)
// char* __stdcall GetDateStringFromFileTimestamp(char* filepath, char* format,
// int Year, int Month, int Day, int Hour, int Minute, int Second);

#pragma hdrstop
//-------------------------------------------------------------------------
// 以下は，ユーザー DLL が静的ランタイムライブラリを使う場合の DLL
// メモリ管理に関する重要な注意です
//
// 引数または返り値として String 型オブジェクト (または String を含む構
// 造体・クラス) を扱う関数を DLL からエクスポートする使う場合，その DLL
// のプロジェクトや，その DLL を使うプロジェクトに MEMMGR.LIB ライブラリ
// を追加する必要があります。
//
// DLL からエクスポートされた，TObject から派生されていないクラスに対して
// new または delete を使う場合にも MEMMGR.LIB を追加しなければなりません。
//
// MEMMGR.LIB を追加することにより，DLL と DLL を参照する EXE が共通の
// メモリマネージャとして BORLNDMM.DLL を使うようになります。
// この場合，DLL またはアプリケーションとともに BORLANDMM.DLL を配布して
// ください。
//
// BORLNDMM.DLL が使われるのを避けるには，String 型のかわりに
// "char *" または ShortString 型を使ってください。
//
// 作成する DLL が共有 RTL DLL を使う場合，RTL の方で MEMMGR.LIB をライブ
// ラリとして追加するため DLL プロジェクトに明示的に追加する必要はありま
// せん。
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma argsused

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason,
	void* lpReserved) {

	// #ifdef LANG_EN
	// 英語表記
	// char lang[] = "English_United States.1252";
	// std::locale::global(std::locale(lang));
	// setlocale(LC_ALL, lang);
	// #else
	// 日本語表記
	// char lang[] = "Japanese_Japan.20932";
	// std::locale::global(std::locale(lang));
	// setlocale(LC_ALL, lang);
	// #endif

	return 1;

}
//---------------------------------------------------------------------------
// 日付書式を生成（デフォルトロケール）
//---------------------------------------------------------------------------
char* GetDateString(char* format, int Year, int Month,
	int Day, int Hour, int Minute, int Second) {

	// 秀丸マクロから呼ばれる場合、
	// 変数は固定のメモリ領域のアドレスにないとダメらしい
	static char output[MAX_OUPUT_TEXT];

	String OutputText =
		CreateDateTimeString(
			format, NULL, 0,     //デフォルトロケール
			FILE_TIMESTAMP_NONE,
			Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//---------------------------------------------------------------------------
// 日付書式を生成（英語表記）
//---------------------------------------------------------------------------
char* GetDateStringEn(char* format, int Year, int Month,
	int Day, int Hour, int Minute, int Second) {

	static char output[MAX_OUPUT_TEXT];

	String OutputText =
		CreateDateTimeString(
			format, NULL, 1, // 英語表記
			FILE_TIMESTAMP_NONE,
			Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//---------------------------------------------------------------------------
// ファイルの「作成日時」から文字列を取得
//---------------------------------------------------------------------------
char* GetCreateDateString(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second) {

	static char output[MAX_OUPUT_TEXT];

	String OutputText = CreateDateTimeString(
		format, filepath, 0,        // デフォルトロケール
		FILE_TIMESTAMP_CREATE_DATE,	// 作成日時
		Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//---------------------------------------------------------------------------
// ファイルの「作成日時」から文字列を取得から文字列を取得（英語表記）
//---------------------------------------------------------------------------
char* GetCreateDateStringEn(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second) {

	static char output[MAX_OUPUT_TEXT];

	String OutputText = CreateDateTimeString(
		format, filepath, 1,        // 英語表記
		FILE_TIMESTAMP_CREATE_DATE,	// 作成日時
		Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//---------------------------------------------------------------------------
// ファイルの「更新日時」から文字列を取得
//---------------------------------------------------------------------------
char* GetLastWriteDateString(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second) {

	static char output[MAX_OUPUT_TEXT];

	String OutputText = CreateDateTimeString(
		format, filepath, 0,            // デフォルトロケール
		FILE_TIMESTAMP_LASTWRITE_DATE,	// 更新日時
		Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//---------------------------------------------------------------------------
// ファイルの「更新日時」から文字列を取得から文字列を取得（英語表記）
//---------------------------------------------------------------------------
char* GetLastWriteDateStringEn(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second) {

	static char output[MAX_OUPUT_TEXT];

	String OutputText = CreateDateTimeString(
		format, filepath, 1,            // 英語表記
		FILE_TIMESTAMP_LASTWRITE_DATE,	// 更新日時
		Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//---------------------------------------------------------------------------
// ファイルの「アクセス日時」から文字列を取得
//---------------------------------------------------------------------------
char* GetAccessDateString(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second){

	static char output[MAX_OUPUT_TEXT];

	String OutputText = CreateDateTimeString(
		format, filepath, 0,          // デフォルトロケール
		FILE_TIMESTAMP_ACCESS_DATE,  	// アクセス日時
		Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//---------------------------------------------------------------------------
// ファイルの「アクセス日時」から文字列を取得から文字列を取得（英語表記）
//---------------------------------------------------------------------------
char* GetAccessDateStringEn(
	char* filepath, char* format,
	int Year, int Month, int Day, int Hour, int Minute, int Second) {

	static char output[MAX_OUPUT_TEXT];

	String OutputText = CreateDateTimeString(
		format, filepath, 1,          // 英語表記
		FILE_TIMESTAMP_ACCESS_DATE,  	// アクセス日時
		Year, Month, Day, Hour, Minute, Second);

	StrCopy(output, OutputText.t_str());

	return(output);

}
//===========================================================================
// ↓内部関数↓
//===========================================================================

//---------------------------------------------------------------------------
// 入力された引数から日時文字列を生成して返す
//---------------------------------------------------------------------------
String CreateDateTimeString(
	char* format, char* filepath,
	int Lang,  int fOption,
	int Year, int Month, int Day, int Hour, int Minute, int Second) {

	// これはいずれもうまく機能しなかった
	// std::locale::global(std::locale("japanese_japan.20932"));
	// setlocale(LC_ALL, "japanese"); //ロケール

	String FilePath;
	String OutputText;

	TDateTime dtNow;

	FilePath = String(filepath);
	// String FilePath = (String)filepath;

	if (FileExists(FilePath) == true) {
		// if (FileAge(FilePath, dtNow) == false) {
		// ファイルのタイムスタンプ
		dtNow = GetFromFileTimestamp(FilePath, fOption);

		if (dtNow.operator double() == 0) {
			dtNow = Now();
		}
	}
	else {
		// ファイルパスがなければ現在日時
		dtNow = Now();
	}

	//-----------------------------------
	//時間の増減
	dtNow = IncHour(dtNow, Hour == NULL ? 0 : Hour);
	dtNow = IncMinute(dtNow, Minute == NULL ? 0 : Minute);
	dtNow = IncSecond(dtNow, Second == NULL ? 0 : Second);

	//-----------------------------------
	// 日付の増減
	dtNow = IncYear(dtNow, Year == NULL ? 0 : Year);
	dtNow = IncMonth(dtNow, Month == NULL ? 0 : Month);
	dtNow = IncDay(dtNow, Day == NULL ? 0 : Day);

	//-----------------------------------
	// ロケール（日本語環境のみ）
	if (GetLocaleLangType().CompareIC("Japanese") == 0) {
		// 午前・午後表記を使っている
		if (strstr(format, "ampm") != NULL ) {
			if (Hour == 12 || Hour == 0) { // 12時間制での「12時」は0時に変更する
				//書式自体を先に置き換えてしまう
				strchg( format, "hh", "00" );
				strchg( format, "h", "0" );
			}
		}
	}

	//デバッグ表示
	//ShowMessage(format);

	// 表示する日時をエンコードする
	//TDateTime dt = EncodeDateTime(year, month, day, hour, min, sec, msec);

	TFormatSettings fst;

	if (Lang == 1) {
		// 英語 (U.S.)
		LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			SORT_DEFAULT);
		GetLocaleFormatSettings(lcid, fst);
	}
	else {
		// デフォルトロケール
		GetLocaleFormatSettings(LOCALE_USER_DEFAULT, fst);
	}

	OutputText = FormatDateTime(format, dtNow, fst);

	// Win32 APIを直接コールする場合
	// SYSTEMTIME st;
	// DateTimeToSystemTime(dt, st);
	// http://msdn.microsoft.com/en-us/library/windows/desktop/ms695537%28v=vs.85%29.aspx
	// LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
	// GetDateFormat(lcid, 0, &st, FormatText, output, sizeof output / sizeof output[0]);

	return(OutputText);

}
//---------------------------------------------------------------------------
// ロケール言語を取得する（日本語環境なら、"Japanese"を返す）
//---------------------------------------------------------------------------
String GetLocaleLangType(void){

char *LangName = NULL;

LCID id = GetUserDefaultLCID();
int len = GetLocaleInfo( id, LOCALE_SENGLANGUAGE, NULL, 0);
if ( len > 0 ) {
	LangName = new char[len+1];
	ZeroMemory(LangName, len+1);
	GetLocaleInfo( id, LOCALE_SENGLANGUAGE, LangName, len+1);
	return((String)LangName);
}
else{
	return("");
}

}
//---------------------------------------------------------------------------
// 文字列置換
//
// ※参考にさせていただきました
// http://www.grapecity.com/tools/support/powernews/column/clang/049/page03.htm
//---------------------------------------------------------------------------
void strchg(char *buf, const char *str1, const char *str2)
{

char tmp[2048];
char *p;

int len = strlen(buf);

//見つからなくなるまで繰り返す
while ((p = strstr(buf, str1)) != NULL) {
	//pは旧文字列の先頭を指している */
	*p = '¥0';          /* 元の文字列を旧文字列の直前で区切って */
	p += strlen(str1);  /* ポインタを旧文字列の次の文字へ */
	strcpy(tmp, p);     /* 旧文字列から後を保存 */
	strcat(buf, str2);  /* 新文字列をその後につなぎ */
	strcat(buf, tmp);   /* さらに残りをつなぐ */
}

buf[len] = '\0';	//終端文字を挿入（これをやらないと二回目でゴミが入ってくる）


}
//---------------------------------------------------------------------------
// ファイルのタイムスタンプなどを取得する
//---------------------------------------------------------------------------
TDateTime GetFromFileTimestamp(String FilePath, int fOption) {

	TDateTime dtOutput;

	HANDLE hFile;
	FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
	FILETIME lftCreationTime, lftLastAccessTime, lftLastWriteTime;
	SYSTEMTIME stCreationTime, stLastAccessTime, stLastWriteTime;

	hFile = CreateFileW(FilePath.c_str(), 0, FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE) {

		GetFileTime(hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);

		switch(fOption){

		//#define FILE_TIMESTAMP_CREATE_DATE 1     //作成日時
		case FILE_TIMESTAMP_CREATE_DATE:
			FileTimeToLocalFileTime(&ftCreationTime, &lftCreationTime);
			FileTimeToSystemTime(&lftCreationTime, &stCreationTime);
			dtOutput = SystemTimeToDateTime(stCreationTime);
			break;

		//#define FILE_TIMESTAMP_LASTWRITE_DATE 2  //更新日時
		case FILE_TIMESTAMP_LASTWRITE_DATE:
			FileTimeToLocalFileTime(&ftLastWriteTime ,&lftLastWriteTime);
			FileTimeToSystemTime(&lftLastWriteTime ,&stLastWriteTime);
			dtOutput = SystemTimeToDateTime(stLastWriteTime);
			break;

		//#define FILE_TIMESTAMP_ACCESS_DATE 3     //アクセス日
		case FILE_TIMESTAMP_ACCESS_DATE:
			FileTimeToLocalFileTime(&ftLastAccessTime ,&lftLastAccessTime);
			FileTimeToSystemTime(&lftLastAccessTime ,&stLastAccessTime);
			dtOutput = SystemTimeToDateTime(stLastAccessTime);
			break;

		default:
			//オプション指定が無いので現在日時
			dtOutput = Now();
			break;
		}
	}
	else{
		dtOutput = NULL;
		return(dtOutput);
	}

	CloseHandle(hFile);

	return(dtOutput);

}




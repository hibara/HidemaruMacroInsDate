//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

//DLLファイル
FileList[0][0] = "insdate.dll";
FileList[0][1] = "日付時刻挿入マクロの動作に必要なファイルです。";

//マクロファイル
FileList[1][0] = "InsertDate.mac";
FileList[1][1] = "標準的な日付時刻文字列を挿入するマクロです。";
FileList[2][0] = "InsertDateList01.mac";
FileList[2][1] = "さまざまな書式の日時をリストメニューから挿入するマクロです。";
FileList[3][0] = "InsertDateList02.mac";
FileList[3][1] = "書式サンプル集です。必要な書式を探して参考にしてみてください。";
FileList[4][0] = "InsertDateList03.mac";
FileList[4][1] = "編集中のテキストファイルのタイムスタンプを取得して挿入します。";

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

int i;
String MsgText;
String FilePath, FileName, DestFilePath;

//引数が指定されてきた場合
if ( ParamCount() > 0 && ParamStr(1) == "-s"){

	String DestDirPath = ParamStr(2);

	if (DirectoryExists(DestDirPath) == false) {
		//エラーメッセージ
		MsgText = "秀丸エディタがインストールされているフォルダーが見つかりません。\n";
		MsgText += "インストール(コピー)できませんでした。";
		MessageDlg(MsgText, mtError, TMsgDlgButtons()<<mbOK,  NULL );
		exit(0);
	}

	for ( i = 3; i < ParamCount()+1; i++ ){
		FilePath = ParamStr(i);
		if (FileExists(FilePath) == false) {
			//エラーメッセージ
			MsgText = "コピーしようとしたファイルが見つかりません！\n";
			MsgText += "インストール(コピー)できませんでした。\n" + ExtractFileName(FilePath);
			MessageDlg(MsgText, mtError, TMsgDlgButtons()<<mbOK,  NULL );
			exit(0);
		}
		else{
			//コピーする
			DestFilePath = IncludeTrailingPathDelimiter(DestDirPath)+ExtractFileName(FilePath);
			CopyFile(FilePath.t_str(), DestFilePath.t_str(), false);
		}

	}//loop;

	//Application->Terminate();
	exit(0);

}

Label1->Caption =
"日付時刻挿入マクロに必要なファイルを秀丸エディタのあるフォルダーにコピーします。\n\
以下の秀丸エディタ本体（Hidemaru.exe）の場所が正しくない場合は変更してください。\n\
インストール（コピー）には管理者権限での実行が必要な場合があります。\
";
cmdInstall->Left = Form1->ClientWidth/2 - cmdInstall->Width - 8;
cmdClose->Left = Form1->ClientWidth/2 + 8;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{

//

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{

int i, num;
int ret;
//TSearchRec sr;
String FilePath, FileName;

//-----------------------------------
//インストーラーのディレクトリパス

//※実行ファイルパスはいったん絶対パスに展開(ExpandFileName)
//　しておかないと相対パス"."が含まれてしまう
String AppDirPath = ExtractFileDir(ExpandFileName(Application->ExeName));

//-----------------------------------
//ステータスバーにバージョン番号の表示

TGetAppInfoString *pAppInfoString = new TGetAppInfoString();
StatusBar1->Panels->Items[0]->Text = "ver." + pAppInfoString->FileVersion;
delete pAppInfoString;

//-----------------------------------
//ファイルリスト
num = sizeof(FileList)/sizeof(FileList[0]);

for (i = 0; i < num; i++) {

	FilePath = ExpandFileName(FileList[i][0]);

	if (FileExists(FilePath) == true) {
		FileName = ExtractFileName(FilePath);
		TListItem *AddItem = ListView1->Items->Add();
		AddItem->Caption = FileName;
		AddItem->SubItems->Add(FileList[i][1]);	//ファイルの説明
		AddItem->SubItems->Add(FilePath);
		AddItem->Checked = true;
	}

}

//-----------------------------------
//秀丸マクロ実行に必要なDLLファイルを検索
/*
ret = FindFirst(IncludeTrailingPathDelimiter(AppDirPath) + "*.dll", faAnyFile, sr);

while (ret == 0) {

	if (sr.Name != "." && sr.Name != "..") {

		if (sr.Attr & faDirectory) {
		}
		else{
			TListItem *AddItem = ListView1->Items->Add();
			AddItem->Caption = sr.Name;
			AddItem->SubItems->Add("秀丸マクロ動作に必要なファイル");
			AddItem->SubItems->Add(IncludeTrailingPathDelimiter(AppDirPath)+sr.Name);
			AddItem->Checked = true;
		}

	}

	ret = FindNext(sr);

}//while;

FindClose(sr);

//秀丸マクロファイルを検索
String MacroFilePath = "";
ret = FindFirst(AppDirPath + "\\*.mac", faAnyFile, sr);

while (ret == 0) {

	if (sr.Name != "." && sr.Name != "..") {

		if (sr.Attr & faDirectory) {
		}
		else{
			TListItem *AddItem = ListView1->Items->Add();
			FileName = sr.Name;
			AddItem->Caption = FileName;
			if(MacroFilePath == "" ){
				MacroFilePath = IncludeTrailingPathDelimiter(AppDirPath)+FileName;
			}
			AddItem->SubItems->Add("秀丸マクロファイル");
			AddItem->SubItems->Add(IncludeTrailingPathDelimiter(AppDirPath)+sr.Name);
			AddItem->Checked = true;
		}

	}

	ret = FindNext(sr);

}//while;

FindClose(sr);

*/

//-----------------------------------
//実行ファイルパスを取得する
char exefilepath[MAX_PATH];
//実行ファイルパス（秀丸エディタ？）
FindExecutable("readme.txt", NULL, exefilepath);
Edit1->Text = exefilepath;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdCloseClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdOpenHidemaruClick(TObject *Sender)
{

String DirPath = ExtractFileDir(Edit1->Text);

if (DirectoryExists(DirPath)) {
	OpenDialog1->InitialDir = DirPath;
}

if (OpenDialog1->Execute() == true) {
	Edit1->Text = OpenDialog1->FileName;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdInstallClick(TObject *Sender)
{

int i;
int res;
String MsgText;

//char *rs;
//String CommandLine = "copy";
String Parameters = "";
String DirPath = ExtractFileDir(Edit1->Text);;

if (DirectoryExists(DirPath) == false) {
	//エラーメッセージ
	MsgText =
	"秀丸エディタがインストールされているフォルダーが見つかりません。\n\
	インストール(コピー)できませんでした。";
	MessageDlg(MsgText, mtError, TMsgDlgButtons()<<mbOK,  NULL );
	return;
}

//-----------------------------------
//自分自身をUACしてから二重起動する
TShellExecuteInfoA sei = {0};

if ( Win32MajorVersion >= 6 ) {
	sei.lpVerb = "runas";	//Vista以降
}
else{
	sei.lpVerb = "open";	//その他OS
}

sei.cbSize = sizeof(sei);
sei.hwnd = Application->Handle;
sei.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_FLAG_NO_UI;
sei.lpFile = Application->ExeName.t_str();

TStringList *FileStringList = new TStringList();
for (i = 0; i < ListView1->Items->Count; i++) {
	//チェックありのファイルのみをリストアップする
	if (ListView1->Items->Item[i]->Checked == true) {
		FileStringList->Add(ListView1->Items->Item[i]->SubItems->Strings[1]);
	}
}

Parameters = "-s ";	                  // 1番目にスイッチ
Parameters += "\"" + DirPath + "\"";	// 2番目に秀丸エディタのディレクトリパス
for (i = 0; i < FileStringList->Count; i++) {
	Parameters += (" \"" + FileStringList->Strings[i] + "\"");	//コピーファイル
}

sei.lpParameters = Parameters.t_str();
sei.nShow = SW_SHOWNOACTIVATE;

if ( ShellExecuteEx(&sei) == true){
	//成功
	MsgText = "正常にインストール(コピー)されました。";
	for (i = 0; i < FileStringList->Count; i++) {
		MsgText += "\n" + ExtractFileName(FileStringList->Strings[i]);
	}
	MessageDlg(MsgText, mtInformation, TMsgDlgButtons()<<mbOK,  NULL );
}
else{
	//エラー：RaiseLastOSError();
	MsgText =
	"インストール中に問題が発生したようです。\n\
	インストール(コピー)できませんでした。";
	MessageDlg(MsgText, mtError, TMsgDlgButtons()<<mbOK,  NULL );
}

delete FileStringList;


}
//---------------------------------------------------------------------------

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
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

//ドラッグ＆ドロップを許可する
DragAcceptFiles(Handle,true);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{

//レジストリ操作
TRegIniFile *pReg = new TRegIniFile("Software\\Hibara");

//フォーム状態
int WinStyle;

if ( Form1->WindowState == wsMinimized ){ //最小化
	WinStyle = 1;
}
else if ( Form1->WindowState == wsMaximized ){//最大化
	WinStyle = 2;
}
else{
	WinStyle = 0;
}

//フォーム状態、位置、サイズ
pReg->WriteInteger( "InsDateMenuBuilder\\WindowPos", "FormStyle", WinStyle);
pReg->WriteInteger( "InsDateMenuBuilder\\WindowPos", "WindowTop", Form1->Top);
pReg->WriteInteger( "InsDateMenuBuilder\\WindowPos", "WindowLeft", Form1->Left);

if ( WinStyle != 2 ){ //最大化以外はサイズを記録
	pReg->WriteInteger( "InsDateMenuBuilder\\WindowPos", "WindowWidth", Form1->Width);
	pReg->WriteInteger( "InsDateMenuBuilder\\WindowPos", "WindowHeight", Form1->Height);
}

pReg->CloseKey();
delete pReg;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{

//レジストリ操作
TRegIniFile *pReg = new TRegIniFile("Software\\Hibara");

//フォーム位置
int FormTop = pReg->ReadInteger( "InsDateMenuBuilder\\WindowPos", "WindowTop", Screen->Height/2-Form1->Height/2);
int FormLeft = pReg->ReadInteger( "InsDateMenuBuilder\\WindowPos", "WindowLeft", Screen->Width/2-Form1->Width/2);
int FormWidth = pReg->ReadInteger( "InsDateMenuBuilder\\WindowPos", "WindowWidth", 600);
int FormHeight = pReg->ReadInteger( "InsDateMenuBuilder\\WindowPos", "WindowHeight", 500);
int WinStyle = pReg->ReadInteger( "InsDateMenuBuilder\\WindowPos", "FormStyle", 0);

//フォーム位置の修正（スクリーン外にある場合は戻す）
if ( FormTop < 0 ) FormTop = 0;
if ( FormLeft < 0 ) FormLeft = 0;
if ( FormTop+FormHeight > Screen->Height ) FormTop = Screen->Height-FormHeight;
if ( FormLeft+FormWidth > Screen->Width ) FormLeft = Screen->Width-FormWidth;

Form1->Top = FormTop;
Form1->Left = FormLeft;
Form1->Width = FormWidth;
Form1->Height = FormHeight;

//フォームの状態
if ( WinStyle == 1 ){
	Application->Minimize();//最小化
}
else if ( WinStyle == 2 ){
	Form1->WindowState = wsMaximized; //最大化
}
else{
	Form1->WindowState = wsNormal;
}

delete pReg;

//-----------------------------------
//デバッグ
ParseCodeFile("");



}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
if ( Key == VK_ESCAPE ){
	Close();
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cmdExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDockOver(TObject *Sender, TDragDockObject *Source, int X,
          int Y, TDragState State, bool &Accept)
{
//ドラッグを受け容れ
Accept = true;
}
//---------------------------------------------------------------------------
//フォーム上にファイルのドラッグ＆ドロップを可能にする関数
MESSAGE void __fastcall TForm1::FWmDropFiles(TWMDropFiles &msg)
{

int DropCount;//ドロップされたファイル数
wchar_t DropFileName[MAX_PATH];//ドロップされたファイル名
POINT droppoint;//ドロップされた位置

//ファイル数を取得するには0xFFFFFFFFを指定
DropCount = DragQueryFile((HDROP)msg.Drop,0xFFFFFFFF,NULL,MAX_PATH);


for ( int i = 0; i < DropCount; i++ ){

	//i番目のファイル名を取得
	DragQueryFileW((HDROP)msg.Drop,i,DropFileName,MAX_PATH);

	if (String(".TXT").CompareIC(ExtractFileExt(DropFileName)) == 0){

		//===================================
    //処理したいルーチン
    //===================================



	}//end if;

}//end for;


}//end FWmDropFiles;
//---------------------------------------------------------------------------
//指定のコードファイルをパースする
bool __fastcall TForm1::ParseCodeFile(String FilePath)
{

int i;
String OneLine;
String ResultString;

String SourceCode;

//using namespace SkRegExpW;

//デバッグ
FilePath = "InsertDateList02.mac";

if (FileExists(FilePath) == false) {
	return(false);
}

TStringList *FileList = new TStringList();
FileList->LoadFromFile(FilePath);

for( i = 0; i < FileList->Count; i++ ){

	OneLine = FileList->Strings[i];

	//unique_ptr<TSkRegExp> r(new TSkRegExp());

	TSkRegExp *r = new TSkRegExp();

	//$InsDate[0] = dllfuncstr( #dll, "GetDateString", "yyyy/mm/dd", 0);
	//$InsDate[14] = dllfuncstr( #dll, "GetDateString", "hh:nn:ss", 0, 0, 0, 12, 0, 0);

	//正規表現パターンを設定
	r->Expression = "\$InsDate\[[0-9]*\].*;";
	//検索開始
	if (r->Exec(OneLine)) {

		do{

			if (r->MatchPos[0] > 0) {

				SourceCode = r->Match[0];

				SourceCode = SourceCode.SubString(String("$InsDate[").Length()+1, SourceCode.Length());




				//デバッグ
				ResultString += SourceCode;

			}









		}while(r->ExecNext());


	}

	delete r;


}//loop;

ShowMessage(ResultString);

delete FileList;
return(true);

}
//---------------------------------------------------------------------------


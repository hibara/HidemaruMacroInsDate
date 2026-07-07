//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <Registry.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>     //レジストリ操作用

#include <memory>
#include "SkRegExpW.hpp"


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPaintBox *PaintBox1;
	TMainMenu *MainMenu1;
	TMenuItem *mnuFile;
	TMenuItem *mnuHelp;
	TMenuItem *mnuExit;
	TMenuItem *mnuHelpContents;
	TMenuItem *N1;
	TMenuItem *mnuAbout;
	TPanel *Panel1;
	TButton *cmdExit;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cmdExitClick(TObject *Sender);
	void __fastcall FormDockOver(TObject *Sender, TDragDockObject *Source, int X, int Y,
          TDragState State, bool &Accept);

private:	// ユーザー宣言

	//フォーム上にファイルのドラッグ＆ドロップを可能にする関数
	MESSAGE void __fastcall TForm1::FWmDropFiles(TWMDropFiles &msg);



public:		// ユーザー宣言
	__fastcall TForm1(TComponent* Owner);


	//指定のコードファイルをパースする
	bool __fastcall ParseCodeFile(String FilePath);



};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

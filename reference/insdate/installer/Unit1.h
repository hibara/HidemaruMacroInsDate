//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "GetAppInfoString.h"
#include <CheckLst.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TStatusBar *StatusBar1;
	TPanel *Panel1;
	TButton *cmdInstall;
	TButton *cmdClose;
	TLabeledEdit *Edit1;
	TListView *ListView1;
	TBitBtn *cmdOpenHidemaru;
	TBalloonHint *BalloonHint1;
	TOpenDialog *OpenDialog1;
	TLabel *Label1;
	TFileOpenDialog *FileOpenDialog1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall cmdCloseClick(TObject *Sender);
	void __fastcall cmdOpenHidemaruClick(TObject *Sender);
	void __fastcall cmdInstallClick(TObject *Sender);

private:	// ユーザー宣言



public:		// ユーザー宣言

	__fastcall TForm1(TComponent* Owner);

	//インストールファイルリスト
	String FileList[5][2];


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

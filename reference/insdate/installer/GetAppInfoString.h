//======================================================================
//
//	GetAppInfoStringクラス     Ver.1.00      Copyright(C) 2011 M.Hibara
// 
// 
// ※ソースは無保証の代わりに、特に使用条件はありません。
//   改造、転載はご自由にどうぞ。作者への連絡もいりません。
//
//   Site: http://homepage2.nifty.com/hibara/software/
//   Blog: http://hibara.sblo.jp/
//   E-mail: hibara@mbh.nity.com
//
//======================================================================

//----------------------------------------------------------------------
#ifndef GetAppInfoStringHeader
#define GetAppInfoStringHeader

//----------------------------------------------------------------------
class TGetAppInfoString : public TObject
{
private:

	int VersionWithoutDot(String strVerNum);


protected:

public:

	LPVOID* pVersionInfo;

	__fastcall TGetAppInfoString();
	__fastcall ~TGetAppInfoString();

	String Comments;
	String InternalName;
	String ProductName;
	String CompanyName;
	String LegalCopyright;
	String ProductVersion;
	int ProductVersionNum;
	String FileDescription;
	String LegalTrademarks;
	String PrivateBuild;
	String FileVersion;
	int FileVersionNum;
	String OriginalFilename;
	String SpecialBuild;

};


#endif


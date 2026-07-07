// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Skregexpw.pas' rev: 21.00

#ifndef SkregexpwHPP
#define SkregexpwHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Contnrs.hpp>	// Pascal unit
#include <Comctrls.hpp>	// Pascal unit
#include <Skregexpconst.hpp>	// Pascal unit
#include <Unicodeprop.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Skregexpw
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESkRegExp;
class PASCALIMPLEMENTATION ESkRegExp : public Sysutils::Exception
{
	typedef Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESkRegExp(const System::UnicodeString Msg) : Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESkRegExp(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	/* Exception.CreateRes */ inline __fastcall ESkRegExp(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	/* Exception.CreateResFmt */ inline __fastcall ESkRegExp(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	/* Exception.CreateHelp */ inline __fastcall ESkRegExp(const System::UnicodeString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESkRegExp(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESkRegExp(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESkRegExp(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESkRegExp(void) { }
	
};


class DELPHICLASS ESkRegExpRuntime;
class PASCALIMPLEMENTATION ESkRegExpRuntime : public ESkRegExp
{
	typedef ESkRegExp inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESkRegExpRuntime(const System::UnicodeString Msg) : ESkRegExp(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESkRegExpRuntime(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : ESkRegExp(Msg, Args, Args_Size) { }
	/* Exception.CreateRes */ inline __fastcall ESkRegExpRuntime(int Ident)/* overload */ : ESkRegExp(Ident) { }
	/* Exception.CreateResFmt */ inline __fastcall ESkRegExpRuntime(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : ESkRegExp(Ident, Args, Args_Size) { }
	/* Exception.CreateHelp */ inline __fastcall ESkRegExpRuntime(const System::UnicodeString Msg, int AHelpContext) : ESkRegExp(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESkRegExpRuntime(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : ESkRegExp(Msg, Args, Args_Size, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESkRegExpRuntime(int Ident, int AHelpContext)/* overload */ : ESkRegExp(Ident, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESkRegExpRuntime(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : ESkRegExp(ResStringRec, Args, Args_Size, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESkRegExpRuntime(void) { }
	
};


class DELPHICLASS ESkRegExpCompile;
class PASCALIMPLEMENTATION ESkRegExpCompile : public ESkRegExp
{
	typedef ESkRegExp inherited;
	
public:
	int ErrorPos;
public:
	/* Exception.Create */ inline __fastcall ESkRegExpCompile(const System::UnicodeString Msg) : ESkRegExp(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESkRegExpCompile(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : ESkRegExp(Msg, Args, Args_Size) { }
	/* Exception.CreateRes */ inline __fastcall ESkRegExpCompile(int Ident)/* overload */ : ESkRegExp(Ident) { }
	/* Exception.CreateResFmt */ inline __fastcall ESkRegExpCompile(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : ESkRegExp(Ident, Args, Args_Size) { }
	/* Exception.CreateHelp */ inline __fastcall ESkRegExpCompile(const System::UnicodeString Msg, int AHelpContext) : ESkRegExp(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESkRegExpCompile(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : ESkRegExp(Msg, Args, Args_Size, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESkRegExpCompile(int Ident, int AHelpContext)/* overload */ : ESkRegExp(Ident, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESkRegExpCompile(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : ESkRegExp(ResStringRec, Args, Args_Size, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESkRegExpCompile(void) { }
	
};


typedef Classes::TStrings TREStrings;

typedef Classes::TStringList TREStringList;

typedef System::UnicodeString REString;

#pragma option push -b-
enum TRECompareOption { coIgnoreCase, coIgnoreWidth, coIgnoreKana };
#pragma option pop

typedef Set<TRECompareOption, coIgnoreCase, coIgnoreKana>  TRECompareOptions;

#pragma option push -b-
enum TREOption { roNone, roIgnoreCase, roMultiLine, roNamedGroupOnly, roSingleLine, roExtended, roIgnoreWidth, roIgnoreKana, roDefinedCharClassLegacy };
#pragma option pop

typedef Set<TREOption, roNone, roDefinedCharClassLegacy>  TREOptions;

typedef TREOptions *PREOptions;

#pragma option push -b-
enum TREToken { tkEnd, tkChar, tkUnion, tkQuest, tkDot, tkRangeChar, tkLHead, tkLTail, tkEmpty, tkLPar, tkRPar, tkStar, tkPlus, tkBound, tkCharClassFirst, tkNegativeCharClassFirst, tkCharClassEnd, tkGroupBegin, tkReference, tkReferenceRelative, tkNamedReference, tkLParWithOption, tkWordChar, tkNEWordChar, tkDigitChar, tkNEDigitChar, tkHexDigitChar, tkNEHexDigitChar, tkSpaceChar, tkNESpaceChar, tkTHead, tkTTail, tkTTailEnd, tkWordBoundary, tkNEWordBoundary, tkOption, tkHorizontalSpaceChar, tkNEHorizontalSpaceChar, tkVerticalSpaceChar, tkNEVerticalSpaceChar, tkLineBreak, tkPosixBracket, tkNEPosixBracket, tkProperty, tkNEProperty, tkNoBackTrack, tkKeepPattern, tkAheadMatch, tkAheadNoMatch, tkBehindMatch, tkBehindNoMatch, tkCombiningSequence, tkGoSub, tkGoSubName, tkGoSubRelative, tkIfMatch, tkIfMatchRef, tkGlobalPos, tkBranchReset, tkFail };
#pragma option pop

#pragma option push -b-
enum TREOperator { opEmply, opConcat, opUnion, opGroup, opLHead, opLTail, opQuest, opPlus, opStar, opBound, opLoop, opNoBackTrack, opKeepPattern, opAheadMatch, opAheadNoMatch, opBehindMatch, opBehindNoMatch, opGoSub, opIfMatch, opIfThen, opFail };
#pragma option pop

#pragma option push -b-
enum TRENFAKind { nkNormal, nkChar, nkEmpty, nkStar, nkPlus, nkBound, nkLoop, nkLoopExit, nkLoopEnd, nkGroupBegin, nkGroupEnd, nkKeepPattern, nkNoBackTrack, nkMatchEnd, nkEnd, nkGoSub, nkAheadMatch, nkAheadNoMatch, nkBehindMatch, nkBehindNoMatch, nkIfMatch, nkIfThen, nkFail };
#pragma option pop

#pragma option push -b-
enum TRELoopKind { lkGreedy, lkReluctant, lkSimpleReluctant, lkPossessive, lkAny, lkCombiningSequence };
#pragma option pop

class DELPHICLASS TREQuickSearch;
class PASCALIMPLEMENTATION TREQuickSearch : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::WideChar *FPattern;
	int FPatternLen;
	StaticArray<int, 256> FSkipTable;
	System::WideChar *FTextTopP;
	System::WideChar *FTextEndP;
	int FTextLen;
	bool FCompiled;
	System::WideChar *FMatchP;
	System::UnicodeString FFindText;
	TRECompareOptions FOptions;
	void __fastcall SetFindText(const System::UnicodeString Value);
	void __fastcall SetOptions(const TRECompareOptions Value);
	int __fastcall GetMatchPos(void);
	
protected:
	bool __fastcall IsMatch(System::WideChar * AStr, TRECompareOptions AOptions);
	
public:
	void __fastcall Clear(void);
	void __fastcall Compile(void);
	bool __fastcall Exec(System::WideChar * AStr, int ATextLen);
	bool __fastcall ExecNext(void);
	__property System::UnicodeString FindText = {read=FFindText, write=SetFindText};
	__property System::WideChar * MatchP = {read=FMatchP};
	__property int MatchPos = {read=GetMatchPos, nodefault};
	__property TRECompareOptions Options = {read=FOptions, write=SetOptions, nodefault};
public:
	/* TObject.Create */ inline __fastcall TREQuickSearch(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TREQuickSearch(void) { }
	
};


class DELPHICLASS TRECapture;
class PASCALIMPLEMENTATION TRECapture : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::WideChar *FStartP;
	bool FMatched;
	System::WideChar *FEndP;
	void __fastcall SetEndP(const System::WideChar * Value);
	
public:
	void __fastcall Clear(void);
	__property System::WideChar * StartP = {read=FStartP, write=FStartP};
	__property System::WideChar * EndP = {read=FEndP, write=SetEndP};
	__property bool Matched = {read=FMatched, write=FMatched, nodefault};
public:
	/* TObject.Create */ inline __fastcall TRECapture(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRECapture(void) { }
	
};


class DELPHICLASS TGroup;
class DELPHICLASS TSkRegExp;
class PASCALIMPLEMENTATION TGroup : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSkRegExp* FRegExp;
	System::UnicodeString FGroupName;
	int FIndexBegin;
	int FIndexEnd;
	TRECapture* FCapture;
	int __fastcall GetIndex(void);
	int __fastcall GetLength(void);
	System::UnicodeString __fastcall GetStrings(void);
	bool __fastcall GetSuccess(void);
	
protected:
	void __fastcall Clear(void);
	void __fastcall Reset(void);
	
public:
	__fastcall TGroup(TSkRegExp* ARegExp);
	__fastcall virtual ~TGroup(void);
	void __fastcall Assign(TGroup* Source);
	__property System::UnicodeString GroupName = {read=FGroupName, write=FGroupName};
	__property int IndexBegin = {read=FIndexBegin, write=FIndexBegin, nodefault};
	__property int IndexEnd = {read=FIndexEnd, write=FIndexEnd, nodefault};
	__property System::UnicodeString Strings = {read=GetStrings};
	__property int Index = {read=GetIndex, nodefault};
	__property int Length = {read=GetLength, nodefault};
	__property bool Success = {read=GetSuccess, nodefault};
	__property TRECapture* Capture = {read=FCapture};
};


class DELPHICLASS TGroupCollectionEnumerator;
class PASCALIMPLEMENTATION TGroupCollectionEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FIndex;
	Contnrs::TObjectList* FList;
	
public:
	__fastcall TGroupCollectionEnumerator(Contnrs::TObjectList* AList);
	TGroup* __fastcall GetCurrent(void);
	bool __fastcall MoveNext(void);
	__property TGroup* Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TGroupCollectionEnumerator(void) { }
	
};


struct TREHashItem
{
	
public:
	void *Next;
	System::UnicodeString Key;
	int Value;
};


typedef TREHashItem *PREHashItem;

typedef StaticArray<PREHashItem, 17> TREHashArray;

typedef DynamicArray<int> TIntDynArray;

class DELPHICLASS TGroupCollection;
class PASCALIMPLEMENTATION TGroupCollection : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TGroup* operator[](int Index) { return Items[Index]; }
	
private:
	TSkRegExp* FRegExp;
	Contnrs::TObjectList* FItems;
	TREHashArray FBuckets;
	TGroup* __fastcall GetItems(int Index);
	TGroup* __fastcall GetNames(System::UnicodeString AName);
	int __fastcall GetCount(void);
	
protected:
	int __fastcall Add(const System::UnicodeString AGroupName, int AEntry, int AWayout);
	void __fastcall AddGroupName(const System::UnicodeString AGroupName, int Index);
	void __fastcall Clear(void);
	unsigned __fastcall HashOf(const System::UnicodeString Key);
	bool __fastcall IsDuplicateGroupName(const System::UnicodeString AGroupName);
	void __fastcall Reset(void);
	
public:
	__fastcall TGroupCollection(TSkRegExp* ARegExp);
	__fastcall virtual ~TGroupCollection(void);
	void __fastcall Assign(TGroupCollection* Source);
	TIntDynArray __fastcall EnumIndexOfName(const System::UnicodeString AGroupName);
	TGroupCollectionEnumerator* __fastcall GetEnumerator(void);
	int __fastcall IndexOfName(const System::UnicodeString AGroupName);
	int __fastcall IndexOfMatchedName(const System::UnicodeString AGroupName);
	__property int Count = {read=GetCount, nodefault};
	__property TGroup* Items[int Index] = {read=GetItems/*, default*/};
	__property TGroup* Names[System::UnicodeString AName] = {read=GetNames};
};


struct TRECharMapRec
{
	
public:
	System::UCS4Char Ch;
	void *Next;
};


typedef TRECharMapRec *PRECharMapRec;

class DELPHICLASS TRECharMap;
class PASCALIMPLEMENTATION TRECharMap : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	StaticArray<void *, 256> FMap;
	
public:
	__fastcall virtual ~TRECharMap(void);
	void __fastcall Add(System::UCS4Char Ch);
	void __fastcall Clear(void);
	bool __fastcall IsExists(System::WideChar * AStr);
public:
	/* TObject.Create */ inline __fastcall TRECharMap(void) : System::TObject() { }
	
};


class DELPHICLASS TRECode;
class PASCALIMPLEMENTATION TRECode : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSkRegExp* FRegExp;
	
protected:
	virtual int __fastcall GetLength(void);
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TRECode(TSkRegExp* ARegExp);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Source);
	virtual bool __fastcall ExecRepeat(System::WideChar * &AStr, bool IsStar)/* overload */;
	virtual bool __fastcall ExecRepeat(System::WideChar * &AStr, int AMin, int AMax)/* overload */;
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
	__property int Length = {read=GetLength, nodefault};
	__property int CharLength = {read=GetCharLength, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRECode(void) { }
	
};


class DELPHICLASS TRECharCode;
class PASCALIMPLEMENTATION TRECharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	System::UnicodeString FStrings;
	System::WideChar *FSubP;
	int FLength;
	int FCharLength;
	TREOptions FOptions;
	TRECompareOptions FCompareOptions;
	bool FConvert;
	
protected:
	virtual int __fastcall GetCharLength(void);
	virtual int __fastcall GetLength(void);
	
public:
	__fastcall TRECharCode(TSkRegExp* ARegExp, System::UCS4Char AWChar, TREOptions AOptions, bool AConvert);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall ExecRepeat(System::WideChar * &AStr, bool IsStar)/* overload */;
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	System::UCS4Char __fastcall GetWChar(void);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRECharCode(void) { }
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  ExecRepeat(System::WideChar * &AStr, int AMin, int AMax){ return TRECode::ExecRepeat(AStr, AMin, AMax); }
	
};


class DELPHICLASS TRELiteralCode;
class PASCALIMPLEMENTATION TRELiteralCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	System::UnicodeString FStrings;
	System::WideChar *FSubP;
	int FLength;
	int FCharLength;
	TREOptions FOptions;
	TRECompareOptions FCompareOptions;
	
protected:
	virtual int __fastcall GetCharLength(void);
	virtual int __fastcall GetLength(void);
	
public:
	__fastcall TRELiteralCode(TSkRegExp* ARegExp, System::UCS4String Str, TREOptions AOptions)/* overload */;
	__fastcall TRELiteralCode(TSkRegExp* ARegExp, System::UnicodeString Str, TREOptions AOptions)/* overload */;
	virtual bool __fastcall ExecRepeat(System::WideChar * &AStr, bool IsStar)/* overload */;
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRELiteralCode(void) { }
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  ExecRepeat(System::WideChar * &AStr, int AMin, int AMax){ return TRECode::ExecRepeat(AStr, AMin, AMax); }
	
};


class DELPHICLASS TRERangeCharCode;
class PASCALIMPLEMENTATION TRERangeCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	System::UCS4Char FStartWChar;
	System::UCS4Char FLastWChar;
	TREOptions FOptions;
	TRECompareOptions FCompareOptions;
	
public:
	__fastcall TRERangeCharCode(TSkRegExp* ARegExp, System::UCS4Char AStartWChar, System::UCS4Char ALastWChar, TREOptions AOptions);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRERangeCharCode(void) { }
	
};


class DELPHICLASS TREAnyCharCode;
class PASCALIMPLEMENTATION TREAnyCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	TREOptions FOptions;
	TRECompareOptions FCompareOptions;
	
public:
	__fastcall TREAnyCharCode(TSkRegExp* ARegExp, TREOptions AOptions);
	virtual bool __fastcall ExecRepeat(System::WideChar * &AStr, bool IsStar)/* overload */;
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREAnyCharCode(void) { }
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  ExecRepeat(System::WideChar * &AStr, int AMin, int AMax){ return TRECode::ExecRepeat(AStr, AMin, AMax); }
	
};


class DELPHICLASS TREWordCharCode;
class PASCALIMPLEMENTATION TREWordCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	bool FNegative;
	
public:
	__fastcall TREWordCharCode(TSkRegExp* ARegExp, bool ANegative);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREWordCharCode(void) { }
	
};


class DELPHICLASS TREDigitCharCode;
class PASCALIMPLEMENTATION TREDigitCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	bool FNegative;
	
public:
	__fastcall TREDigitCharCode(TSkRegExp* ARegExp, bool ANegative);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREDigitCharCode(void) { }
	
};


class DELPHICLASS TREHexDigitCharCode;
class PASCALIMPLEMENTATION TREHexDigitCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	bool FNegative;
	
public:
	__fastcall TREHexDigitCharCode(TSkRegExp* ARegExp, bool ANegative);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREHexDigitCharCode(void) { }
	
};


class DELPHICLASS TRESpaceCharCode;
class PASCALIMPLEMENTATION TRESpaceCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	bool FNegative;
	
public:
	__fastcall TRESpaceCharCode(TSkRegExp* ARegExp, bool ANegative);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRESpaceCharCode(void) { }
	
};


class DELPHICLASS TREHorizontalSpaceCharCode;
class PASCALIMPLEMENTATION TREHorizontalSpaceCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	bool FNegative;
	
public:
	__fastcall TREHorizontalSpaceCharCode(TSkRegExp* ARegExp, bool ANegative);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREHorizontalSpaceCharCode(void) { }
	
};


class DELPHICLASS TREVerticalSpaceCharCode;
class PASCALIMPLEMENTATION TREVerticalSpaceCharCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	bool FNegative;
	
public:
	__fastcall TREVerticalSpaceCharCode(TSkRegExp* ARegExp, bool ANegative);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREVerticalSpaceCharCode(void) { }
	
};


class DELPHICLASS TRELineBreakCharCode;
class PASCALIMPLEMENTATION TRELineBreakCharCode : public TRECode
{
	typedef TRECode inherited;
	
protected:
	virtual int __fastcall GetCharLength(void);
	virtual int __fastcall GetLength(void);
	
public:
	__fastcall TRELineBreakCharCode(TSkRegExp* ARegExp);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRELineBreakCharCode(void) { }
	
};


class DELPHICLASS TRECharClassCode;
class PASCALIMPLEMENTATION TRECharClassCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	TRECharMap* FMap;
	bool FNegative;
	Contnrs::TObjectList* FCodeList;
	TREOptions FOptions;
	bool FIsSimple;
	
public:
	__fastcall TRECharClassCode(TSkRegExp* ARegExp, bool ANegative, TREOptions AOptions);
	__fastcall virtual ~TRECharClassCode(void);
	int __fastcall Add(System::UCS4Char AWChar)/* overload */;
	int __fastcall Add(System::UCS4Char AStartWChar, System::UCS4Char ALastWChar)/* overload */;
	int __fastcall Add(TRECode* Value)/* overload */;
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual bool __fastcall IsOverlap(TRECode* ACode);
	void __fastcall Rebuild(void);
	void __fastcall Sort(void);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
};


class DELPHICLASS TRECombiningSequence;
class PASCALIMPLEMENTATION TRECombiningSequence : public TRECode
{
	typedef TRECode inherited;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	virtual bool __fastcall ExecRepeat(System::WideChar * &AStr, bool IsStar)/* overload */;
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TRECode.Create */ inline __fastcall TRECombiningSequence(TSkRegExp* ARegExp) : TRECode(ARegExp) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRECombiningSequence(void) { }
	
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  ExecRepeat(System::WideChar * &AStr, int AMin, int AMax){ return TRECode::ExecRepeat(AStr, AMin, AMax); }
	
};


class DELPHICLASS TREBoundaryCode;
class PASCALIMPLEMENTATION TREBoundaryCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	bool FNegative;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TREBoundaryCode(TSkRegExp* ARegExp, bool ANegative);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREBoundaryCode(void) { }
	
};


class DELPHICLASS TREReferenceCode;
class PASCALIMPLEMENTATION TREReferenceCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	int FGroupIndex;
	TREOptions FOptions;
	TRECompareOptions FCompareOptions;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TREReferenceCode(TSkRegExp* ARegExp, int AGroupIndex, TREOptions AOptions)/* overload */;
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREReferenceCode(void) { }
	
};


class DELPHICLASS TRENamedReferenceCode;
class PASCALIMPLEMENTATION TRENamedReferenceCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	System::UnicodeString FGroupName;
	TIntDynArray FGroupIndexArray;
	int FCount;
	TREOptions FOptions;
	TRECompareOptions FCompareOptions;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TRENamedReferenceCode(TSkRegExp* ARegExp, System::UnicodeString AGroupName, TIntDynArray AGroupIndexArray, TREOptions AOptions);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRENamedReferenceCode(void) { }
	
};


class DELPHICLASS TRELineHeadCode;
class PASCALIMPLEMENTATION TRELineHeadCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	TREOptions FOptions;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TRELineHeadCode(TSkRegExp* ARegExp, TREOptions AOptions);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRELineHeadCode(void) { }
	
};


class DELPHICLASS TRELineTailCode;
class PASCALIMPLEMENTATION TRELineTailCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	TREOptions FOptions;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TRELineTailCode(TSkRegExp* ARegExp, TREOptions AOptions);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRELineTailCode(void) { }
	
};


class DELPHICLASS TRETextHeadCode;
class PASCALIMPLEMENTATION TRETextHeadCode : public TRECode
{
	typedef TRECode inherited;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TRECode.Create */ inline __fastcall TRETextHeadCode(TSkRegExp* ARegExp) : TRECode(ARegExp) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRETextHeadCode(void) { }
	
};


class DELPHICLASS TRETextTailCode;
class PASCALIMPLEMENTATION TRETextTailCode : public TRECode
{
	typedef TRECode inherited;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TRECode.Create */ inline __fastcall TRETextTailCode(TSkRegExp* ARegExp) : TRECode(ARegExp) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRETextTailCode(void) { }
	
};


class DELPHICLASS TRETextEndCode;
class PASCALIMPLEMENTATION TRETextEndCode : public TRECode
{
	typedef TRECode inherited;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TRECode.Create */ inline __fastcall TRETextEndCode(TSkRegExp* ARegExp) : TRECode(ARegExp) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TRETextEndCode(void) { }
	
};


class DELPHICLASS TREPropertyCode;
class PASCALIMPLEMENTATION TREPropertyCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	Unicodeprop::TUnicodeProperty FUniCodeProperty;
	bool FNegative;
	
public:
	__fastcall TREPropertyCode(TSkRegExp* ARegExp, Unicodeprop::TUnicodeProperty AUnicodeProperty, bool ANegative);
	virtual int __fastcall Compare(System::WideChar * AStr);
	virtual int __fastcall CompareCode(TRECode* Dest);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREPropertyCode(void) { }
	
};


class DELPHICLASS TREGlobalPosCode;
class PASCALIMPLEMENTATION TREGlobalPosCode : public TRECode
{
	typedef TRECode inherited;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TRECode.Create */ inline __fastcall TREGlobalPosCode(TSkRegExp* ARegExp) : TRECode(ARegExp) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREGlobalPosCode(void) { }
	
};


class DELPHICLASS TREIfThenReferenceCode;
class PASCALIMPLEMENTATION TREIfThenReferenceCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	int FGroupIndex;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TREIfThenReferenceCode(TSkRegExp* ARegExp, const int AGroupIndex);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREIfThenReferenceCode(void) { }
	
};


class DELPHICLASS TREIfThenNamedReferenceCode;
class PASCALIMPLEMENTATION TREIfThenNamedReferenceCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	System::UnicodeString FGroupName;
	
protected:
	virtual int __fastcall GetCharLength(void);
	
public:
	__fastcall TREIfThenNamedReferenceCode(TSkRegExp* ARegExp, const System::UnicodeString AGroupName);
	virtual bool __fastcall IsEqual(System::WideChar * AStr, int &Len);
	virtual bool __fastcall IsInclude(TRECode* ACode);
	virtual System::UnicodeString __fastcall GetDebugStr(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREIfThenNamedReferenceCode(void) { }
	
};


class DELPHICLASS TREBinCode;
class PASCALIMPLEMENTATION TREBinCode : public TRECode
{
	typedef TRECode inherited;
	
private:
	TREOperator FOp;
	TRECode* FLeft;
	TRECode* FRight;
	int FGroupIndex;
	int FMin;
	int FMax;
	TRELoopKind FMatchKind;
	System::UnicodeString FGroupName;
	bool FHasRecursion;
	
public:
	__fastcall TREBinCode(TSkRegExp* ARegExp, TREOperator AOp, TRECode* ALeft, TRECode* ARight, int AMin, int AMax)/* overload */;
	__property TREOperator Op = {read=FOp, nodefault};
	__property TRECode* Left = {read=FLeft};
	__property TRECode* Right = {read=FRight};
	__property int Min = {read=FMin, nodefault};
	__property int Max = {read=FMax, nodefault};
	__property int GroupIndex = {read=FGroupIndex, write=FGroupIndex, nodefault};
	__property System::UnicodeString GroupName = {read=FGroupName, write=FGroupName};
	__property TRELoopKind MatchKind = {read=FMatchKind, write=FMatchKind, nodefault};
	__property bool HasRecursion = {read=FHasRecursion, write=FHasRecursion, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TREBinCode(void) { }
	
};


#pragma option push -b-
enum TRELexMode { lmOptimize, lmNormal };
#pragma option pop

#pragma option push -b-
enum TREContextKind { ctNormal, ctCharClass, ctNegativeCharClass, ctQuote };
#pragma option pop

struct TRELexRec
{
	
public:
	bool FStored;
	TREToken FToken;
	TREOptions FOptions;
	TREOptions FNewOptions;
	System::WideChar *FP;
	System::WideChar *FTokenStartP;
	System::WideChar *FTopP;
	System::UCS4Char FWChar;
	System::UCS4Char FStartWChar;
	System::UCS4Char FLastWChar;
	int FMin;
	int FMax;
	int FLevel;
	TREContextKind FContext;
	Unicodeprop::TUnicodeProperty FUniCodeProperty;
	bool FConvert;
	bool FNoBackTrack;
	System::UnicodeString FGroupName;
	Classes::TList* FOptionList;
	bool FIsQuote;
};


class DELPHICLASS TRELex;
class PASCALIMPLEMENTATION TRELex : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	typedef StaticArray<TRELexRec, 3> _TRELex__1;
	
	
private:
	TSkRegExp* FRegExp;
	TREToken FToken;
	System::WideChar *FP;
	System::WideChar *FTokenStartP;
	System::WideChar *FTopP;
	System::WideChar *FLastP;
	System::UCS4Char FWChar;
	System::UCS4Char FStartWChar;
	System::UCS4Char FLastWChar;
	int FMin;
	int FMax;
	int FLevel;
	TREContextKind FContext;
	Unicodeprop::TUnicodeProperty FUniCodeProperty;
	bool FConvert;
	bool FIsQuote;
	System::UnicodeString FGroupName;
	TREOptions FOptions;
	TREOptions FNewOptions;
	Classes::TList* FOptionList;
	_TRELex__1 FPrevLex;
	int FPrevCount;
	
protected:
	void __fastcall Error(const System::UnicodeString Msg, const System::UnicodeString Prefix = L"...")/* overload */;
	void __fastcall Error(const System::UnicodeString Msg, int APosition)/* overload */;
	System::UnicodeString __fastcall GetErrorPositionString(int APosition);
	void __fastcall SkipWhiteSpace(void);
	void __fastcall LexCharClass(void);
	void __fastcall LexOption(void);
	System::UCS4Char __fastcall GetControlCode(int &Len);
	int __fastcall GetDigit(int &Len);
	System::UCS4Char __fastcall GetHexDigit(int &Len);
	System::UCS4Char __fastcall GetOctalDigit(int &Len);
	void __fastcall LexBrace(void);
	void __fastcall LexProperty(const bool CheckNegative);
	void __fastcall LexGroupName(const System::WideChar LastDelimiter);
	void __fastcall LexReference(const System::WideChar LastDelimiter);
	void __fastcall LexGoSub(const System::WideChar LastDelimiter);
	void __fastcall LexEscChar(void);
	void __fastcall LexLeftPar(void);
	void __fastcall PushOptions(void);
	void __fastcall PopOptions(void);
	void __fastcall UpdateOptions(void);
	void __fastcall ClearOptionList(void);
	TRECompareOptions __fastcall GetRECompareOptions(void);
	
public:
	__fastcall TRELex(TSkRegExp* ARegExp, const System::UnicodeString Expression);
	__fastcall virtual ~TRELex(void);
	void __fastcall Assign(TRELex* Source);
	int __fastcall GetCompileErrorPos(void);
	void __fastcall CharNext(System::WideChar * &P, const int Len = 0x1);
	void __fastcall CharPrev(System::WideChar * &P, const int Len = 0x1);
	void __fastcall GetToken(bool Skip = false);
	void __fastcall PushToken(void);
	void __fastcall Save(void);
	__property TREToken Token = {read=FToken, nodefault};
	__property int Min = {read=FMin, nodefault};
	__property int Max = {read=FMax, nodefault};
	__property int Level = {read=FLevel, nodefault};
	__property TREOptions Options = {read=FOptions, nodefault};
	__property System::UCS4Char WChar = {read=FWChar, nodefault};
	__property System::UCS4Char StartWChar = {read=FStartWChar, nodefault};
	__property System::UCS4Char LastWChar = {read=FLastWChar, nodefault};
	__property Unicodeprop::TUnicodeProperty UnicodeProperty = {read=FUniCodeProperty, nodefault};
	__property bool Convert = {read=FConvert, nodefault};
	__property System::WideChar * TokenStartP = {read=FTokenStartP};
	__property System::UnicodeString GroupName = {read=FGroupName};
};


struct TReferenceErrorRec
{
	
public:
	int ErrorPos;
	#pragma pack(push,1)
	
public:
	bool IsRelative;
	union
	{
		struct 
		{
			unsigned:24;
			int GroupIndex;
			
		};
		struct 
		{
			unsigned:24;
			int RelativeGourpIndex;
			
		};
		
	};
	#pragma pack(pop)
};


typedef TReferenceErrorRec *PReferenceErrorRec;

class DELPHICLASS TREParser;
class PASCALIMPLEMENTATION TREParser : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSkRegExp* FRegExp;
	TRELex* FLex;
	int FCurrentGroup;
	int FGroupLevel;
	int FGroupCount;
	bool FHasRecursion;
	Classes::TStrings* FReferenceErrorList;
	Classes::TStrings* FGoSubErrorList;
	Contnrs::TStack* FGroupStack;
	
protected:
	TRECode* __fastcall NewBinCode(TREOperator AOperator, TRECode* ALeft, TRECode* ARight, int AMin = 0x0, int AMax = 0x0);
	TRECode* __fastcall NewCharClassCode(bool ANegative);
	TRECode* __fastcall Term(void);
	TRECode* __fastcall Factor(void);
	TRECode* __fastcall Primay(void);
	TRECode* __fastcall RegExpr(void);
	
public:
	__fastcall TREParser(TSkRegExp* ARegExp, const System::UnicodeString Expression);
	__fastcall virtual ~TREParser(void);
	void __fastcall Parse(void);
};


class DELPHICLASS TRENFAState;
class PASCALIMPLEMENTATION TRENFAState : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TRENFAKind FKind;
	TRECode* FCode;
	int FTransitTo;
	TRENFAState* FNext;
	int FGroupIndex;
	int FMin;
	int FMax;
	TRELoopKind FMatchKind;
	int FExtendTo;
	bool FHasRecursion;
	int FIndex;
	
public:
	__property int Index = {read=FIndex, write=FIndex, nodefault};
	__property TRECode* Code = {read=FCode, write=FCode};
	__property int TransitTo = {read=FTransitTo, write=FTransitTo, nodefault};
	__property TRENFAState* Next = {read=FNext, write=FNext};
	__property TRENFAKind Kind = {read=FKind, write=FKind, nodefault};
	__property int GroupIndex = {read=FGroupIndex, write=FGroupIndex, nodefault};
	__property TRELoopKind MatchKind = {read=FMatchKind, write=FMatchKind, nodefault};
	__property int Min = {read=FMin, write=FMin, nodefault};
	__property int Max = {read=FMax, write=FMax, nodefault};
	__property int ExtendTo = {read=FExtendTo, write=FExtendTo, nodefault};
	__property bool HasRecursion = {read=FHasRecursion, write=FHasRecursion, nodefault};
	System::UnicodeString __fastcall GetString(void);
public:
	/* TObject.Create */ inline __fastcall TRENFAState(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRENFAState(void) { }
	
};


class DELPHICLASS TRENFA;
class PASCALIMPLEMENTATION TRENFA : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSkRegExp* FRegExp;
	Classes::TList* FStateList;
	int FBEntryState;
	int FBExitState;
	Classes::TList* FEntryStack;
	Classes::TList* FExitStack;
	int FEntryStackIndex;
	int FExitStateIndex;
	Classes::TList* FStateStack;
	int FStateStackIndex;
	int FGroupCount;
	
protected:
	int __fastcall GetNumber(void);
	void __fastcall AddTransition(TRENFAKind AKind, int ATransFrom, int ATransTo, TRECode* ACode, int AMin = 0x0, int AMax = 0x0);
	void __fastcall GenerateStateList(TRECode* ACode, int AEntry, int AWayout);
	void __fastcall ReplaceCode(TRECode* &OldCode, TRECode* &NewCode);
	void __fastcall PushState(int AEntry, int AWayout, int ANewEntry, int ANewWayout);
	void __fastcall PopState(void);
	int __fastcall GetRealState(void);
	
public:
	__fastcall TRENFA(TSkRegExp* ARegExp);
	__fastcall virtual ~TRENFA(void);
	void __fastcall Compile(void);
};


struct TREMatchExplosionStateRec
{
	
public:
	TRENFAState* NFACode;
	void *Next;
};


typedef TREMatchExplosionStateRec *PREMatchExplosionStateRec;

struct TREBackTrackStackRec
{
	
public:
	TRENFAState* NFACode;
	System::WideChar *Str;
};


typedef TREBackTrackStackRec *PREBackTrackStackRec;

typedef StaticArray<void *, 134217727> TPointerList;

typedef TPointerList *PPointerList;

class DELPHICLASS TREStack;
class PASCALIMPLEMENTATION TREStack : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSkRegExp* FRegExp;
	int FCount;
	int FSize;
	TPointerList *FStat;
	TPointerList *FGroup;
	bool FCheckMatchExplosion;
	
protected:
	void __fastcall Extend(int ASize);
	
public:
	__fastcall TREStack(TSkRegExp* ARegExp, bool ACheckMatchExplosion);
	__fastcall virtual ~TREStack(void);
	void __fastcall Clear(void);
	int __fastcall Count(void);
	TRENFAState* __fastcall Peek(void);
	int __fastcall Index(void);
	void __fastcall Push(TRENFAState* NFACode, System::WideChar * AStr, bool IsPushGroup)/* overload */;
	void __fastcall Pop(TRENFAState* &NFACode, System::WideChar * &AStr);
	void __fastcall Remove(const int AIndex);
};


class DELPHICLASS TRELeadCode;
class PASCALIMPLEMENTATION TRELeadCode : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TRECode* FCode;
	int FOffset;
	bool FIsBehindMatch;
	
public:
	__property TRECode* Code = {read=FCode, write=FCode};
	__property int Offset = {read=FOffset, write=FOffset, nodefault};
	__property bool IsBehindMatch = {read=FIsBehindMatch, write=FIsBehindMatch, nodefault};
public:
	/* TObject.Create */ inline __fastcall TRELeadCode(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRELeadCode(void) { }
	
};


class DELPHICLASS TRELeadCodeCollection;
class PASCALIMPLEMENTATION TRELeadCodeCollection : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TRELeadCode* operator[](int Index) { return Items[Index]; }
	
private:
	Contnrs::TObjectList* FList;
	TRELeadCode* __fastcall GetItem(int Index);
	int __fastcall GetCount(void);
	
public:
	__fastcall TRELeadCodeCollection(void);
	__fastcall virtual ~TRELeadCodeCollection(void);
	void __fastcall Clear(void);
	int __fastcall Add(TRECode* Value, int AOffset, bool ABehindMatch);
	void __fastcall Delete(int Index);
	__property int Count = {read=GetCount, nodefault};
	__property TRELeadCode* Items[int Index] = {read=GetItem/*, default*/};
};


#pragma option push -b-
enum TRELeadCharMode { lcmNone, lcmFirstLiteral, lcmSimple, lcmTextTop, lcmLineTop, lcmLastLiteral, lcmHasLead, lcmMap };
#pragma option pop

class DELPHICLASS TREMatchEngine;
class PASCALIMPLEMENTATION TREMatchEngine : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSkRegExp* FRegExp;
	TGroupCollection* FGroups;
	Classes::TList* FStateList;
	TRELeadCodeCollection* FLeadCode;
	Contnrs::TObjectList* FTailCode;
	TREQuickSearch* FLeadStrings;
	bool FIsNotSimplePattern;
	bool FIsPreMatch;
	TRELeadCharMode FLeadCharMode;
	TRECharMap* FMap;
	int FPreMatchLength;
	bool FIsBehindMatch;
	Classes::TList* FSpecialMatchStack;
	
protected:
	void __fastcall GenerateLeadCode(void);
	void __fastcall GenerateTailCode(void);
	bool __fastcall MatchCore(TRENFAState* &NFACode, System::WideChar * &AStr)/* overload */;
	bool __fastcall MatchCore(TRENFAState* &NFACode, TRENFAState* &EndCode, System::WideChar * &AStr, bool ACheckExplosion = true)/* overload */;
	bool __fastcall MatchEntry(System::WideChar * &AStr);
	bool __fastcall MatchRecursion(TRENFAState* &NFACode, TRENFAState* EndCode, System::WideChar * &AStr);
	TRENFAState* __fastcall MatchPrim(TRENFAState* NFACode, System::WideChar * &AStr, TREStack* Stack);
	void __fastcall OptimizeLoop(void);
	bool __fastcall IsLeadStrings(System::WideChar * &AStr);
	void __fastcall SetupLeadStrings(void);
	
public:
	__fastcall TREMatchEngine(TSkRegExp* ARegExp);
	__fastcall virtual ~TREMatchEngine(void);
	bool __fastcall Match(System::WideChar * AStr);
	void __fastcall Optimize(void);
};


typedef bool __fastcall (*TRECharTypeFunc)(System::UCS4Char W);

typedef System::UnicodeString __fastcall (__closure *TSkRegExpReplaceFunction)(TSkRegExp* ARegExp);

typedef void __fastcall (__closure *TSkRegExpReplaceEvent)(System::TObject* Sender, System::UnicodeString &ReplaceWith);

class PASCALIMPLEMENTATION TSkRegExp : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	typedef DynamicArray<PREMatchExplosionStateRec> _TSkRegExp__1;
	
	
private:
	TREMatchEngine* FMatchEngine;
	TRECode* FCode;
	Classes::TList* FCodeList;
	Classes::TList* FBinCodeList;
	bool FCompiled;
	System::WideChar *FTextTopP;
	System::WideChar *FTextEndP;
	System::WideChar *FMatchTopP;
	System::WideChar *FMatchEndP;
	System::UnicodeString FEOL;
	System::WideChar *FEOLHeadP;
	System::WideChar *FEOLTailP;
	int FEOLLen;
	TGroupCollection* FGroups;
	System::UnicodeString FInputString;
	System::UnicodeString FExpression;
	TREOptions FOptions;
	_TSkRegExp__1 FMatchExplosionState;
	Classes::TList* FStateList;
	int FEntryState;
	int FExitState;
	Classes::TNotifyEvent FOnMatch;
	TRELexMode FLexMode;
	System::WideChar *FGlobalStartP;
	System::WideChar *FGlobalEndP;
	bool FSuccess;
	TSkRegExpReplaceFunction FReplaceFunc;
	TSkRegExpReplaceEvent FOnReplace;
	void __fastcall SetExpression(const System::UnicodeString Value);
	void __fastcall SetEOL(const System::UnicodeString Value);
	void __fastcall SetInputString(const System::UnicodeString Value);
	int __fastcall GetGroupCount(void);
	System::UnicodeString __fastcall GetVersion(void);
	bool __fastcall GetOptions(const int Index);
	void __fastcall SetOptions(const int Index, const bool Value);
	System::UnicodeString __fastcall GetMatchStr(int Index);
	int __fastcall GetMatchLen(int Index);
	int __fastcall GetMatchPos(int Index);
	System::UnicodeString __fastcall GetNamedGroupStr(System::UnicodeString Name);
	int __fastcall GetNamedGroupPos(System::UnicodeString Name);
	int __fastcall GetNamedGroupLen(System::UnicodeString Name);
	void __fastcall SetIgnoreZenHan(const bool Value);
	bool __fastcall GetIgnoreZenHan(void);
	bool __fastcall GetDefineCharClassLegacy(void);
	void __fastcall SetDefineCharClassLegacy(const bool Value);
	void __fastcall SetLexMode(const TRELexMode Value);
	System::UnicodeString __fastcall GetGroupNameFromIndex(int Index);
	int __fastcall GetIndexFromGroupName(System::UnicodeString Name);
	
protected:
	TRECharTypeFunc IsWord;
	TRECharTypeFunc IsDigit;
	TRECharTypeFunc IsSpace;
	void __fastcall ClearCodeList(void);
	void __fastcall ClearBinCodeList(void);
	bool __fastcall IsEOL(System::WideChar * AStr, /* out */ int &Len);
	void __fastcall ClearStateList(void);
	void __fastcall ClearExplosionState(void);
	void __fastcall Error(const System::UnicodeString ErrorMes);
	bool __fastcall MatchCore(System::WideChar * AStr);
	void __fastcall DoReplaceFunc(System::TObject* Sender, System::UnicodeString &ReplaceWith);
	
public:
	__fastcall TSkRegExp(void);
	__fastcall virtual ~TSkRegExp(void);
	void __fastcall Compile(void);
	bool __fastcall Exec(const System::UnicodeString AInputStr);
	bool __fastcall ExecNext(void);
	bool __fastcall ExecPos(int AOffset = 0x1, int AMaxLength = 0x0);
	System::UnicodeString __fastcall Substitute(const System::UnicodeString ATemplate);
	System::UnicodeString __fastcall Replace(const System::UnicodeString Input, const System::UnicodeString Replacement, int Count = 0x0, int AOffset = 0x1)/* overload */;
	System::UnicodeString __fastcall Replace(const System::UnicodeString Input, TSkRegExpReplaceFunction AReplaceFunc, int Count = 0x0, int AOffset = 0x1)/* overload */;
	void __fastcall Split(const System::UnicodeString Input, Classes::TStrings* APieces, int Count = 0x0, int AOffset = 0x1);
	__classmethod bool __fastcall RegIsMatch(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, TREOptions AOptions = TREOptions() );
	__classmethod bool __fastcall RegMatch(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, Classes::TStrings* AMatches, TREOptions AOptions = TREOptions() );
	__classmethod System::UnicodeString __fastcall RegReplace(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, const System::UnicodeString AReplaceStr, TREOptions AOptions = TREOptions() )/* overload */;
	__classmethod System::UnicodeString __fastcall RegReplace(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, TSkRegExpReplaceFunction AReplaceFunc, TREOptions AOptions = TREOptions() )/* overload */;
	__classmethod void __fastcall RegSplit(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, Classes::TStrings* APieces, TREOptions AOptions = TREOptions() );
	__classmethod System::UnicodeString __fastcall DecodeEscape(const System::UnicodeString S);
	__classmethod System::UnicodeString __fastcall EncodeEscape(const System::UnicodeString Str);
	void __fastcall DumpParse(Comctrls::TTreeView* TreeView);
	void __fastcall DumpNFA(Classes::TStrings* ADest);
	System::UnicodeString __fastcall DumpLeadCode(void);
	void __fastcall DumpMatchProcess(Classes::TStrings* ADest);
	__property System::UnicodeString Expression = {read=FExpression, write=SetExpression};
	__property System::UnicodeString EOL = {read=FEOL, write=SetEOL};
	__property int GroupCount = {read=GetGroupCount, nodefault};
	__property System::UnicodeString InputString = {read=FInputString, write=SetInputString};
	__property TREOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property bool IgnoreCase = {read=GetOptions, write=SetOptions, index=0, nodefault};
	__property bool MultiLine = {read=GetOptions, write=SetOptions, index=1, nodefault};
	__property bool NamedGroupOnly = {read=GetOptions, write=SetOptions, index=2, nodefault};
	__property bool SingleLine = {read=GetOptions, write=SetOptions, index=3, nodefault};
	__property bool Extended = {read=GetOptions, write=SetOptions, index=4, nodefault};
	__property bool IgnoreWidth = {read=GetOptions, write=SetOptions, index=5, nodefault};
	__property bool IgnoreKana = {read=GetOptions, write=SetOptions, index=6, nodefault};
	__property bool IgnoreZenHan = {read=GetIgnoreZenHan, write=SetIgnoreZenHan, nodefault};
	__property bool DefinedCharClassLegacy = {read=GetDefineCharClassLegacy, write=SetDefineCharClassLegacy, nodefault};
	__property TGroupCollection* Groups = {read=FGroups};
	__property System::UnicodeString Match[int Index] = {read=GetMatchStr};
	__property int MatchPos[int Index] = {read=GetMatchPos};
	__property int MatchLen[int Index] = {read=GetMatchLen};
	__property System::UnicodeString NamedGroup[System::UnicodeString Name] = {read=GetNamedGroupStr};
	__property int NamedGroupPos[System::UnicodeString Name] = {read=GetNamedGroupPos};
	__property int NamedGroupLen[System::UnicodeString Name] = {read=GetNamedGroupLen};
	__property System::UnicodeString GroupNameFromIndex[int Index] = {read=GetGroupNameFromIndex};
	__property int IndexFromGroupName[System::UnicodeString Name] = {read=GetIndexFromGroupName};
	__property System::UnicodeString Version = {read=GetVersion};
	__property TRELexMode LexMode = {read=FLexMode, write=SetLexMode, nodefault};
	__property bool Success = {read=FSuccess, nodefault};
	__property Classes::TNotifyEvent OnMatch = {read=FOnMatch, write=FOnMatch};
	__property TSkRegExpReplaceEvent OnReplace = {read=FOnReplace, write=FOnReplace};
};


//-- var, const, procedure ---------------------------------------------------
static const int MaxListSize = 0x7ffffff;
extern PACKAGE TREOptions SkRegExpDefaultOptions;
extern PACKAGE bool __fastcall RegIsMatch(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, TREOptions AOptions = TREOptions() );
extern PACKAGE bool __fastcall RegMatch(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, Classes::TStrings* AMatches, TREOptions AOptions = TREOptions() );
extern PACKAGE System::UnicodeString __fastcall RegReplace(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, const System::UnicodeString AReplaceStr, TREOptions AOptions = TREOptions() )/* overload */;
extern PACKAGE System::UnicodeString __fastcall RegReplace(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, TSkRegExpReplaceFunction AReplaceFunc, TREOptions AOptions = TREOptions() )/* overload */;
extern PACKAGE void __fastcall RegSplit(const System::UnicodeString ARegExpStr, const System::UnicodeString AInputStr, Classes::TStrings* APieces, TREOptions AOptions = TREOptions() );
extern PACKAGE System::UnicodeString __fastcall DecodeEscape(const System::UnicodeString S);
extern PACKAGE System::UnicodeString __fastcall EncodeEscape(const System::UnicodeString Str);
extern PACKAGE System::UCS4Char __fastcall ToUCS4Char(System::WideChar * AStr);
extern PACKAGE int __fastcall REStrLComp(System::WideChar * Str1, System::WideChar * Str2, unsigned MaxLen);
extern PACKAGE int __fastcall REStrLJComp(System::WideChar * AStr, System::WideChar * ASubStr, int ALen, TRECompareOptions AOptions);
extern PACKAGE int __fastcall REStrLIComp(System::WideChar * Str1, System::WideChar * Str2, unsigned MaxLen);
extern PACKAGE int __fastcall RECompareString(System::WideChar * SourceP, System::WideChar * DestP, int DestLen, TRECompareOptions Options);
extern PACKAGE System::WideChar * __fastcall REStrPos(System::WideChar * AStr, int ALen, System::WideChar * APattern, int APatternLen, TRECompareOptions AOptions);

}	/* namespace Skregexpw */
using namespace Skregexpw;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SkregexpwHPP

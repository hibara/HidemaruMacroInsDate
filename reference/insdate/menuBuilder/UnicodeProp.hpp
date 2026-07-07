// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Unicodeprop.pas' rev: 21.00

#ifndef UnicodepropHPP
#define UnicodepropHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Inifiles.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Unicodeprop
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TUnicodeProperty { upAlnum, upAlpha, upAscii, upBlank, upCntrl, upDigit, upGraph, upLower, upPrint, upUpper, upPunct, upSpace, upXdigit, upWord, upAny, upAssigned, upC, upL, upM, upN, upP, upS, upZ, upCc, upCf, upCn, upCo, upCs, upLC, upLl, upLm, upLo, upLt, upLu, upLamp, upMc, upMe, upMn, upNd, upNl, upNo, upPc, upPd, upPe, upPf, upPi, upPo, upPs, upSc, upSk, upSm, upSo, upZl, upZp, upZs, upunKnown, upArabic, upImperialAramaic, upArmenian, upAvestan, upBalinese, upBamum, upBengali, upBopomofo, upBraille, upBuginese, upBuhid, upCanadianAboriginal, upCarian, upCham, upCherokee, upCoptic, upCypriot, upCyrillic, upDevanagari, upDeseret, upEgyptianHieroglyphs, upEthiopic, upGeorgian, upGlagolitic, upGothic, upGreek, upGujarati, upGurmukhi, upHangul, upHan, upHanunoo, upHebrew, upHiragana, upKatakanaOrHiragana, upOldItalic, upJavanese, upKayahLi, upKatakana, upKharoshthi, upKhmer, upKannada, upKaithi, upTaiTham, upLao, upLatin, upLepcha, upLimbu, upLinearB, upLisu, upLycian, upLydian, upMalayalam, 
	upMongolian, upMeeteiMayek, upMyanmar, upNko, upOgham, upOlChiki, upOldTurkic, upOriya, upOsmanya, upPhagsPa, upInscriptionalPahlavi, upPhoenician, upInscriptionalParthian, upRejang, upRunic, upSamaritan, upOldSouthArabian, upSaurashtra, upShavian, upSinhala, upSundanese, upSylotiNagri, upSyriac, upTagbanwa, upTaiLe, upNewTaiLue, upTamil, upTaiViet, upTelugu, upTifinagh, upTagalog, upThaana, upThai, upTibetan, upUgaritic, upVai, upOldPersian, upCuneiform, upYi, upInherited, upCommon, upInBasicLatin, upInLatin1Supplement, upInLatinExtendedA, upInLatinExtendedB, upInIPAExtensions, upInSpacingModifierLetters, upInCombiningDiacriticalMarks, upInGreekandCoptic, upInCyrillic, upInCyrillicSupplement, upInArmenian, upInHebrew, upInArabic, upInSyriac, upInArabicSupplement, upInThaana, upInNKo, upInSamaritan, upInDevanagari, upInBengali, upInGurmukhi, upInGujarati, upInOriya, upInTamil, upInTelugu, upInKannada, upInMalayalam, upInSinhala, upInThai, upInLao, upInTibetan, upInMyanmar, upInGeorgian, upInHangulJamo, upInEthiopic, 
	upInEthiopicSupplement, upInCherokee, upInUnifiedCanadianAboriginalSyllabics, upInOgham, upInRunic, upInTagalog, upInHanunoo, upInBuhid, upInTagbanwa, upInKhmer, upInMongolian, upInUnifiedCanadianAboriginalSyllabicsExtended, upInLimbu, upInTaiLe, upInNewTaiLue, upInKhmerSymbols, upInBuginese, upInTaiTham, upInBalinese, upInSundanese, upInLepcha, upInOlChiki, upInVedicExtensions, upInPhoneticExtensions, upInPhoneticExtensionsSupplement, upInCombiningDiacriticalMarksSupplement, upInLatinExtendedAdditional, upInGreekExtended, upInGeneralPunctuation, upInSuperscriptsandSubscripts, upInCurrencySymbols, upInCombiningDiacriticalMarksforSymbols, upInLetterlikeSymbols, upInNumberForms, upInArrows, upInMathematicalOperators, upInMiscellaneousTechnical, upInControlPictures, upInOpticalCharacterRecognition, upInEnclosedAlphanumerics, upInBoxDrawing, upInBlockElements, upInGeometricShapes, upInMiscellaneousSymbols, upInDingbats, upInMiscellaneousMathematicalSymbolsA, upInSupplementalArrowsA, upInBraillePatterns, upInSupplementalArrowsB, 
	upInMiscellaneousMathematicalSymbolsB, upInSupplementalMathematicalOperators, upInMiscellaneousSymbolsandArrows, upInGlagolitic, upInLatinExtendedC, upInCoptic, upInGeorgianSupplement, upInTifinagh, upInEthiopicExtended, upInCyrillicExtendedA, upInSupplementalPunctuation, upInCJKRadicalsSupplement, upInKangxiRadicals, upInIdeographicDescriptionCharacters, upInCJKSymbolsandPunctuation, upInHiragana, upInKatakana, upInBopomofo, upInHangulCompatibilityJamo, upInKanbun, upInBopomofoExtended, upInCJKStrokes, upInKatakanaPhoneticExtensions, upInEnclosedCJKLettersandMonths, upInCJKCompatibility, upInCJKUnifiedIdeographsExtensionA, upInYijingHexagramSymbols, upInCJKUnifiedIdeographs, upInYiSyllables, upInYiRadicals, upInLisu, upInVai, upInCyrillicExtendedB, upInBamum, upInModifierToneLetters, upInLatinExtendedD, upInSylotiNagri, upInCommonIndicNumberForms, upInPhagspa, upInSaurashtra, upInDevanagariExtended, upInKayahLi, upInRejang, upInHangulJamoExtendedA, upInJavanese, upInCham, upInMyanmarExtendedA, upInTaiViet, upInMeeteiMayek, upInHangulSyllables
	, upInHangulJamoExtendedB, upInHighSurrogates, upInHighPrivateUseSurrogates, upInLowSurrogates, upInPrivateUseArea, upInCJKCompatibilityIdeographs, upInAlphabeticPresentationForms, upInArabicPresentationFormsA, upInVariationSelectors, upInVerticalForms, upInCombiningHalfMarks, upInCJKCompatibilityForms, upInSmallFormVariants, upInArabicPresentationFormsB, upInHalfwidthandFullwidthForms, upInSpecials, upInLinearBSyllabary, upInLinearBIdeograms, upInAegeanNumbers, upInAncientGreekNumbers, upInAncientSymbols, upInPhaistosDisc, upInLycian, upInCarian, upInOldItalic, upInGothic, upInUgaritic, upInOldPersian, upInDeseret, upInShavian, upInOsmanya, upInCypriotSyllabary, upInImperialAramaic, upInPhoenician, upInLydian, upInKharoshthi, upInOldSouthArabian, upInAvestan, upInInscriptionalParthian, upInInscriptionalPahlavi, upInOldTurkic, upInRumiNumeralSymbols, upInKaithi, upInCuneiform, upInCuneiformNumbersandPunctuation, upInEgyptianHieroglyphs, upInByzantineMusicalSymbols, upInMusicalSymbols, 
	upInAncientGreekMusicalNotation, upInTaiXuanJingSymbols, upInCountingRodNumerals, upInMathematicalAlphanumericSymbols, upInMahjongTiles, upInDominoTiles, upInEnclosedAlphanumericSupplement, upInEnclosedIdeographicSupplement, upInCJKUnifiedIdeographsExtensionB, upInCJKUnifiedIdeographsExtensionC, upInCJKCompatibilityIdeographsSupplement, upInTags, upInVariationSelectorsSupplement, upInSupplementaryPrivateUseAreaA, upInSupplementaryPrivateUseAreaB };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE StaticArray<StaticArray<unsigned, 2>, 197> UnicodeBlockTable;
extern PACKAGE StaticArray<TUnicodeProperty, 32> UnicodeGeneralCategoryTable;
extern PACKAGE StaticArray<System::Byte, 8720> UnicodeCategory1Table;
extern PACKAGE StaticArray<System::Word, 22160> UnicodeCategory2Table;
extern PACKAGE Inifiles::THashedStringList* PropertyNames;
extern PACKAGE System::Word __fastcall GetCharType(System::UCS4Char Ch);
extern PACKAGE TUnicodeProperty __fastcall GetUnicodeCategory(System::UCS4Char Ch);
extern PACKAGE TUnicodeProperty __fastcall GetUnicodeGeneralCategory(System::UCS4Char Ch);
extern PACKAGE TUnicodeProperty __fastcall GetUnicodeScript(System::UCS4Char Ch);
extern PACKAGE TUnicodeProperty __fastcall GetUnicodeBlock(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsUnicodeProperty(System::UCS4Char Ch, TUnicodeProperty AType)/* overload */;
extern PACKAGE bool __fastcall IsAlnum(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsAlpha(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsAscii(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsBlank(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsCntrl(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsDigit(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsSpace(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsGraph(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsLower(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsPrint(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsPunct(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsUpper(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsXDigit(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsWord(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsAssigned(System::UCS4Char Ch);
extern PACKAGE bool __fastcall IsAny(System::UCS4Char Ch);

}	/* namespace Unicodeprop */
using namespace Unicodeprop;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// UnicodepropHPP

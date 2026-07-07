object Form1: TForm1
  Left = 336
  Top = 102
  Caption = #31168#20024#12510#12463#12525#12288#25407#20837#26085#20184#12513#12491#12517#12540#12499#12523#12480#12540
  ClientHeight = 418
  ClientWidth = 516
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnDockOver = FormDockOver
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 8
    Top = 8
    Width = 381
    Height = 313
  end
  object Panel1: TPanel
    Left = 0
    Top = 377
    Width = 516
    Height = 41
    Align = alBottom
    TabOrder = 0
    object cmdExit: TButton
      Left = 428
      Top = 8
      Width = 75
      Height = 25
      Cancel = True
      Caption = #32066#20102'(&X)'
      TabOrder = 0
      OnClick = cmdExitClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 24
    Top = 324
    object mnuFile: TMenuItem
      Caption = #12501#12449#12452#12523'(&F)'
      object mnuExit: TMenuItem
        Caption = #32066#20102'(&X)'
      end
    end
    object mnuHelp: TMenuItem
      Caption = #12504#12523#12503'(&H)'
      object mnuHelpContents: TMenuItem
        Caption = #12504#12523#12503#12434#34920#31034
        ShortCut = 112
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object mnuAbout: TMenuItem
        Caption = #12496#12540#12472#12519#12531#24773#22577'(&A)'
      end
    end
  end
end

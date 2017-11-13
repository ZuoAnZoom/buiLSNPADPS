object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'GNSS'#25968#25454#36136#37327#35780#20272#36719#20214
  ClientHeight = 540
  ClientWidth = 1000
  Color = clBtnFace
  Constraints.MinHeight = 540
  Constraints.MinWidth = 1000
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object aogroup: TPageControl
    Left = 0
    Top = 0
    Width = 1000
    Height = 521
    ActivePage = rtkplotgroup
    Align = alClient
    TabOrder = 0
    object strsvrgroup: TTabSheet
      Caption = #25968#25454#30340#25509#25910#21644#19979#36733
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
    end
    object rtkconvgroup: TTabSheet
      Caption = #25968#25454#26684#24335#36716#25442#21644#32534#36753
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
    end
    object rtkplotgroup: TTabSheet
      Caption = #25968#25454#36136#37327#35780#20272#21644#20998#26512
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 521
    Width = 1000
    Height = 19
    BiDiMode = bdLeftToRight
    Panels = <
      item
        Text = ' '#27426#36814#20351#29992#26412#36719#20214
        Width = 100
      end
      item
        Alignment = taRightJustify
        BiDiMode = bdLeftToRight
        ParentBiDiMode = False
        Width = 100
      end>
    ParentBiDiMode = False
  end
  object MainMenu: TMainMenu
    Left = 400
    Top = 56
    object MenuFile: TMenuItem
      Caption = #25991#20214'&'
      object actQuit: TMenuItem
        Caption = #36864#20986'&'
        OnClick = actQuitClick
      end
    end
    object menuHelp: TMenuItem
      Caption = #24110#21161'&'
      object actHelp: TMenuItem
        Caption = #24110#21161'&'
        OnClick = actHelpClick
      end
      object actAbout: TMenuItem
        Caption = #20851#20110'&'
        OnClick = actAboutClick
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 496
    Top = 480
  end
end

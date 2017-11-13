object strsvrMainWindow: TstrsvrMainWindow
  Left = 0
  Top = 0
  Align = alClient
  BorderStyle = bsNone
  Caption = 'strsvrMainWindow'
  ClientHeight = 403
  ClientWidth = 794
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 794
    Height = 403
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object Panel21: TPanel
      Left = 0
      Top = 0
      Width = 470
      Height = 403
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object Panel211: TPanel
        Left = 0
        Top = 0
        Width = 470
        Height = 137
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object GroupBoxDateConv: TGroupBox
          Left = 1
          Top = 0
          Width = 297
          Height = 137
          Caption = #26085#26399#36716#25442
          TabOrder = 0
          object LabelMJD: TLabel
            Left = 8
            Top = 102
            Width = 143
            Height = 13
            Caption = '         '#31616#21270#20754#30053#26085#65288'MJD'#65289#65306
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object LabelDayOfYear: TLabel
            Left = 8
            Top = 75
            Width = 144
            Height = 13
            Caption = '  '#24180'  '#24180#31215#26085#65288'YYYY DDD'#65289#65306
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object LabelGPSWeek: TLabel
            Left = 8
            Top = 50
            Width = 144
            Height = 13
            Caption = 'GPS'#21608' '#26143#26399#65288'WWWW D'#65289#65306
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object LabelYearMonthDay: TLabel
            Left = 8
            Top = 26
            Width = 144
            Height = 13
            BiDiMode = bdLeftToRight
            Caption = '  '#24180' '#26376' '#26085#65288'YYYY MM DD'#65289#65306
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
          end
          object EditMJD: TEdit
            Left = 157
            Top = 102
            Width = 130
            Height = 21
            ReadOnly = True
            TabOrder = 0
          end
          object EditDayOfYear: TEdit
            Left = 157
            Top = 75
            Width = 130
            Height = 21
            TabOrder = 1
            OnChange = EditDayOfYearChange
          end
          object EditGPSWeek: TEdit
            Left = 158
            Top = 48
            Width = 130
            Height = 21
            TabOrder = 2
            OnChange = EditGPSWeekChange
          end
          object EditYearMonthDay: TEdit
            Left = 157
            Top = 21
            Width = 130
            Height = 21
            TabOrder = 3
            OnChange = EditYearMonthDayChange
          end
        end
        object GroupBoxDownloadTips: TGroupBox
          Left = 304
          Top = 0
          Width = 167
          Height = 137
          Caption = #19979#36733#25552#31034
          TabOrder = 1
          object MemoDataDownload: TMemo
            Left = 9
            Top = 19
            Width = 150
            Height = 104
            ReadOnly = True
            TabOrder = 0
          end
        end
      end
      object Panel212: TPanel
        Left = 0
        Top = 137
        Width = 470
        Height = 261
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object GroupBoxStreamRe: TGroupBox
          Left = 0
          Top = 0
          Width = 470
          Height = 257
          Caption = #25968#25454#27969#25509#25910
          TabOrder = 0
          object Message: TLabel
            Left = 20
            Top = 127
            Width = 444
            Height = 13
            Alignment = taCenter
            AutoSize = False
            Caption = #29366#24577#28040#24687
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clGray
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object Progress: TProgressBar
            Left = 21
            Top = 111
            Width = 431
            Height = 10
            TabOrder = 0
          end
          object BtnOpt: TBitBtn
            Left = 9
            Top = 24
            Width = 6
            Height = 16
            Caption = #35774#32622
            Glyph.Data = {
              AA030000424DAA03000000000000360000002800000011000000110000000100
              18000000000074030000120B0000120B00000000000000000000FFFFFFFFFFFF
              FFFFFFFFFFFFFFFFFFF8F7F5CFC9BEB1A28AA49071B1A28ACEC8BCF6F5F2FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFF6FFFFFFFFFFFFFFFFFFFFFFFFFCDC9BFA57F4D
              B04900D56500E2831FD66600B450008D5D21BAB09FFFFFFFFFFFFFFFFFFFFFFF
              FF65FFFFFFFFFFFFFFFFFFAA9D88E19447FF7703FFC37CFFB160FF5A00FFAF5C
              FFC681FF7D04BC6306846943FEFEFEFFFFFFFFFFFF69FFFFFFFFFFFFB5AE9CE0
              8A35FF7600FA6000FFFCFBFFFFFFFAB27FFFFFFFFEFFFFFB6400FF8604D46700
              A29070FFFFFFFFFFFF75FFFFFFDCD9D0C66A10FFBC6DFCDFC5FCC898FEF3E8FD
              DDBFFDE5C9FDDDBFFEF3E8FBC99AFDE1C8FFC57BBC4C00D8D5CCFFFFFF0AFBFA
              F9AE885CFF8005FA9538FFFFFFFFFFFFFBA657FA9437FB9F4AFA9537FBA555FF
              FFFFFFFFFFFB9C45FF7A04A5743BF9F9F86CDED9D1CC7622FF7C00F9983FFEF9
              F4FA983DFA9D48FDECDBFFFFFFFDEDDDFA9F4BFA963AFEFAF5F99A42FF8100C8
              690DD7CFC375C2A98BEA7304FFE2C0FFFFFFFCBE84F86F00FEEEE0FFFFFFFCCF
              A6FFFFFFFEF0E3F87100FBBD83FFFFFFFFE4C4ED770AC5AC8D52BB9971F87C0E
              FFAE69FEFAF5FA9A42FA8C23FFFFFFFAA14FF85A00FA9E4AFFFFFFFA8F2AFA96
              3CFFFAF5FEAD69FC871CD2BBA16FCCB395F08119FF5100FCD1A8FBB06CF8790E
              FFFFFFFBB778F75900FBB473FFFFFFF97C11FBAD67FCD3ADFD4D00F58B29E0D1
              C009EAE2D7DE6700FF9639FFFFFFFDD5B1F64B00FCC797FFFFFFFEFBFFFFFFFF
              FCCA9BF64B00FDD4AFFFFFFFFF9337E77D1AF3EFEB2CFDFDFDD78739FFA74DFC
              D3B2FEFFFEFA9944F75200FBA85CFDD5ABFBAA5FF75200F99640FEFEFDFCD3B1
              FFA74DE8B482FFFFFF74FFFFFFF2EEE8F56A00FC5E00FAA14EFFFFFFFBB779F8
              6D00F75900F86C00FBB576FFFFFFFAA353FA5900F87600FBFAF9FFFFFF09FFFF
              FFFFFFFFEECCACFF5E00FB9436FFFFFFFDE7D9FDEAD9FDE1CDFEE9D9FDE6D9FF
              FFFFFA9538FE5E00F7E8D8FFFFFFFFFFFF73FFFFFFFFFFFFFFFFFFEEC39BFF82
              12FD9537F76300FAA04DFFFFFFFAA352F86000F99030FF8A20F4DAC1FFFFFFFF
              FFFFFFFFFF6DFFFFFFFFFFFFFFFFFFFFFFFFF6E5D4F98F30FC7900F97700FAA0
              4DF97400F97901FAA14EFFEEDFFFFFFFFFFFFFFFFFFFFFFFFF62FFFFFFFFFFFF
              FFFFFFFFFFFFFFFFFFFFFEFEFBE6D2FCC795FBB06DFCCFA5FDF0E3FFFFFFFFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFF50}
            TabOrder = 1
            Visible = False
            OnClick = BtnOptClick
          end
          object BtnStop: TBitBtn
            Left = 295
            Top = 146
            Width = 75
            Height = 25
            Caption = #32467#26463
            Glyph.Data = {
              AA030000424DAA03000000000000360000002800000011000000110000000100
              18000000000074030000120B0000120B00000000000000000000FFFFFFFFFFFF
              FFFFFFFFFFFFFFFFFFF6F1EAE0C7A2DEBB88DFBC85DEBB88DFC59EF4EEE5FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFF70FFFFFFFFFFFFFFFFFFFFFFFFD7B084D9853A
              E8925BFCAA82FFBB99FFB08AEC9662D7823BD4A878FCFAF9FFFFFFFFFFFFFFFF
              FF20FFFFFFFFFFFFF8F4F2D89454D26C2D922E0A973515BC5D39CD704CC36440
              A4432193300FC05B23D28743F1EAE5FFFFFFFFFFFF73FFFFFFFFFFFFD4915CBC
              59236D13007013006F13008627049E421B8D2D08711500701200701500A54417
              CD8249FBF9F8FFFFFF20FFFFFFD3A88EC0662D4F08005F02009E664FF0FCFFAF
              8F83640000AB8172EBFBFF9F7260670700520A00A24E1ECE9B7DFFFFFF20F8F3
              F3C473406222084C11004E0000A78377FFFFFFD1C5C1520000C9B2AAFFFFFFB2
              9B945100005918004F1400AA5826F0E6E470DFC3BAA058292C02004A16003400
              00937970FFFFFFCDC0BD3D0000B9A49EFFFFFFAA97913400004713002300007C
              401AD9B6AA31D2A49566391C0300003C0F003A0000997D71FFFFFFD3C4BF5A00
              00C0A9A0FFFFFFB59E955200005B1C012F08004F260FC2928270C596887F431B
              53160187330F871C00B1897AFFFFFFDCCAC4861B00C9B0A7FFFFFFC7A99E9024
              009E3F178B310D964516B9867620CBA198D26E2EA13A13A84920952A00B68D7E
              FFFFFFE0CEC78E2400CAB2A9FFFFFFCCADA2952E03A449239A3E1AC5642AC594
              8874D7BFBDD98349B15532B65C36AF4519C39787FFFFFFE8D6CFAB4015D2B8AF
              FFFFFFD8B8ACB14A1EBC613BB35936D17943D0B2AE70FDFCFCCE8961F59C6CD1
              7551D36639CCA796FEFFFFEBDDD6CB5E30D8C5BBFFFFFFE0C0B3D36B3ED77B56
              F2976BCC7E53F2EDED2FFFFFFFC19D95FFC288FFA37FF79168E89C7BE9C2B2EC
              AD92F68F64E9A587EBC6B5ECA486F79369FFA580FFBE88BB9086FFFFFF3AFFFF
              FFFFFFFFBA816BFFE4B1FFC7ACFFA987FF9970FEA682FFBB9DFFAC89FF9971FE
              A784FFC8ADFFE2B4B9795FFFFFFFFFFFFF39FFFFFFFFFFFFFFFFFFB67A68FFDE
              B4FFF7DDFFDDCCFFCFBBFFCAB6FFCEBAFFDDCCFFF7DFFFDFB8B57461F9F7F7FF
              FFFFFFFFFF20FFFFFFFFFFFFFFFFFFFFFFFFC3A19DCA8F76FBCCAEFFEBD0FFF7
              DEFFECD2FBCEB0CC8F76BF9894FFFFFFFFFFFFFFFFFFFFFFFF65FFFFFFFFFFFF
              FFFFFFFFFFFFFFFFFFFCFBFBD4BAB9C39B97C09791C29995D1B5B4F9F7F7FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFF3F}
            TabOrder = 2
            OnClick = BtnStopClick
          end
          object BtnStart: TBitBtn
            Left = 119
            Top = 145
            Width = 75
            Height = 25
            Caption = #24320#22987
            Glyph.Data = {
              AA030000424DAA03000000000000360000002800000011000000110000000100
              18000000000074030000120B0000120B00000000000000000000FFFFFFFFFFFF
              FFFFFFFFFFFFFFFFFFF6F5F5CCC5BEB8AFA7B3ACA4BAB1AACDC6C2FDFDFDFFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFBCB2A59EA1AD
              85AAE477B0FB7ABAFF8CC7FFA1CDF0B5B8BAC2B5AFFFFFFFFFFFFFFFFFFFFFFF
              FF00FFFFFFFFFFFFF1F0EFB3A69A80A6F21A73FF0066FC0376FF1285FF1692FF
              11A0FF44CEFFB9F3FFC1B0A6FDFDFDFFFFFFFFFFFF00FFFFFFFDFDFDB1A19553
              9EFF004FFC005CF21375F62183F72A90FF359EFF30A7FF12AEFF00BAFFA1F9FF
              B7A39AFFFFFFFFFFFF00FFFFFFB1A29563ADFF0062FF005DE8004DCF025DD61C
              7DF40E74E81685F631AAFF2DAFFF20B5FF00B0FFB1E5FFB9ADA5FFFFFF00E7E4
              E283A0C40078FF0060F82C7AE8C8D3E8B1C2DA2976D8B6CEEA6798CE0274E01D
              9FFF33AFFF1CA7FF41BBFFA3A3A8F4F4F400BBAFA587C3FF0077FF0053F7458C
              EBFFFFFFF9F8F32F72CAFFFFFFFFFFF99AB4D41D77D00984F535A4FF1695FF92
              BCEAC3BBB500A4A09E82CDFF35A2FF0064FE277DEAFFFDE4C9D4DB286DCCCADD
              ECFFFFF3FFFFFFE2E1E3538BCA1B7CE5118BFF73B1FAAEA49B009EA0A362C4FF
              4BACFF2993FF4591ECE0D7C3AFBAC22063C9B5C5D3DCDED1D6E0DEFFFEEFFFFF
              E46998D00062FC579FFDA69D9500A7A5A56ACAFF33A5FF389DFF73AFF4D7CABA
              A3ABB42568CD9BA7B9B3B0A7C8C3B4D9D5C48AAFDC2276EB0468FD73A9F8AAA1
              9800B9AFA88AD6FF20A3FF2999FF6CAFF6F8E4D1C6C6C85D93DCCACED5E9D4B9
              BDBCBC5F8FD7176BEC3883F24D98FFACC2EBB7B0A900D7D2CEAFD6F91AA4FF23
              9DFF66B2F9FFF8E8D5D8DE5F9DE7E8ECF1BACCE74B8FF13D87F55F9AF25F9AF3
              66A9FFA0A5B5E7E6E500FFFFFFBFB4AE77D9FF0C98FF41A9FF5AAFFD58A8FB42
              9BFE56A2FB358BF83B8FFA4F98F64F95F53491FFA3CDFFA59A8FFFFFFF00FFFF
              FFE5E3E2E3E8EA4CC4FF0996FF229CFF2A9BFF3B9EFF3094FF3D99FF469BFE42
              98FE2A95FF83C7FFACA09AF4F4F4FFFFFFFFFFFFFFFFFFFFD2CCC8E7EEEA71D7
              FF129FFF189EFF2BA2FF309FFF2D9DFF239BFF34A8FF93D1FFB6AAA6DEDCDAFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDCD9D7CEC6BEAEDEFF84D8FF5FCAFF59C7
              FF68CAFF8DD2FFABC3DCB3A69DEAE9E9FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
              FFFFFFFFFFFFFFFFFFD2CCC7BFB6B0ABADAEA3A8ACA9A8A8B9AEA8D4CFCCFFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFF00}
            TabOrder = 3
            OnClick = BtnStartClick
          end
          object PanelStr1: TPanel
            Left = 30
            Top = 24
            Width = 44
            Height = 81
            BevelOuter = bvNone
            TabOrder = 4
            object LabelOutput1: TLabel
              Left = 14
              Top = 57
              Width = 36
              Height = 13
              Caption = #36755#20986#65306
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object LabelInput: TLabel
              Left = 14
              Top = 27
              Width = 36
              Height = 13
              Caption = #36755#20837#65306
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
            end
            object Label5: TLabel
              Left = 26
              Top = 0
              Width = 13
              Height = 13
              Caption = #27969
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object PanelStr2: TPanel
            Left = 80
            Top = 24
            Width = 145
            Height = 81
            BevelOuter = bvNone
            TabOrder = 5
            object Label6: TLabel
              Left = 60
              Top = 0
              Width = 26
              Height = 13
              Caption = #31867#22411
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Output1: TComboBox
              Left = 4
              Top = 54
              Width = 136
              Height = 21
              Style = csDropDownList
              ItemIndex = 0
              TabOrder = 0
              OnChange = Output1Change
              Items.Strings = (
                ''
                #25991#20214#27169#24335)
            end
            object Input: TComboBox
              Left = 4
              Top = 25
              Width = 136
              Height = 21
              Style = csDropDownList
              ItemIndex = 0
              TabOrder = 1
              Text = #20018#21475#27169#24335
              OnChange = InputChange
              Items.Strings = (
                #20018#21475#27169#24335
                'NTRIP'#23458#25143#31471#27169#24335)
            end
          end
          object PanelStr3: TPanel
            Left = 249
            Top = 24
            Width = 44
            Height = 81
            BevelOuter = bvNone
            TabOrder = 6
            object BtnOutput1: TSpeedButton
              Left = 13
              Top = 54
              Width = 23
              Height = 22
              Glyph.Data = {
                76030000424D7603000000000000360000002800000011000000100000000100
                18000000000040030000202E0000202E00000000000000000000FFFFFFFFFFFF
                ECE4C8D3C287CEBD81CBB97CC8B676C6B371C6B371C8B574CAB879CFBE84D2C0
                80D0BE7DE6DCB9FFFFFFFFFFFF6CFFFFFFE9DDACC1A235C7AA42C8A93DC7A734
                CBAD43CBAD43CBAD42CBAD42CAAC42C9AA3EC8AA44C8AB45C2A236DFCE8BFFFF
                FF27F6F0D6CDAD41D5B955D4B954D9C066D7BC5ECEAE3BD6BB59D5BA58D6BB59
                D3B750D2B44AD3B54CD2B54BD7BC5CCCAB3DF2EACB27E5D59FD4B85AD5BA5FD1
                B34EDDC87EFFFFFFE2D090CFAF43D6BC63D3B654CFB045E9DBABF1E9CAD9C16E
                D3B655D5B95CE3D29776E6D69ED7BD61D7BD61D7BC5FD2B44DF2E9CAFFFFFFDE
                C87CD1B145CFB041F4EED7EEE3BCEADEAFECE1B7D1B247D7BE62E4D29509E9D9
                A1DABF62DABF63DABE64D8BC5CD2B247EADCABF2EBCFD1AF3DF0E5C0FFFFFFFF
                FFFFF1E9CBDCC26CD8BB5ADABF63E7D5997AEAD9A4DBC065DBC166DCC267DDC4
                6DDBBF5FD1AB2EDABD5CF4EBD0FFFFFFFFFFFFFBF9EFDDC36CD6B84FDCC269DB
                C065E8D69B6FEBDCA7E1C66EE3C973E4CA75E3C76CE5C971EFE0ADF6EDD1FFFF
                FFFFFFFFF9F3DEE0C15FDFBF58E5CC79E3C871E1C76FE9D89F09EDDDA9E8CD7A
                EACF7DE8CD78E6C970F9F3E0FFFFFFFFFFFFFFFFFFF8F2DDE8CE80F0E1B0EBD3
                8AE6C86BE9CF7EEACF7DEDDBA269EDDEABEACF7CECD17FEACC74EFD997FCF8EC
                E9CD77F7EDCDFFFFFFE9CD77F1E2B2FBF9EFF5EBCAEAD07FEACD75ECD180EDDC
                A309EFDFADEDD280EFD483EED280EFD78CECCF77EACD72FDFCF8FCF8EAEBCB6B
                EFD78EF6ECCBFAF8EBFBF7EAEED382EED27EEFDEA76FF0E1AEF0D684F1D886F0
                D786EFD581EED071F5E6B4FAF3DBEFD582EFD47DEED276EFD685FAF5E4FCFAEE
                EFD680F1D782F0DEA767F1E2B0F2D885F4DA88F3D987F3D987F3DA89F2D781F0
                D06EF2D67EF3DA8AF3DA89F2D57DF3D888F2D681F3D782F5DB8AF1DFAA73F7EE
                D2F1D78EF7E0A0F4DB93F4DC95F4DC95F4DC94F4DC94F4DC95F4DC95F4DC95F4
                DC96F4DA8FF3DA8EF6DF9CF3DB98F7EDCD20FFFFFFF4E5B4F5E1AEF9EAC4F8EA
                C5F8EAC4F8EAC4F8EAC4F8EAC4F8EAC4F8EAC4F8EAC4F8EAC5F8EAC4F7E5B8F2
                DFA8FFFFFD61FFFFFFFFFFFEF5EAC5F5E5B4F5E5B5F6E5B6F6E5B6F6E5B6F6E5
                B6F6E5B6F6E5B6F6E5B6F5E5B5F5E4B6F4E6BCFEFDF9FFFFFF20}
              OnClick = BtnOutput1Click
            end
            object BtnInput: TSpeedButton
              Left = 13
              Top = 24
              Width = 23
              Height = 22
              Glyph.Data = {
                76030000424D7603000000000000360000002800000011000000100000000100
                18000000000040030000202E0000202E00000000000000000000FFFFFFFFFFFF
                ECE4C8D3C287CEBD81CBB97CC8B676C6B371C6B371C8B574CAB879CFBE84D2C0
                80D0BE7DE6DCB9FFFFFFFFFFFF6CFFFFFFE9DDACC1A235C7AA42C8A93DC7A734
                CBAD43CBAD43CBAD42CBAD42CAAC42C9AA3EC8AA44C8AB45C2A236DFCE8BFFFF
                FF27F6F0D6CDAD41D5B955D4B954D9C066D7BC5ECEAE3BD6BB59D5BA58D6BB59
                D3B750D2B44AD3B54CD2B54BD7BC5CCCAB3DF2EACB27E5D59FD4B85AD5BA5FD1
                B34EDDC87EFFFFFFE2D090CFAF43D6BC63D3B654CFB045E9DBABF1E9CAD9C16E
                D3B655D5B95CE3D29776E6D69ED7BD61D7BD61D7BC5FD2B44DF2E9CAFFFFFFDE
                C87CD1B145CFB041F4EED7EEE3BCEADEAFECE1B7D1B247D7BE62E4D29509E9D9
                A1DABF62DABF63DABE64D8BC5CD2B247EADCABF2EBCFD1AF3DF0E5C0FFFFFFFF
                FFFFF1E9CBDCC26CD8BB5ADABF63E7D5997AEAD9A4DBC065DBC166DCC267DDC4
                6DDBBF5FD1AB2EDABD5CF4EBD0FFFFFFFFFFFFFBF9EFDDC36CD6B84FDCC269DB
                C065E8D69B6FEBDCA7E1C66EE3C973E4CA75E3C76CE5C971EFE0ADF6EDD1FFFF
                FFFFFFFFF9F3DEE0C15FDFBF58E5CC79E3C871E1C76FE9D89F09EDDDA9E8CD7A
                EACF7DE8CD78E6C970F9F3E0FFFFFFFFFFFFFFFFFFF8F2DDE8CE80F0E1B0EBD3
                8AE6C86BE9CF7EEACF7DEDDBA269EDDEABEACF7CECD17FEACC74EFD997FCF8EC
                E9CD77F7EDCDFFFFFFE9CD77F1E2B2FBF9EFF5EBCAEAD07FEACD75ECD180EDDC
                A309EFDFADEDD280EFD483EED280EFD78CECCF77EACD72FDFCF8FCF8EAEBCB6B
                EFD78EF6ECCBFAF8EBFBF7EAEED382EED27EEFDEA76FF0E1AEF0D684F1D886F0
                D786EFD581EED071F5E6B4FAF3DBEFD582EFD47DEED276EFD685FAF5E4FCFAEE
                EFD680F1D782F0DEA767F1E2B0F2D885F4DA88F3D987F3D987F3DA89F2D781F0
                D06EF2D67EF3DA8AF3DA89F2D57DF3D888F2D681F3D782F5DB8AF1DFAA73F7EE
                D2F1D78EF7E0A0F4DB93F4DC95F4DC95F4DC94F4DC94F4DC95F4DC95F4DC95F4
                DC96F4DA8FF3DA8EF6DF9CF3DB98F7EDCD20FFFFFFF4E5B4F5E1AEF9EAC4F8EA
                C5F8EAC4F8EAC4F8EAC4F8EAC4F8EAC4F8EAC4F8EAC4F8EAC5F8EAC4F7E5B8F2
                DFA8FFFFFD61FFFFFFFFFFFEF5EAC5F5E5B4F5E5B5F6E5B6F6E5B6F6E5B6F6E5
                B6F6E5B6F6E5B6F6E5B6F5E5B5F5E4B6F4E6BCFEFDF9FFFFFF20}
              OnClick = BtnInputClick
            end
            object Label7: TLabel
              Left = 11
              Top = 0
              Width = 26
              Height = 13
              Caption = #37197#32622
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object PanelStr4: TPanel
            Left = 394
            Top = 24
            Width = 57
            Height = 81
            BevelOuter = bvNone
            TabOrder = 7
            object Output1Bps: TLabel
              Left = 40
              Top = 58
              Width = 6
              Height = 13
              BiDiMode = bdRightToLeft
              Caption = '0'
              ParentBiDiMode = False
            end
            object InputBps: TLabel
              Left = 40
              Top = 29
              Width = 6
              Height = 13
              BiDiMode = bdRightToLeft
              Caption = '0'
              ParentBiDiMode = False
            end
            object Label9: TLabel
              Left = 10
              Top = 0
              Width = 39
              Height = 13
              Caption = #27604#29305#29575
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object PanelStr5: TPanel
            Left = 313
            Top = 24
            Width = 57
            Height = 81
            BevelOuter = bvNone
            TabOrder = 8
            object Output1Byte: TLabel
              Left = 40
              Top = 58
              Width = 6
              Height = 13
              BiDiMode = bdRightToLeft
              Caption = '0'
              ParentBiDiMode = False
            end
            object InputByte: TLabel
              Left = 40
              Top = 29
              Width = 6
              Height = 13
              BiDiMode = bdRightToLeft
              Caption = '0'
              ParentBiDiMode = False
            end
            object Label8: TLabel
              Left = 10
              Top = 0
              Width = 39
              Height = 13
              Caption = #23383#33410#25968
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'Tahoma'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object MemoStreamStr: TMemo
            Left = 2
            Top = 188
            Width = 466
            Height = 67
            Align = alBottom
            ScrollBars = ssVertical
            TabOrder = 9
          end
          object CheckBoxHEX: TCheckBox
            Left = 424
            Top = 175
            Width = 40
            Height = 13
            BiDiMode = bdLeftToRight
            Caption = 'HEX'
            Checked = True
            ParentBiDiMode = False
            State = cbChecked
            TabOrder = 10
          end
        end
      end
    end
    object Panel22: TPanel
      Left = 470
      Top = 0
      Width = 324
      Height = 403
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 1
      object GroupBoxDataDownload: TGroupBox
        Left = 3
        Top = 0
        Width = 318
        Height = 400
        Caption = #25968#25454#19979#36733
        TabOrder = 0
        object PanelDataDownload: TPanel
          Left = 2
          Top = 15
          Width = 314
          Height = 81
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object LabelAddress: TLabel
            Left = 8
            Top = 7
            Width = 64
            Height = 13
            Caption = #26381#21153#22120#22320#22336':'
          end
          object LabelUserName: TLabel
            Left = 8
            Top = 31
            Width = 40
            Height = 13
            Caption = #29992#25143#21517':'
          end
          object LabelPassWord: TLabel
            Left = 154
            Top = 31
            Width = 28
            Height = 13
            Caption = #23494#30721':'
          end
          object LabelCurDir: TLabel
            Left = 8
            Top = 56
            Width = 52
            Height = 13
            Caption = #24403#21069#30446#24405':'
          end
          object btn_EnterDirectory: TSpeedButton
            Left = 190
            Top = 53
            Width = 23
            Height = 22
            Glyph.Data = {
              AA030000424DAA03000000000000360000002800000011000000110000000100
              18000000000074030000120B0000120B00000000000000000000A0A0D019199E
              0D0DA10D0DA30D0DA60D0DA90D0DAB0D0DAE0D0DAE0D0DAD0D0DAA0D0DA70D0D
              A40D0DA00D0D9E1717979797D02F0000930000C90000CC0000CC0000D70000E1
              0000EA0000F00000F10000ED0000ED0000E40000DA0000D00000C70000C10000
              91CC0505990000BB0000B96262DB8D8DE98F8FED8E8EF09292F08D8DEF4E4EE3
              0000CF0000CE0000C60000C00000B70000B5070798FF0E0F980000A56C6BD3FF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF3131D00000BB0000BC0000B6
              0000AE0000AB0D0D96CA1111950000999999DCFFFFFFFFFFFFD4D7D567716AED
              EEEDFFFFFFFFFFFF5757D10000AA0000B10000AB0000A50000A10D0D91311414
              9200008D8888D2FFFFFFFFFFFFCBCFCC203024F3F4F3FFFFFFFFFFFF4E4EC600
              009C0000A50000A000009A0000960D0D8D4514138C0000808788CCFFFFFFFFFF
              FFB5B9B6202A22EEF0EFFFFFFFFFFFFF4D4DBC00008D00009900009500008F00
              00880D0D87401010870000738C8CC8FFFFFFFFFFFFA6ACA81B231DE4E6E5FFFF
              FFFFFFFF4A4AB100007B00008A00008700008200007F0D0D86400F0F8700006B
              9897CBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF5B5AAF00006F0202
              8000007C00007A00007F0D0D86000F0F870101707776BBE1E1F0E0E0F0E5E5F4
              EEEDFDE2E2F2D4D4E9D2D2E85A59AC03037C1C1C8D12128800007800007D0D0D
              87000E0E870606820606830808840909840B0B850C0C86020378A0A0CF9B9ACD
              04047B17178C16168B1D1D8EABABD536369A0D0D7B000D0D8603038200007F00
              007C00007D00007E00007F000066C2C2E0E5E5F200006F15158C040482232291
              FFFFFF4141A10D0D78000D0D860000800303810505820707830808840A0A8500
              00735E5EB1FFFFFF09098500006F0000658A89C4FFFFFF0B0B830D0D84000D0D
              86000080000080020281050582070783080884040481000076E4E4F2E9E9F540
              40936E6EB4FFFFFF7B7BBD00007913138B0005058200007D00007E00007E0000
              7F0000800000810404830000740F0E84C4C4E2EAEAF6F2F1FA7C7CBD00007412
              1289111187620707801313851111861010861010861111871313881615891919
              8D05057F00007E2D2D9521218F00007C1E1E8D2F2F9310108500A3A3D22C2C94
              21218E20208F20208F20208E21218F21218F22228F23238F1E1E8E1515891717
              8A2424902626912D2E959A9ACDFF}
            OnClick = btn_EnterDirectoryClick
          end
          object btn_Back: TSpeedButton
            Left = 218
            Top = 53
            Width = 23
            Height = 22
            Glyph.Data = {
              86050000424D8605000000000000320400002800000011000000110000000100
              08000000000054010000120B0000120B0000FF000000FF000000A496FF00583C
              FF006658FF005C38FF007A72FF00D3CCFF003C5CFE00DBD4FF00FAF9FF00DBDB
              FF00F5F5FF005873FE00BCBBFF00796DFF00BBC3FF00CBC9FF00D5DAFF00B2AB
              FF00836AFF004058FE00CBD1FF00F1F1FF00AAB3FF00CCC3FF00EDEDFF00ABAB
              FF006C7AFE00C3C2FF00C4BBFF00B3B4FF00B2A3FF00947BFF006A82FE006343
              FF00BBB2FF003E5AFE00A2A5FE008984FF007664FF00E2DEFF009BA3FE00653B
              FF007478FE00929BFE00756EFF00A4ACFF004562FE00FFFFFF00C2B6FF00E9E6
              FF009B8BFF004C4AFE007153FF004C63FE006D6CFE008B9AFE007283FE007965
              FF00A4B1FF00544DFF00536BFE00C5CCFF008393FE006A4DFF004C5BFE007676
              FE004C54FE00E8E9FF00DDE0FF006273FE00AAA3FF00B4BCFF00725BFF00E5E8
              FF00BAACFF0095A3FE005C43FF009C9CFE009C92FF00FCFCFF00ACB9FF007670
              FF00EEEAFF004A4CFE00634BFF009182FF008D93FE00D1D5FF009A84FF006363
              FE008372FF007B89FE005A63FE00F1EEFF006876FE005254FE00948BFF00E1E4
              FF005B4AFF00E5E6FF00D6D6FF00617BFE008384FE00636BFE00545BFE00D7D0
              FF008B8BFE005265FE004E48FF00B6C1FF005A3AFF00706DFE005D5BFE00858D
              FE007E6EFF00E5E1FF005C52FF007B5DFF00E1E1FF008162FF006A61FF00EAED
              FF005C6DFE009191FE008599FE00A38EFF007D90FE007372FE00707EFE006D71
              FE00857EFF00F4F3FF00EDF0FF004D6AFE007C6BFF007175FE00727AFE00726A
              FF007C7CFE007969FF008B7AFF006D76FE007C83FE008F74FF00C8BDFF007568
              FF00425DFE005046FF00F2F3FF005F3EFF006945FF00455FFE00748DFE00465A
              FE00F8F6FF005646FF00B09DFF00747EFE00714EFF00896EFF006A72FE008FA0
              FE00F7F8FF003E61FE004F4EFE00BFC7FF009AA8FE00D0D0FF007857FF004655
              FE005543FF003B5DFE005E35FF005D36FF005245FF005045FF003D5BFE005C37
              FF005144FF004F46FF00484EFE00494DFE005243FF00474FFE004E47FF004354
              FE005342FF003A5EFE004356FE004650FE004753FE004453FE005F34FF00553F
              FF005741FF005441FF004D48FF004B4BFE003D5AFE005440FF00563EFF003C5B
              FE005D37FF004552FE004551FE005B38FF005341FF004156FE004255FE00573D
              FF004C49FE005B39FF003E59FE004651FE005540FF00593BFF004057FE003F58
              FE004D49FF004452FE005242FF004750FE004B4AFE004353FE003B5CFE005E36
              FF004F47FF00563FFF005A39FF003F59FE004A4BFE00484FFE005143FF00593A
              FF00494CFE004D49FE003A5DFE005F35FF00573EFF004254FE004157FE00583B
              FF005044FF00494EFE00FEFEFF004155FE00FDFDFF00FBFBFF00FDFEFF00FBFC
              FF004950FE00B7A7FF004851FE004668FE005541FF00FEBAC3C1C8D101D7E4CD
              B1ADE1ACC0C0FE000000AFB2B6CEC7E32F2F2F2F2F03B1ADACACC00000006CB3
              AFE82F2F2F2F2F2F2F2F2FB1ADE1AC00000033C4B82F2F2F2F2F2F2F2F2F2F2F
              03B1AD00000053DE2F2F2F2F2F2F2F2F2F2F2F2F2FCDB1000000B4F32F2FC4B8
              AFB2B6CEC7E32F2F2F6ED3000000BD2F2F2F2F2F2F2F2F2F2FC3C12F2F2FE900
              0000CB2F2F2F2F2F2F2F2F2F2F2FCE2F2F2F01000000B92F2F2F2F2F2F2F2F2F
              2F2FE82F2F2FC8000000CF2F2F2F2F2F2F242F2F2F2F932F2F2FC7000000132F
              2F2F2FCCBD192F2F2FD26C2F2F2FBA000000D4D92F2F2FDFDBD5B7B4B5C52F2F
              2FAEB2000000B0232F2F2F2FB92D2F2F2F2F2F2F2F6CB300000006B0C62F2F2F
              2F2F2F2F2F2F2F2FC533C4000000ABE006B02F2F2F2F2F2F2F2F2FB7B553DEB7
              1C11BBECAB06B0C62F2F2F2F2FDFCBD5B7B4B5000000FEBBBBABE006B023E513
              CFD0B9BFCCDDFE000000}
            OnClick = btn_BackClick
          end
          object edt_ServerAddress: TEdit
            Left = 74
            Top = 4
            Width = 231
            Height = 21
            TabOrder = 0
            Text = 'cddis.gsfc.nasa.gov'
          end
          object edt_UserName: TEdit
            Left = 74
            Top = 29
            Width = 70
            Height = 21
            TabOrder = 1
            Text = 'anonymous'
          end
          object edt_UserPassword: TEdit
            Left = 184
            Top = 29
            Width = 57
            Height = 21
            TabOrder = 2
          end
          object btn_Connect: TButton
            Left = 247
            Top = 31
            Width = 59
            Height = 21
            Caption = #36830#25509
            TabOrder = 3
            OnClick = btn_ConnectClick
          end
          object btn_Download: TButton
            Left = 247
            Top = 54
            Width = 59
            Height = 21
            Caption = #19979#36733
            TabOrder = 4
            OnClick = btn_DownloadClick
          end
          object edt_CurrentDirectory: TEdit
            Left = 74
            Top = 54
            Width = 111
            Height = 21
            TabOrder = 5
          end
        end
        object StringGrid1: TStringGrid
          Left = 2
          Top = 96
          Width = 314
          Height = 302
          Align = alClient
          FixedCols = 0
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
          TabOrder = 1
          OnDblClick = StringGrid1DblClick
        end
      end
    end
  end
  object dlgSave_File: TSaveDialog
    Filter = #25152#26377#25991#20214'(*.*)|(*.*)'
    Left = 544
    Top = 248
  end
  object idftp_Client: TIdFTP
    IPVersion = Id_IPv4
    NATKeepAlive.UseKeepAlive = False
    NATKeepAlive.IdleTimeMS = 0
    NATKeepAlive.IntervalMS = 0
    ProxySettings.ProxyType = fpcmNone
    ProxySettings.Port = 0
    Left = 696
    Top = 248
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 430
    Top = 152
  end
  object Timer2: TTimer
    Interval = 1
    OnTimer = Timer2Timer
    Left = 388
    Top = 184
  end
end
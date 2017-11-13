object convMainWindow: TconvMainWindow
  Left = 49
  Top = 165
  Align = alClient
  BorderStyle = bsNone
  Caption = 'convMainWindow'
  ClientHeight = 403
  ClientWidth = 794
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 384
    Width = 794
    Height = 19
    Align = alBottom
    TabOrder = 0
    object Message: TLabel
      Left = 1
      Top = 1
      Width = 792
      Height = 17
      Align = alClient
      Alignment = taCenter
      AutoSize = False
      ExplicitLeft = 2
      ExplicitTop = 8
      ExplicitWidth = 31
      ExplicitHeight = 13
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 794
    Height = 384
    Align = alTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvNone
    TabOrder = 1
    object Panel21: TPanel
      Left = 0
      Top = 0
      Width = 329
      Height = 384
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object Panel211: TPanel
        Left = 0
        Top = 0
        Width = 329
        Height = 126
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          329
          126)
        object BtnInFile: TSpeedButton
          Left = 20
          Top = 14
          Width = 73
          Height = 25
          Caption = #25171#24320
          Glyph.Data = {
            66030000424D660300000000000036000000280000000F000000110000000100
            18000000000030030000120B0000120B00000000000000000000FFFFFFFFFFFF
            FFFFFFA4D5E4C9E0E8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE5EFFAE9EEF0FFFF
            FFFFFFFFFFFFFF202020FFFFFFFFFFFFACD5E364C5E5C7DBE0FFFFFFF5F9FBD6
            E8EFABD1E385B9DF50ABAB5CAAC8D0E0E5FFFFFFFFFFFF202020FAFCFDA8D9E5
            62C4DE7DD7EF90B8C684A2B06CB2CC60AED26CAEF13DB78A20B54863B6EEAED6
            E6FFFFFFFFFFFF202020CDEAF159C2DE7CD1E984D8ED63A3BE4686A266B9DC7D
            BDFE51BCA119C83126B8516DBBFBC1E1FCFFFFFFFFFFFF202020D0EEF567CBE4
            79D1EA82DBF067ACC15794B475BDFA53C0AA27CC4C2CCB571FB84117AB4FA0D3
            CAFFFFFFFFFFFF202020D1EEF66CCEE67BD5EB85E0F168ADC8609BC958C1A61A
            C94236CE6932C66024BF4A01AA0B009300E2F3E1FFFFFF202020D2EFF66FD2E9
            7DDBED83DEF178C4DC579ECA88D3A74ED7671EC45B35C96023BC4608AA210096
            00189116F6FCF6202020D3F1F56FD5EC80DEF180DCF186DEEE62ADD271BAE7A6
            E7CB46D06313C04A32BF4F33BF3E009A00008600BBDFBC202020D2F1F56ED8EE
            82E1F282E2F285DDEC6AB5D65EB7E87BD4FFA3E6C534C74417B358BAEEEB5FC8
            60008E0082C3820A2020D3F2F672DCF081E5F481E6F385E1ED6BB9DC6CC2EA6D
            D0FF80D7FF8BE5A836C75ECEE2FCF3FAF603A20171BA71202020D3F2F675E0F2
            86E8F683E9F689E3EF6FBFE06EC7F277D5FF71D3FF7ADCFB7AE5D1B9D6EAFFFF
            FF0A9703ABD8AA202020D3F3F773E3F385EBF883ECF98AE6F171C4E670CCF677
            D5FF76D6FF74D4FF75DBFFD8EAFCDEEEDB068D04F9FDF9202020D3F3F774E5F5
            84EEFB83EFFC89E9F373C8E972D0FA77D6FF76D5FF76D5FF74DAFFBCE3E85BB5
            4FE3F4E3FFFFFF202020D2F3F777E7F788F0FD84F2FE8EECF477CDF074D7FF77
            D5FF76D5FF76D5FF76D9FF7CCCBBEFF9EDFFFFFFFFFFFF202020D4F5F778EBF7
            8CF6FF8DFAFF8DEBF276CFF770D5FF6DD4FF6ED5FF6AD2FF62D7FFB9E1EFFFFF
            FFFFFFFFFFFFFF202020D2F5F878F3FB82F2FB7BE1F871D2F870D4FC76D6FD7B
            D6FA82D8F692DDF69BE1F4E6F3F7FFFFFFFFFFFFFFFFFF202020D7F3F78AE1EB
            A8DEE9B8E0EFCCE9F3DCF1F5E9F7F7F1F8F8F8FBFBFEFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFF202020}
          OnClick = BtnInFileClick
        end
        object BtnConvert: TSpeedButton
          Left = 99
          Top = 14
          Width = 73
          Height = 25
          Caption = #36716#25442
          Glyph.Data = {
            AA030000424DAA03000000000000360000002800000011000000110000000100
            18000000000074030000120B0000120B00000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFDFDFEF0EFF3D8D9DCCCC9C2C4BBAAC6BCABCAC5BDD4D6DAEEF3
            F8FDFDFDFFFFFFFFFFFFFFFFFF20FFFFFFFFFFFFFFFFFFFFFFFFF3EEF8C5BABE
            A69E77B3A159C19942B8802EA26B278C5D2AA69D92E9F6FFFFFFFFFFFFFFFFFF
            FF20FFFFFFFFFFFFFFFFFFFFFFFFEDECDF9EB5559BA430969714A19417B58B19
            C2710CBB5B00AA4600D9B9A0FFFFFFFFFFFFFFFFFF20FFFFFFE0F3E2A4E4AA84
            D68C42BD4162C45B93B00AB7C51CE1E49AF0F3CDF2E1A0CA7521B55102AF3300
            EBE1D3FFFFFFFEFDFC20FFFFFFEDFBF11EAE2D15AD1E31BC4C8FDC90F4F8ACFF
            FFFFFFFFFFFFFFFFFFFFFFFCEFD8C56A14B25207BA5310CD8348EED9C720FFFF
            FFECFBF127B9442DB53544BE4CC5EDCBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEED
            D7B3C1772FBC6724AF4500CD8F5AFDFAF420FFFFFFA0E7BF17B64335BE4271D1
            75D5F2D8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFEF7E8BDD3AA4FC07C2CAF4F01F1
            D8CBFFFFFF20FFFFFF62DC9F22C05761D372FAFDFAF9FDF9FFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFF1EFE58A56C76917EAB0D3FFFFFF20FFFFFF6EE2AE
            1DC760A4E8B8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9
            FEFF4BB3C33A54D28FC3FFFAFF20FFFFFFADF5D735D67D5BCEA1FCFEFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAFFE236AE980E77CE9CD1FDFA
            FD20FFFFFFE5FDF25EEBA333B58596D9DBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
            FFFFFFFFFFFFFCE7F9A92987882A9BD6B6E0FFFFFF20FFFFFFFFFFFF98F3CD69
            CD9A00949784E5FDFFFFFFFFFFFFEEE0FCE0CEF6FFFFFFFFFFFFD193D17D27AE
            6A20ACF7F1FAFFFFFF20FFFFFFFFFFFFF6FEFDBDF9D33AA7930091C48EC7FDD3
            B6F57F5BD5AB91E7E7DBFEB68DE86C2AC54D0AB5C0A1E8FFFFFFFFFFFF20FFFF
            FFFFFFFFFFFFFFFEFFFFC7F5D83A8FB27852E67459DA6F5AD26646D3582CCE41
            12C03500B4A17AE2FFFFFFFFFFFFFFFFFF20FFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFF0FDF499B2E15738DA4E37D53217C92C0DBB360DBBB49EE7FFFFFFFFFFFFFF
            FFFFFFFFFF20FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA9A3EF1F0D
            CAA296E2C4B9F0F6F5FCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF20FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFEFDCDC9F7FFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFF20}
          OnClick = BtnConvertClick
        end
        object GroupBoxRawData: TGroupBox
          Left = 8
          Top = 63
          Width = 316
          Height = 57
          Anchors = [akLeft, akTop, akRight, akBottom]
          Caption = #28304#25968#25454#65288'Stream or Rinex File'#65289
          TabOrder = 0
          object BtnInFileView: TSpeedButton
            Left = 286
            Top = 24
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnInFileViewClick
          end
          object InFile: TEdit
            Left = 3
            Top = 25
            Width = 279
            Height = 21
            TabOrder = 0
            OnChange = InFileChange
          end
        end
        object GroupBoxFormat: TGroupBox
          Left = 194
          Top = 2
          Width = 130
          Height = 55
          Anchors = [akTop, akRight]
          BiDiMode = bdLeftToRight
          Caption = #25968#25454#26684#24335
          ParentBiDiMode = False
          TabOrder = 1
          DesignSize = (
            130
            55)
          object ComFormat: TComboBox
            Left = 8
            Top = 25
            Width = 113
            Height = 21
            Style = csDropDownList
            Anchors = [akTop, akRight]
            TabOrder = 0
            OnChange = ComFormatChange
          end
        end
      end
      object Panel212: TPanel
        Left = 0
        Top = 126
        Width = 329
        Height = 254
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object GroupBoxConvData: TGroupBox
          Left = 8
          Top = 0
          Width = 317
          Height = 252
          Caption = #36716#25442#21518#25968#25454#65288'Obs'#65292'Nav of GPS-GLO-BDS-QZSS-GAL-SBAS'#65289
          TabOrder = 0
          object BtnOutFileView1: TSpeedButton
            Left = 286
            Top = 24
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnOutFileView1Click
          end
          object BtnOutFileView2: TSpeedButton
            Left = 286
            Top = 51
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnOutFileView2Click
          end
          object BtnOutFileView3: TSpeedButton
            Left = 286
            Top = 78
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnOutFileView3Click
          end
          object BtnOutFileView4: TSpeedButton
            Left = 286
            Top = 105
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnOutFileView4Click
          end
          object BtnOutFileView5: TSpeedButton
            Left = 286
            Top = 144
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnOutFileView5Click
          end
          object BtnOutFileView6: TSpeedButton
            Left = 286
            Top = 184
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnOutFileView6Click
          end
          object BtnOutFileView7: TSpeedButton
            Left = 286
            Top = 220
            Width = 23
            Height = 22
            Glyph.Data = {
              72020000424D720200000000000042000000280000000A0000000E0000000100
              20000300000030020000130B0000130B000000000000000000000000FF0000FF
              0000FF000000D2073700BF073700AB0637009B0936008709350085001F006A1D
              54001F5FD5002650C89F5C9CE7FACE032900B50014009F001B008C001C007500
              1D0065001A00710009003C378E313889F4FF86CDF9D1DD375BD3DA7D8AF2CE68
              77DEC36571DDB7636CDDB56A68DCA84B4CD44652AFEB64C1FFFF8E4D6988F57C
              97F0FFFFFFFFFFFFFBFFFFFFE7FFFFFFDDFFFFFFC8FFF0EDBEFF6DB1F6FFAFCE
              D0FF9A1C258CFB7791EFF8FFFFFFF8FAF1FFF9FCE4FFF2E4BFFFEED9A0FFFBF8
              E3FFFAF8E6FFEED499FF8C1D3A8BFB8294EFF8FFFFFFF9FAFAFFF8F7F5FFEED9
              AAFFF2E980FFF8FBD1FFFFFFD2FFEFCEA1FF85204089FC8F99EFF8FFFFFFF9FA
              FDFFFAFDFFFFF1E0CDFFEDD780FFF2E980FFF5E7A1FFEED5B0FF8E204388FC9A
              9EEFF8FFFFFFF9FAFAFFF9FBFCFFF8F7F7FFF1E0CAFFEED8A9FFF7F1C0FFF3E7
              B9FF9E1C4187FCA5A2EFF8FFFFFFF9F9F9FFF9F8FAFFF9FAF8FFF9FFFEFFF7FF
              FDFFFEFFEDFFF7F8CAFFAF1E4384FCB0A6EFF8FFFFFFF9F9F9FFF9F9FAFFF9FF
              FDFFF9E1E8FFF7BBD3FFF4D1CDFFEDC9B5FFC0194184FCBBA9F0F8FFFFFFF9F9
              F9FFF9FBFBFFF8FFFFFFFD8283FEFC2B06FDF15147FFE11D48FFCA003656FCC6
              ACF0F8FFFFFFF9F9F9FFF9FAFAFFF8FFFFFFFC9786FDFFA700FFFF6A22FFEC00
              3B6BC9033500FCD5B3F0F7FFFFFFF8FFFFFFF8FFFFFFF7FFFFFFFCBCAEFFFF7F
              35FFFF102F6AEC003700C70B3800FECB94E4FBDDC6FFFCCDB7F2FCC5B4F2FCC7
              BCF6FE8F82FFFF37526BFF0B4200EB033300C70A3700}
            OnClick = BtnOutFileView7Click
          end
          object OutFile1: TEdit
            Left = 24
            Top = 25
            Width = 258
            Height = 21
            TabOrder = 0
          end
          object OutFileEna1: TCheckBox
            Left = 6
            Top = 27
            Width = 17
            Height = 17
            TabOrder = 1
          end
          object OutFile2: TEdit
            Left = 24
            Top = 52
            Width = 258
            Height = 21
            TabOrder = 2
          end
          object OutFileEna2: TCheckBox
            Left = 6
            Top = 54
            Width = 17
            Height = 17
            TabOrder = 3
          end
          object OutFile3: TEdit
            Left = 24
            Top = 79
            Width = 258
            Height = 21
            TabOrder = 4
          end
          object OutFileEna3: TCheckBox
            Left = 6
            Top = 81
            Width = 17
            Height = 17
            TabOrder = 5
          end
          object OutFile4: TEdit
            Left = 24
            Top = 106
            Width = 258
            Height = 21
            TabOrder = 6
          end
          object OutFileEna4: TCheckBox
            Left = 6
            Top = 108
            Width = 17
            Height = 17
            TabOrder = 7
          end
          object OutFile5: TEdit
            Left = 24
            Top = 145
            Width = 258
            Height = 21
            TabOrder = 8
          end
          object OutFileEna5: TCheckBox
            Left = 6
            Top = 147
            Width = 17
            Height = 17
            TabOrder = 9
          end
          object OutFile6: TEdit
            Left = 24
            Top = 185
            Width = 258
            Height = 21
            TabOrder = 10
          end
          object OutFileEna6: TCheckBox
            Left = 6
            Top = 187
            Width = 17
            Height = 17
            TabOrder = 11
          end
          object OutFile7: TEdit
            Left = 24
            Top = 220
            Width = 258
            Height = 21
            TabOrder = 12
          end
          object OutFileEna7: TCheckBox
            Left = 6
            Top = 220
            Width = 17
            Height = 17
            TabOrder = 13
          end
        end
      end
    end
    object Panel22: TPanel
      Left = 331
      Top = 0
      Width = 463
      Height = 384
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 1
      object GroupBoxConvOpt: TGroupBox
        Left = 4
        Top = 4
        Width = 453
        Height = 374
        Caption = #25968#25454#36716#25442#35774#32622
        TabOrder = 0
        object PanelRnxVer: TPanel
          Left = 12
          Top = 20
          Width = 157
          Height = 21
          BevelOuter = bvNone
          TabOrder = 0
          object Label1: TLabel
            Left = 6
            Top = 3
            Width = 68
            Height = 13
            Caption = 'RINEX Version'
          end
          object ComRnxVer: TComboBox
            Left = 80
            Top = 0
            Width = 77
            Height = 21
            Style = csDropDownList
            TabOrder = 0
            OnChange = ComRnxVerChange
            Items.Strings = (
              '2.10'
              '2.11'
              '2.12'
              '3.00'
              '3.01'
              '3.02'
              '3.03')
          end
        end
        object PanelRnxCode: TPanel
          Left = 193
          Top = 20
          Width = 147
          Height = 21
          AutoSize = True
          BevelOuter = bvNone
          TabOrder = 1
          object Label2: TLabel
            Left = 0
            Top = 3
            Width = 48
            Height = 13
            Caption = 'Station ID'
          end
          object EditRnxCode: TEdit
            Left = 54
            Top = 0
            Width = 93
            Height = 21
            TabOrder = 0
          end
        end
        object PanelRnxFile: TPanel
          Left = 350
          Top = 20
          Width = 98
          Height = 21
          BevelOuter = bvNone
          TabOrder = 2
          object CheckRnxFile: TCheckBox
            Left = 19
            Top = 0
            Width = 79
            Height = 21
            Align = alRight
            BiDiMode = bdLeftToRight
            Caption = 'RINEX Name'
            ParentBiDiMode = False
            TabOrder = 0
          end
        end
        object PanelMarker: TPanel
          Left = 12
          Top = 47
          Width = 141
          Height = 21
          BevelOuter = bvNone
          TabOrder = 3
          object Label3: TLabel
            Left = 4
            Top = 3
            Width = 132
            Height = 13
            Caption = 'Marker Name/Number/Type'
          end
        end
        object EditMarker: TEdit
          Left = 159
          Top = 47
          Width = 93
          Height = 21
          TabOrder = 4
        end
        object EditMarkerNo: TEdit
          Left = 258
          Top = 47
          Width = 93
          Height = 21
          TabOrder = 5
        end
        object EditMarkerType: TEdit
          Left = 357
          Top = 47
          Width = 93
          Height = 21
          TabOrder = 6
        end
        object PanelROA: TPanel
          Left = 12
          Top = 70
          Width = 141
          Height = 21
          BevelOuter = bvNone
          TabOrder = 7
          object Label4: TLabel
            Left = 4
            Top = 3
            Width = 120
            Height = 13
            Caption = 'RunBy/Observer/Agency'
          end
        end
        object EditName1: TEdit
          Left = 357
          Top = 70
          Width = 93
          Height = 21
          TabOrder = 8
        end
        object EditName0: TEdit
          Left = 258
          Top = 70
          Width = 93
          Height = 21
          TabOrder = 9
        end
        object EditRunBy: TEdit
          Left = 159
          Top = 70
          Width = 93
          Height = 21
          TabOrder = 10
        end
        object PanelRec: TPanel
          Left = 12
          Top = 92
          Width = 141
          Height = 21
          BevelOuter = bvNone
          TabOrder = 11
          object Label5: TLabel
            Left = 4
            Top = 3
            Width = 82
            Height = 13
            Caption = 'Rec #/Type/Vers'
          end
        end
        object EditRec2: TEdit
          Left = 357
          Top = 93
          Width = 93
          Height = 21
          TabOrder = 12
        end
        object EditRec1: TEdit
          Left = 258
          Top = 93
          Width = 93
          Height = 21
          TabOrder = 13
        end
        object EditRec0: TEdit
          Left = 159
          Top = 93
          Width = 93
          Height = 21
          TabOrder = 14
        end
        object PanelAnt: TPanel
          Left = 12
          Top = 116
          Width = 141
          Height = 21
          BevelOuter = bvNone
          TabOrder = 15
          object Label6: TLabel
            Left = 4
            Top = 3
            Width = 56
            Height = 13
            Caption = 'Ant #/Type'
          end
        end
        object EditAnt2: TEdit
          Left = 357
          Top = 116
          Width = 93
          Height = 21
          TabOrder = 16
        end
        object EditAnt1: TEdit
          Left = 258
          Top = 116
          Width = 93
          Height = 21
          TabOrder = 17
        end
        object EditAnt0: TEdit
          Left = 159
          Top = 116
          Width = 93
          Height = 21
          TabOrder = 18
        end
        object PanelXYZ: TPanel
          Left = 12
          Top = 138
          Width = 141
          Height = 21
          BevelOuter = bvNone
          TabOrder = 19
          object Label7: TLabel
            Left = 4
            Top = 3
            Width = 96
            Height = 13
            Caption = 'Apporx Position XYZ'
          end
        end
        object EditAppPos1: TEdit
          Left = 258
          Top = 138
          Width = 93
          Height = 21
          TabOrder = 20
        end
        object EditAppPos2: TEdit
          Left = 357
          Top = 138
          Width = 93
          Height = 21
          TabOrder = 21
        end
        object EditAppPos0: TEdit
          Left = 159
          Top = 138
          Width = 93
          Height = 21
          TabOrder = 22
        end
        object PanelHEN: TPanel
          Left = 12
          Top = 160
          Width = 141
          Height = 21
          BevelOuter = bvNone
          TabOrder = 23
          object Label8: TLabel
            Left = 4
            Top = 3
            Width = 104
            Height = 13
            Caption = 'Antenna: Delta H/E/N'
          end
        end
        object EditAntDel2: TEdit
          Left = 357
          Top = 160
          Width = 93
          Height = 21
          TabOrder = 24
        end
        object EditAntDel1: TEdit
          Left = 258
          Top = 160
          Width = 93
          Height = 21
          TabOrder = 25
        end
        object EditAntDel0: TEdit
          Left = 159
          Top = 160
          Width = 93
          Height = 21
          TabOrder = 26
        end
        object GroupBoxNavSys: TGroupBox
          Left = 12
          Top = 232
          Width = 241
          Height = 94
          Caption = #21355#26143#23548#33322#31995#32479
          TabOrder = 27
          object LabelExSats: TLabel
            Left = 13
            Top = 68
            Width = 114
            Height = 13
            Caption = #21024#38500#21355#26143#21495'( , '#38548#24320')'#65306
          end
          object NavSys1: TCheckBox
            Left = 13
            Top = 19
            Width = 69
            Height = 17
            Caption = 'GPS'
            TabOrder = 0
          end
          object NavSys2: TCheckBox
            Left = 81
            Top = 19
            Width = 69
            Height = 17
            Caption = 'GLONASS'
            TabOrder = 1
          end
          object NavSys5: TCheckBox
            Left = 170
            Top = 42
            Width = 69
            Height = 17
            Caption = 'SBAS'
            TabOrder = 4
          end
          object NavSys3: TCheckBox
            Left = 170
            Top = 19
            Width = 69
            Height = 17
            Caption = 'Galileo'
            TabOrder = 2
          end
          object NavSys4: TCheckBox
            Left = 81
            Top = 42
            Width = 69
            Height = 17
            Caption = 'QZSS'
            TabOrder = 3
          end
          object NavSys6: TCheckBox
            Left = 13
            Top = 42
            Width = 69
            Height = 17
            Caption = 'BeiDou'
            TabOrder = 5
          end
          object EditExSats: TEdit
            Left = 127
            Top = 65
            Width = 98
            Height = 21
            TabOrder = 6
          end
        end
        object GroupBoxTimeFirst: TGroupBox
          Left = 12
          Top = 184
          Width = 165
          Height = 43
          Caption = 'Time of First Obs'
          TabOrder = 28
          object FirstTimeH1: TEdit
            Left = 86
            Top = 19
            Width = 55
            Height = 21
            TabOrder = 0
            Text = '00:00:00'
          end
          object FirstTimeH1UD: TUpDown
            Left = 141
            Top = 18
            Width = 17
            Height = 23
            Min = -32000
            Max = 32000
            TabOrder = 1
            Wrap = True
            OnChangingEx = FirstTimeH1UDChangingEx
          end
          object FirstTimeY1: TEdit
            Left = 4
            Top = 19
            Width = 65
            Height = 21
            TabOrder = 2
            Text = '2000/01/01'
          end
          object FirstTimeY1UD: TUpDown
            Left = 69
            Top = 18
            Width = 17
            Height = 23
            Min = -32000
            Max = 32000
            TabOrder = 3
            Wrap = True
            OnChangingEx = FirstTimeY1UDChangingEx
          end
        end
        object GroupBoxFre: TGroupBox
          Left = 254
          Top = 232
          Width = 196
          Height = 94
          Caption = #39057#28857
          TabOrder = 29
          object Freq1: TCheckBox
            Left = 14
            Top = 17
            Width = 53
            Height = 17
            Caption = 'L1'
            TabOrder = 0
          end
          object Freq2: TCheckBox
            Left = 70
            Top = 17
            Width = 53
            Height = 17
            Caption = 'L2'
            TabOrder = 1
          end
          object Freq3: TCheckBox
            Left = 132
            Top = 17
            Width = 53
            Height = 17
            Caption = 'L5/L3'
            TabOrder = 2
          end
          object Freq6: TCheckBox
            Left = 132
            Top = 42
            Width = 53
            Height = 17
            Caption = 'L8'
            TabOrder = 3
          end
          object Freq5: TCheckBox
            Left = 70
            Top = 42
            Width = 53
            Height = 17
            Caption = 'L7'
            TabOrder = 4
          end
          object Freq4: TCheckBox
            Left = 14
            Top = 42
            Width = 53
            Height = 17
            Caption = 'L6'
            TabOrder = 5
          end
          object CheckScanObs: TCheckBox
            Left = 14
            Top = 69
            Width = 97
            Height = 18
            Caption = 'Scan Obs Types'
            Checked = True
            State = cbChecked
            TabOrder = 6
          end
          object BtnMask: TButton
            Left = 124
            Top = 67
            Width = 63
            Height = 23
            Caption = #36890#36947#35774#32622
            TabOrder = 7
            OnClick = BtnMaskClick
          end
        end
        object GroupBoxTimeLast: TGroupBox
          Left = 176
          Top = 184
          Width = 165
          Height = 43
          Caption = 'Time of Last Obs'
          TabOrder = 30
          object LastTimeH1: TEdit
            Left = 86
            Top = 19
            Width = 55
            Height = 21
            TabOrder = 0
            Text = '00:00:00'
          end
          object LastTimeH1UD: TUpDown
            Left = 141
            Top = 18
            Width = 17
            Height = 23
            Min = -32000
            Max = 32000
            TabOrder = 1
            Wrap = True
            OnChangingEx = LastTimeH1UDChangingEx
          end
          object LastTimeY1: TEdit
            Left = 4
            Top = 19
            Width = 65
            Height = 21
            TabOrder = 2
            Text = '2000/01/01'
          end
          object LastTimeY1UD: TUpDown
            Left = 69
            Top = 18
            Width = 17
            Height = 23
            Min = -32000
            Max = 32000
            TabOrder = 3
            Wrap = True
            OnChangingEx = LastTimeY1UDChangingEx
          end
        end
        object GroupBoxObsType: TGroupBox
          Left = 3
          Top = 332
          Width = 286
          Height = 40
          Caption = #35266#27979#37327#31867#22411
          TabOrder = 31
          object Obs1: TCheckBox
            Left = 10
            Top = 16
            Width = 55
            Height = 15
            Caption = 'C-'#20266#36317
            TabOrder = 0
          end
          object Obs2: TCheckBox
            Left = 70
            Top = 16
            Width = 55
            Height = 15
            Caption = 'L-'#30456#20301
            TabOrder = 1
          end
          object Obs3: TCheckBox
            Left = 130
            Top = 16
            Width = 69
            Height = 15
            Caption = 'D-'#22810#26222#21202
            TabOrder = 2
          end
          object Obs4: TCheckBox
            Left = 204
            Top = 16
            Width = 75
            Height = 15
            Caption = 'S-'#20449#21495#24378#24230
            TabOrder = 3
          end
        end
        object PanelIL: TPanel
          Left = 346
          Top = 189
          Width = 105
          Height = 43
          BevelOuter = bvNone
          TabOrder = 32
          object PanelInterval: TPanel
            Left = 1
            Top = 1
            Width = 101
            Height = 21
            BevelOuter = bvNone
            TabOrder = 0
            object Label9: TLabel
              Left = 0
              Top = 3
              Width = 38
              Height = 13
              Caption = 'Interval'
            end
            object EditInterval: TEdit
              Left = 44
              Top = 0
              Width = 57
              Height = 21
              TabOrder = 0
            end
          end
          object PanelLeapSec: TPanel
            Left = 1
            Top = 22
            Width = 101
            Height = 21
            BevelOuter = bvNone
            TabOrder = 1
            object Label10: TLabel
              Left = 0
              Top = 3
              Width = 40
              Height = 13
              Caption = 'LeapSec'
            end
            object EditLeapSec: TEdit
              Left = 44
              Top = 0
              Width = 57
              Height = 21
              TabOrder = 0
            end
          end
        end
        object PanelBtn: TPanel
          Left = 295
          Top = 333
          Width = 158
          Height = 35
          BevelOuter = bvNone
          TabOrder = 33
          object BtnCancel: TButton
            Left = 80
            Top = 5
            Width = 66
            Height = 25
            Caption = #24674#22797#40664#35748
            TabOrder = 0
            OnClick = BtnCancelClick
          end
          object BtnOk: TButton
            Left = 9
            Top = 5
            Width = 66
            Height = 25
            Caption = #36827#34892#35774#32622
            TabOrder = 1
            OnClick = BtnOkClick
          end
        end
      end
    end
  end
  object OpenDialog: TOpenDialog
    Filter = 
      #25152#26377#25991#20214' (*.*)|*.*|RTCM 2'#26684#24335#25991#20214' (*.rtcm2)|*.rtcm2|RTCM 3 '#26684#24335#25991#20214'(*.rtcm3)' +
      '|*.rtcm3|NovtAtel '#26684#24335#25991#20214'(*.gps)|*.gps|ublox'#26684#24335#25991#20214' (*.ubx)|*.ubx|Supe' +
      'rStart II'#26684#24335#25991#20214' (*.log)|*.log|Hemisphere'#26684#24335#25991#20214' (*.bin)|*.bin|Javad'#26684#24335 +
      #25991#20214' (*.jps)|*.jps|RINEX'#35266#27979#25968#25454#25991#20214' (*.obs,*.*O)|*.obs;*.*O'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Left = 294
    Top = 51
  end
end

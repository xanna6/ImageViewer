object FullScreen: TFullScreen
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'FullScreen'
  ClientHeight = 480
  ClientWidth = 640
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  WindowState = wsMaximized
  OnKeyPress = FormKeyPress
  TextHeight = 15
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 640
    Height = 480
    Align = alClient
    Center = True
    Proportional = True
    ExplicitLeft = 224
    ExplicitTop = 8
    ExplicitWidth = 401
    ExplicitHeight = 281
  end
end

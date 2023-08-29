//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	JPEGImage1 = new TJPEGImage;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenExecute(TObject *Sender)
{
	if(OpenPictureDialog1->Execute()) {
		//Je¿eli u¿ytkownik wska¿e poprawny plik mo¿emy go otworzyæ i za³adowaæ
		//do zmiennej JPEGImage1
		JPEGImage1->LoadFromFile(OpenPictureDialog1->FileName);
		Image1->Picture->Assign(JPEGImage1);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
    JPEGImage1->LoadFromFile(FileListBox1->FileName);
	Image1->Picture->Assign(JPEGImage1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveExecute(TObject *Sender)
{
	if(SavePictureDialog1->Execute()) {
		JPEGImage1->SaveToFile(SavePictureDialog1->FileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
		  TPoint &MousePos, bool &Handled)
{
	TPoint MousePosImg = Image1->ScreenToClient(MousePos);
	StatusBar1->Panels->Items[0]->Text = "x: " + IntToStr((int)MousePosImg.x);
	StatusBar1->Panels->Items[1]->Text = "y: " + IntToStr((int)MousePosImg.y);
	StatusBar1->Panels->Items[2]->Text = "delta: " + IntToStr(WheelDelta);
	//StatusBar1->Panels->Items[0]->Text = "MousePos x: " + IntToStr((int) MousePos.x) + " y: " + IntToStr((int) MousePos.y);
	//StatusBar1->Panels->Items[1]->Text = "ImgPos x: " + IntToStr((int) Image1->Left) + " y: " + IntToStr((int) Image1->Top);
	//StatusBar1->Panels->Items[2]->Text = "MousePos x: " + IntToStr((int) MousePosImg.x) + " y: " + IntToStr((int) MousePosImg.y);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	mousePos.x = X;
	mousePos.y = Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	//rysujemy tylko je¿eli wciœniety jest lewy przycisk myszy
	if ( Shift.Contains(ssLeft))
	{
		//przerysowanie poprzedniego prostok¹ta
		Image1->Canvas->Draw(0, 0 , JPEGImage1 );
		Image1->Canvas->DrawFocusRect(lastRect);
		// zapamiêtanie nowego prostok¹ta
		lastRect.Left=mousePos.x;
		lastRect.Right=X;
		lastRect.Top=mousePos.y;
		lastRect.Bottom=Y;
		//rysowanie nowego prostok¹ta
		Image1->Canvas->DrawFocusRect(lastRect);
	}
}
//---------------------------------------------------------------------------

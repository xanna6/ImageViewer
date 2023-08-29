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
		//Jeżeli użytkownik wskaże poprawny plik możemy go otworzyć i załadować
		//do zmiennej JPEGImage1
		JPEGImage1->LoadFromFile(OpenPictureDialog1->FileName);
		Image1->Picture->Bitmap->Assign(JPEGImage1);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
    JPEGImage1->LoadFromFile(FileListBox1->FileName);
	Image1->Picture->Bitmap->Assign(JPEGImage1);
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
//	StatusBar1->Panels->Items[0]->Text = "x: " + IntToStr((int)MousePosImg.x);
//	StatusBar1->Panels->Items[1]->Text = "y: " + IntToStr((int)MousePosImg.y);
//	StatusBar1->Panels->Items[2]->Text = "delta: " + IntToStr(WheelDelta);
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
	//rysujemy tylko jeżeli wciśniety jest lewy przycisk myszy
	if ( Shift.Contains(ssLeft))
	{
		//przerysowanie poprzedniego prostokąta
		Image1->Canvas->DrawFocusRect(lastRect);
		// zapamiętanie nowego prostokąta
		lastRect.Left=mousePos.x;
		lastRect.Right=X;
		lastRect.Top=mousePos.y;
		lastRect.Bottom=Y;
		//rysowanie nowego prostokąta
		Image1->Canvas->DrawFocusRect(lastRect);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(X >= mousePos.x && Y >= mousePos.y) {
       Image1->SetBounds(lastRect.Left, lastRect.Top, lastRect.Right, lastRect.Bottom);
		Image1->Canvas->CopyRect(Image1->ClientRect, Image1->Canvas, lastRect);
	}
}
//---------------------------------------------------------------------------

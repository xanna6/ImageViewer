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
	zoom = 1.0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenExecute(TObject *Sender)
{
	if(OpenPictureDialog1->Execute()) {
		//Jeżeli użytkownik wskaże poprawny plik możemy go otworzyć i załadować
		//do zmiennej JPEGImage1
		JPEGImage1->LoadFromFile(OpenPictureDialog1->FileName);
		Image1->Picture->Bitmap->Assign(JPEGImage1);
		imgTopLeft.x = 0;
		imgTopLeft.y = 0;
		zoom = 1.0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
    JPEGImage1->LoadFromFile(FileListBox1->FileName);
	Image1->Picture->Bitmap->Assign(JPEGImage1);
    imgTopLeft.x = 0;
	imgTopLeft.y = 0;
	zoom = 1.0;
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

	double skok = 1.1; //zakładamy wartość skoku przy zoomowaniu
	/*zmienna WheelDelta przyjmuje wartości dodatnie lub ujemne w zależności
	od kierunku obrotu kółka myszy. Załóżmy, że rozmiar będzie zmniejszany lub
	zwiększany o stały współczynnik skok = 1,1*/
	if (WheelDelta<0) {
		zoom = zoom/skok;
	} else {
		zoom = zoom*skok;
	}

	SkalujIPrzerysuj(Image1, JPEGImage1, zoom, imgTopLeft);
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
	if ( Shift.Contains(ssRight)) {
		imgTopLeft.x = imgTopLeft.x + X - mousePos.x;
		imgTopLeft.y = imgTopLeft.y + Y - mousePos.y;

		//przerysowywanie obrazka podczas przesuwania myszy
		Image1->Canvas->Brush->Color = clAppWorkSpace;
		Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
		Image1->Canvas->Draw(imgTopLeft.x, imgTopLeft.y, JPEGImage1);

		mousePos.x = X;
		mousePos.y = Y;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Shift.Contains(ssLeft) && (X >= mousePos.x && Y >= mousePos.y)) {
	   Image1->Canvas->CopyRect(Image1->ClientRect, Image1->Canvas, lastRect);
	}
}
//---------------------------------------------------------------------------

void TForm1::SkalujIPrzerysuj(TImage *Image1, TJPEGImage *JPEGImage1, double zoom, TPoint &imgTopLeft) {
	TBitmap *Bitmap1;
	Bitmap1 = new TBitmap();
	Bitmap1->Assign(JPEGImage1);

	Bitmap1->Width = int(JPEGImage1->Width * zoom);
	Bitmap1->Height = int(JPEGImage1->Height * zoom);

    Image1->Canvas->Brush->Color = clAppWorkSpace;
	Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
	Image1->Canvas->StretchDraw(Rect(imgTopLeft.x, imgTopLeft.y, Bitmap1->Width, Bitmap1->Height), JPEGImage1);

	delete Bitmap1;
}

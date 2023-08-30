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
		//Je�eli u�ytkownik wska�e poprawny plik mo�emy go otworzy� i za�adowa�
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
	StatusBar1->Panels->Items[0]->Text = "MousePos x: " + IntToStr((int) MousePos.x) + " y: " + IntToStr((int) MousePos.y);
	StatusBar1->Panels->Items[1]->Text = "ImgPos x: " + IntToStr((int) imgTopLeft.x) + " y: " + IntToStr((int) imgTopLeft.y);
	StatusBar1->Panels->Items[2]->Text = "MousePosImg x: " + IntToStr((int) MousePosImg.x) + " y: " + IntToStr((int) MousePosImg.y);

	double skok = 1.1; //zak�adamy warto�� skoku przy zoomowaniu
	/*zmienna WheelDelta przyjmuje warto�ci dodatnie lub ujemne w zale�no�ci
	od kierunku obrotu k�ka myszy. Za��my, �e rozmiar b�dzie zmniejszany lub
	zwi�kszany o sta�y wsp�czynnik skok = 1,1*/
	double zoomBefore = zoom;
	if (WheelDelta<0) {
		zoom = zoom/skok;
	} else {
		zoom = zoom*skok;
	}

	ObliczPozycje(imgTopLeft, MousePosImg, zoomBefore, zoom);
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
	//zmiana wspolrzednych w statusBarze
	StatusBar1->Panels->Items[0]->Text = "MousePos x: " + IntToStr((int) X) + " y: " + IntToStr((int) Y);
	StatusBar1->Panels->Items[1]->Text = "ImgPos x: " + IntToStr((int) imgTopLeft.x) + " y: " + IntToStr((int) imgTopLeft.y);
	StatusBar1->Panels->Items[2]->Text = "";

	//rysujemy tylko je�eli wci�niety jest lewy przycisk myszy
	if ( Shift.Contains(ssLeft))
	{
		//przerysowanie poprzedniego prostok�ta
		Image1->Canvas->DrawFocusRect(lastRect);
		// zapami�tanie nowego prostok�ta
		lastRect.Left=mousePos.x;
		lastRect.Right=X;
		lastRect.Top=mousePos.y;
		lastRect.Bottom=Y;
		//rysowanie nowego prostok�ta
		Image1->Canvas->DrawFocusRect(lastRect);
	}
	if ( Shift.Contains(ssRight)) {
		imgTopLeft.x = imgTopLeft.x + X - mousePos.x;
		imgTopLeft.y = imgTopLeft.y + Y - mousePos.y;

		SkalujIPrzerysuj(Image1, JPEGImage1, zoom, imgTopLeft);

		mousePos.x = X;
		mousePos.y = Y;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft && (X >= mousePos.x && Y >= mousePos.y)) {
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
	Image1->Canvas->StretchDraw(Rect(imgTopLeft.x, imgTopLeft.y,
								 Bitmap1->Width + imgTopLeft.x, Bitmap1->Height + imgTopLeft.y), JPEGImage1);

	delete Bitmap1;
}
//---------------------------------------------------------------------------
void TForm1::ObliczPozycje(TPoint &imgTopLeft, TPoint mousePos, double zoomBef, double zoomAft) {
    /*zmienna zoomBef oznacza poprzedni� warto�� skali, a zmienna zoomAft
	now� warto�� skali po ruchu k�ka myszki */
	imgTopLeft.x = int ((imgTopLeft.x - mousePos.x)*zoomAft/zoomBef + mousePos.x);
	imgTopLeft.y = int ((imgTopLeft.y - mousePos.y)*zoomAft/zoomBef + mousePos.y);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RotateLeftExecute(TObject *Sender)
{
	//definiujemy nowy typ, kt�ry b�dzie tr�jelementow� tablic� bajt�w
	typedef Byte TByteTriple[3];
	TByteTriple *PixelNew, *PixelOld;
	TBitmap *Bitmap1, *Bitmap2;
	Bitmap1 = new TBitmap();
	Bitmap2 = new TBitmap();

	Bitmap1->Assign(JPEGImage1);
	Bitmap2->Width =Bitmap1->Height;
	Bitmap2->Height =Bitmap1->Width;

	//koniecznie musimy ustawi� rozmiar piksela na 24 bity czyli 3 bajty
	Bitmap1->PixelFormat=pf24bit;
	Bitmap2->PixelFormat=pf24bit;
	for(int j=0; j<Bitmap2->Height; j++) {
		//pobieramy wska�nik do pierwszego piksela j-tej lini nowego obrazu
		PixelNew = (TByteTriple *) Bitmap2->ScanLine[j];
		for(int i=0; i<Bitmap1->Height; i++) {
			//pobieramy wska�nik do pierwszego piksela i-tej lini starego obrazu
			PixelOld= (TByteTriple *)Bitmap1->ScanLine[i];
			//przepisujemy zawarto�� 3 bajt�w pami�ci, ze starego obrazu do nowego
			PixelNew[i][0] = PixelOld[Bitmap1->Width-j-1][0];
			PixelNew[i][1] = PixelOld[Bitmap1->Width-j-1][1];
			PixelNew[i][2] = PixelOld[Bitmap1->Width-j-1][2];
		}
	}
	JPEGImage1->Assign(Bitmap2);

	//rysowanie odwr�conego obrazu
	SkalujIPrzerysuj(Image1, JPEGImage1, zoom, imgTopLeft);

	delete(Bitmap1);
	delete(Bitmap2);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RotateRightExecute(TObject *Sender)
{
	//definiujemy nowy typ, kt�ry b�dzie tr�jelementow� tablic� bajt�w
	typedef Byte TByteTriple[3];
	TByteTriple *PixelNew, *PixelOld;
	TBitmap *Bitmap1, *Bitmap2;
	Bitmap1 = new TBitmap();
	Bitmap2 = new TBitmap();

	Bitmap1->Assign(JPEGImage1);
	Bitmap2->Width =Bitmap1->Height;
	Bitmap2->Height =Bitmap1->Width;

	//koniecznie musimy ustawi� rozmiar piksela na 24 bity czyli 3 bajty
	Bitmap1->PixelFormat=pf24bit;
	Bitmap2->PixelFormat=pf24bit;
	for(int j=0; j<Bitmap2->Height; j++) {
		//pobieramy wska�nik do pierwszego piksela j-tej lini nowego obrazu
		PixelNew = (TByteTriple *) Bitmap2->ScanLine[j];
		for(int i=0; i<Bitmap1->Height; i++) {
			//pobieramy wska�nik do pierwszego piksela i-tej lini starego obrazu
			PixelOld= (TByteTriple *)Bitmap1->ScanLine[i];
			//przepisujemy zawarto�� 3 bajt�w pami�ci, ze starego obrazu do nowego
			PixelNew[Bitmap2->Width-i-1][0] = PixelOld[j][0];
			PixelNew[Bitmap2->Width-i-1][1] = PixelOld[j][1];
			PixelNew[Bitmap2->Width-i-1][2] = PixelOld[j][2];
		}
	}
	JPEGImage1->Assign(Bitmap2);

	//rysowanie odwr�conego obrazu
	SkalujIPrzerysuj(Image1, JPEGImage1, zoom, imgTopLeft);

    delete(Bitmap1);
	delete(Bitmap2);
}
//---------------------------------------------------------------------------


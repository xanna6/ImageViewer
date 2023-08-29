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
    if(OpenPictureDialog1->Execute())
{
	//Je¿eli u¿ytkownik wska¿e poprawny plik mo¿emy go otworzyæ i za³dowaæ
	//do zmiennej JPEGImage1
	JPEGImage1->LoadFromFile(OpenPictureDialog1->FileName);
	Image1->Canvas->Draw(0, 0 , JPEGImage1 );
}
//---------------------------------------------------------------------------

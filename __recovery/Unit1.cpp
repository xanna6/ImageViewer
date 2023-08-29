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
//		Image1->Picture->SaveToFile(SavePictureDialog1->FileName);
	}
}
//---------------------------------------------------------------------------

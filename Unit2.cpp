//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFullScreen *FullScreen;
//---------------------------------------------------------------------------
__fastcall TFullScreen::TFullScreen(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFullScreen::FormKeyPress(TObject *Sender, System::WideChar &Key)

{
	if (Key == char(27)) {
		Close();
    }
}
//---------------------------------------------------------------------------

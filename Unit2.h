//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFullScreen : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TFullScreen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFullScreen *FullScreen;
//---------------------------------------------------------------------------
#endif

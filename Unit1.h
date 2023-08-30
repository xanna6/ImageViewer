//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Jpeg.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Unit2.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TDriveComboBox *DriveComboBox1;
	TDirectoryListBox *DirectoryListBox1;
	TFileListBox *FileListBox1;
	TFilterComboBox *FilterComboBox1;
	TImage *Image1;
	TStatusBar *StatusBar1;
	TMainMenu *MainMenu1;
	TMenuItem *Plik1;
	TToolBar *ToolBar1;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TImageList *ImageList1;
	TActionList *ActionList1;
	TToolButton *NewToolButton;
	TToolButton *OpenToolButton;
	TToolButton *SaveToolButton;
	TToolButton *DeleteToolButton;
	TToolButton *ToolSeparator1;
	TToolButton *ExitToolButton;
	TToolButton *ToolSeparator2;
	TToolButton *RotateLeftToolButton;
	TToolButton *RotateRightToolButton;
	TToolButton *ToolSeparator3;
	TToolButton *CutToolButton;
	TAction *New;
	TAction *Open;
	TAction *Save;
	TAction *Delete;
	TAction *Exit;
	TAction *RotateLeft;
	TAction *RotateRight;
	TAction *Cut;
	TMenuItem *New1;
	TMenuItem *Open1;
	TMenuItem *Save1;
	TMenuItem *Delete1;
	TMenuItem *Exit1;
	TMenuItem *RotateLeft1;
	TMenuItem *RotateRight1;
	TMenuItem *Cut1;
	TOpenPictureDialog *OpenPictureDialog1;
	TSavePictureDialog *SavePictureDialog1;
	TAction *Maximize;
	void __fastcall OpenExecute(TObject *Sender);
	void __fastcall FileListBox1Click(TObject *Sender);
	void __fastcall SaveExecute(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall RotateLeftExecute(TObject *Sender);
	void __fastcall RotateRightExecute(TObject *Sender);
	void __fastcall MaximizeExecute(TObject *Sender);





private:	TJPEGImage *JPEGImage1;
			TRect lastRect; //ostatnio narysowany prostok¹t
			TPoint mousePos; //pozycja kursora po wciœniêciu lewego przycisku
			TPoint imgTopLeft; //pozycja lewego górnego rogu obrazka
			double zoom; //

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void SkalujIPrzerysuj(TImage *Image, TJPEGImage *JPEGImage, double zoom, TPoint &imgTopLeft);
	void ObliczPozycje(TPoint &AimgTopLeft, TPoint mousePos, double zoomBef, double zoomAft);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

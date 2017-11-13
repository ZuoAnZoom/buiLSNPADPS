//---------------------------------------------------------------------------

#ifndef LSNMAINH
#define LSNMAINH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *MenuFile;
	TMenuItem *actQuit;
	TMenuItem *menuHelp;
	TMenuItem *actHelp;
	TMenuItem *actAbout;
	TPageControl *aogroup;
	TTabSheet *strsvrgroup;
    TTabSheet *rtkconvgroup;
	TTabSheet *rtkplotgroup;
	TStatusBar *StatusBar1;
	TTimer *Timer1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall actQuitClick(TObject *Sender);
	void __fastcall actHelpClick(TObject *Sender);
	void __fastcall actAboutClick(TObject *Sender);
private:	// User declarations

	void __fastcall DropFiles    (TWMDropFiles msg);
	//BEGIN_MESSAGE_MAP // for files drop, cursor key down event
	//MESSAGE_HANDLER(WM_DROPFILES,TWMDropFiles,DropFiles);
	//END_MESSAGE_MAP(TForm);

	int __fastcall ExecCmd(AnsiString cmd,int show);

public:		// User declarations

	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

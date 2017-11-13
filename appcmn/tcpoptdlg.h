//---------------------------------------------------------------------------

#ifndef tcpoptdlgH
#define tcpoptdlgH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#define MAXHIST		10

//---------------------------------------------------------------------------
class TTcpOptDialog : public TForm
{
__published:	// IDE-managed Components
	TButton *BtnCancel;
	TButton *BtnOk;
	TComboBox *MntPnt;
	TLabel *LabelMntPnt;
	TLabel *LabelUser;
	TEdit *User;
	TEdit *Passwd;
	TLabel *LabelPasswd;
	TEdit *Port;
	TLabel *LabelPort;
	TComboBox *Addr;
	TLabel *LabelAddr;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnOkClick(TObject *Sender);

private:	// User declarations


public:		// User declarations
	int Opt;
	AnsiString Path,History[MAXHIST],MntpHist[MAXHIST];
	__fastcall TTcpOptDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTcpOptDialog *TcpOptDialog;
//---------------------------------------------------------------------------
#endif

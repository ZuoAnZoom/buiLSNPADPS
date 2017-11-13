//---------------------------------------------------------------------------

#ifndef confdlgH
#define confdlgH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TConfDialog : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TButton *BtnOverwrite;
	TButton *BtnCancel;
private:	// User declarations
public:		// User declarations
	__fastcall TConfDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfDialog *ConfDialog;
//---------------------------------------------------------------------------
#endif

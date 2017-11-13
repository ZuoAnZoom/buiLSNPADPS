//---------------------------------------------------------------------------

#ifndef rtkplotallassessH
#define rtkplotallassessH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TrtkplotallassessDialog : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TCheckBox *chkDataIntegrityRate;
	TCheckBox *chkObservationsPerSlip;
	TCheckBox *chkMP;
	TCheckBox *chkCNR;
	TCheckBox *chkPn;
	TCheckBox *chkCn;
	TCheckBox *chkIon;
	TEdit *EditADataIntegrityRate;
	TEdit *EditAObservationsPerSlip;
	TEdit *EditAMP;
	TEdit *EditACNR;
	TEdit *EditAPn;
	TEdit *EditACn;
	TEdit *EditAIon;
	TEdit *EditCDataIntegrityRate;
	TEdit *EditCObservationsPerSlip;
	TEdit *EditCMP;
	TEdit *EditCCNR;
	TEdit *EditCPn;
	TEdit *EditCCn;
	TEdit *EditCIon;
	TLabel *Label4;
	TEdit *EditAllAssessment;
	TButton *BtnComputeAlla;
	TButton *BtnClearAlla;
	void __fastcall chkDataIntegrityRateClick(TObject *Sender);
	void __fastcall chkObservationsPerSlipClick(TObject *Sender);
	void __fastcall chkMPClick(TObject *Sender);
	void __fastcall chkCNRClick(TObject *Sender);
	void __fastcall chkPnClick(TObject *Sender);
	void __fastcall chkCnClick(TObject *Sender);
	void __fastcall chkIonClick(TObject *Sender);
	void __fastcall BtnComputeAllaClick(TObject *Sender);
	void __fastcall BtnClearAllaClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TrtkplotallassessDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TrtkplotallassessDialog *rtkplotallassessDialog;
//---------------------------------------------------------------------------
#endif
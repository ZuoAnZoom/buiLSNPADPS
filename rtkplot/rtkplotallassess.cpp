//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rtkplotallassess.h"
#include "rtklib.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TrtkplotallassessDialog *rtkplotallassessDialog;

//---------------------------------------------------------------------------
static double str2dbl(AnsiString str)
{
    double val=0.0;
    sscanf(str.c_str(),"%lf",&val);
    return val;
}

//---------------------------------------------------------------------------
__fastcall TrtkplotallassessDialog::TrtkplotallassessDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::chkDataIntegrityRateClick(TObject *Sender)
{
	if(this->chkDataIntegrityRate->Checked) {
		this->EditADataIntegrityRate->Enabled = true;
		this->EditCDataIntegrityRate->Enabled = true;
	}
	else {
        this->EditADataIntegrityRate->Enabled = false;
		this->EditCDataIntegrityRate->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::chkObservationsPerSlipClick(TObject *Sender)
{
	if(this->chkObservationsPerSlip->Checked) {
		this->EditAObservationsPerSlip->Enabled = true;
		this->EditCObservationsPerSlip->Enabled = true;
	}
	else {
		this->EditAObservationsPerSlip->Enabled = false;
		this->EditCObservationsPerSlip->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::chkMPClick(TObject *Sender)
{
	if(this->chkMP->Checked) {
		this->EditAMP->Enabled = true;
		this->EditCMP->Enabled = true;
	}
	else {
		this->EditAMP->Enabled = false;
		this->EditCMP->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::chkCNRClick(TObject *Sender)
{
	if(this->chkCNR->Checked) {
		this->EditACNR->Enabled = true;
		this->EditCCNR->Enabled = true;
	}
	else {
		this->EditACNR->Enabled = false;
		this->EditCCNR->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::chkPnClick(TObject *Sender)
{
	if(this->chkPn->Checked) {
		this->EditAPn->Enabled = true;
		this->EditCPn->Enabled = true;
	}
	else {
		this->EditAPn->Enabled = false;
		this->EditCPn->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::chkCnClick(TObject *Sender)
{
	if(this->chkCn->Checked) {
		this->EditACn->Enabled = true;
		this->EditCCn->Enabled = true;
	}
	else {
		this->EditACn->Enabled = false;
		this->EditCCn->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TrtkplotallassessDialog::chkIonClick(TObject *Sender)
{
	if(this->chkIon->Checked) {
		this->EditAIon->Enabled = true;
		this->EditCIon->Enabled = true;
	}
	else {
		this->EditAIon->Enabled = false;
		this->EditCIon->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::BtnComputeAllaClick(TObject *Sender)
{
	double ADataIntegrityRate=0,CDataIntegrityRate=0,AObservationPerSlip=0,CObservationPerSlip=0,AMP=0,
			CMP=0,ACNR=0,CCNR=0,APn=0,CPn=0,ACn=0,CCn=0,AIon=0,CIon=0;
	if(this->chkDataIntegrityRate->Checked) {
		ADataIntegrityRate = str2dbl(this->EditADataIntegrityRate->Text.Trim());
		CDataIntegrityRate = str2dbl(this->EditCDataIntegrityRate->Text.Trim());
	}
	if(this->chkObservationsPerSlip->Checked) {
		AObservationPerSlip = str2dbl(this->EditAObservationsPerSlip->Text.Trim());
		CObservationPerSlip = str2dbl(this->EditCObservationsPerSlip->Text.Trim());
	}
	if(this->chkMP->Checked) {
		AMP = str2dbl(this->EditAMP->Text.Trim());
		CMP = str2dbl(this->EditCMP->Text.Trim());
    }
	if(this->chkCNR->Checked) {
		ACNR = str2dbl(this->EditACNR->Text.Trim());
		CCNR = str2dbl(this->EditCCNR->Text.Trim());
    }
	if(this->chkPn->Checked) {
		APn = str2dbl(this->EditAPn->Text.Trim());
		CPn = str2dbl(this->EditCPn->Text.Trim());
    }
	if(this->chkCn->Checked) {
		ACn = str2dbl(this->EditACn->Text.Trim());
		CCn = str2dbl(this->EditCCn->Text.Trim());
    }
	if(this->chkIon->Checked) {
    	AIon = str2dbl(this->EditAIon->Text.Trim());
		CIon = str2dbl(this->EditCIon->Text.Trim());
	}

	double reVal = sqrtdxy(ADataIntegrityRate,CDataIntegrityRate) + sqrtdxy(AObservationPerSlip,CObservationPerSlip) +
				sqrtdxy(AMP,CMP) + sqrtdxy(ACNR,CCNR) + sqrtdxy(APn,CPn) + sqrtdxy(ACn,CCn) +  sqrtdxy(AIon,CIon);

    this->EditAllAssessment->Text = FloatToStr(reVal);
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotallassessDialog::BtnClearAllaClick(TObject *Sender)
{
	this->EditCDataIntegrityRate->Text = "";
	this->EditCObservationsPerSlip->Text = "";
	this->EditCMP->Text = "";
	this->EditCCNR->Text = "";
	this->EditCPn->Text = "";
	this->EditCCn->Text = "";
	this->EditCIon->Text = "";
	this->EditAllAssessment->Text = "";
}
//---------------------------------------------------------------------------

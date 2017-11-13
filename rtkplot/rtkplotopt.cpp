//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rtkplotopt.h"
#include "rtkplotmain.h"
#include "rtklib.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TrtkplotOptDialog *rtkplotOptDialog;

//---------------------------------------------------------------------------
static double str2dbl(AnsiString str)
{
    double val=0.0;
    sscanf(str.c_str(),"%lf",&val);
    return val;
}

//---------------------------------------------------------------------------
__fastcall TrtkplotOptDialog::TrtkplotOptDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotOptDialog::FormShow(TObject *Sender)
{
	//char s1[64],s2[64];
	AnsiString s;
	//int marks[] = {1,2,3,4,5,10,15,20};

	if(Plot->ShowStats)
		checkboxShowStats->Checked = true;
	else
		checkboxShowStats->Checked = false;

	if(Plot->ShowSlip)
		checkboxShowSlip->Checked = true;
	else
		checkboxShowSlip->Checked = false;

	//if(Plot->ElMaskP)
	//	checkboxElMaskP->Checked = true;
	//else
	//	checkboxElMaskP->Checked = false;

	ElMask->Text = s.sprintf("%g",Plot->ElMask);

	NavSys1->Checked=Plot->NavSys&SYS_GPS;
    NavSys2->Checked=Plot->NavSys&SYS_GLO;
    NavSys3->Checked=Plot->NavSys&SYS_GAL;
    NavSys4->Checked=Plot->NavSys&SYS_QZS;
    NavSys5->Checked=Plot->NavSys&SYS_SBS;
	NavSys6->Checked=Plot->NavSys&SYS_CMP;

    ExSats->Text=Plot->ExSats;
}
//---------------------------------------------------------------------------
void __fastcall TrtkplotOptDialog::BtnOkClick(TObject *Sender)
{
	Plot->ShowStats = checkboxShowStats->Checked;
	Plot->ShowSlip = checkboxShowSlip->Checked;
	//Plot->ElMaskP = checkboxElMaskP->Checked;
	Plot->ElMask = str2dbl(ElMask->Text);
	Plot->NavSys =  (NavSys1->Checked?SYS_GPS:0)|
					(NavSys2->Checked?SYS_GLO:0)|
					(NavSys3->Checked?SYS_GAL:0)|
					(NavSys4->Checked?SYS_QZS:0)|
					(NavSys5->Checked?SYS_SBS:0)|
					(NavSys6->Checked?SYS_CMP:0);
    Plot->ExSats = ExSats->Text;
}
//---------------------------------------------------------------------------
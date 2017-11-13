//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "convmain.h"
#include "rtklib.h"
#include "viewer.h"
#include "confdlg.h"
#include "codeopt.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define TSTARTMARGIN 60.0      // time margin for file name replacement
#define TRACEFILE   "conv.trace" // trace file

TconvMainWindow *convMainWindow;

static int abortf=0;

// show message in message area ---------------------------------------------
extern "C" {
extern int showmsg_conv(char *format,...)
{
    static int i=0;
    va_list arg;
    char buff[1024];
    va_start(arg,format); vsprintf(buff,format,arg); va_end(arg);
    convMainWindow->Message->Caption=buff;
    if (++i%100==0) Application->ProcessMessages();
    return abortf;
}
}

//---------------------------------------------------------------------------
__fastcall TconvMainWindow::TconvMainWindow(TComponent* Owner)
	: TForm(Owner)
{
	int i;
	DoubleBuffered = true;
	this->ComFormat->Items->Clear();

	//ComFormat->Items->Add("Auto");
	//for(i=0;i<= MAXRCVFMT;i++) {
	//	this->ComFormat->Items->Add(formatstrs[i]);
	//}

	this->ComFormat->Items->Add(formatstrs[STRFMT_RINEX]);
	this->ComFormat->Items->Add(formatstrs[0]); //RTCM2
	this->ComFormat->Items->Add(formatstrs[1]); //RTCM3
    this->ComFormat->Items->Add(formatstrs[11]); //BINEX
    //this->ComFormat->Items->Add(formatstrs[4]); //u-blox
}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::FormResize(TObject *Sender)
{
	this->Panel21->Width = 2*this->Panel2->Width/5;
	this->Panel22->Width = 3*this->Panel2->Width/5;
	this->Panel21->Height = this->Panel2->Height;
	this->Panel22->Height = this->Panel2->Height;

	this->Panel211->Width = this->Panel21->Width;
	this->Panel212->Width = this->Panel21->Width;
	this->Panel211->Height = this->Panel21->Height/3;
	this->Panel212->Height = 2*this->Panel21->Height/3;

	this->BtnInFile->Left = this->Panel211->Width*3/20 - this->BtnInFile->Width/2;
	this->BtnInFile->Top = this->Panel211->Height/5 - this->BtnInFile->Height/2;
	this->BtnConvert->Left = this->Panel211->Width*9/20 - this->BtnConvert->Width/2;
	this->BtnConvert->Top = this->Panel211->Height/5 - this->BtnConvert->Height/2;
	this->GroupBoxFormat->Width = 2*this->Panel211->Width/5;
	this->GroupBoxFormat->Height = 2*this->Panel211->Height/5;
	this->GroupBoxFormat->Left = 4*this->Panel211->Width/5 - this->GroupBoxFormat->Width/2;
	this->GroupBoxFormat->Top = this->Panel211->Height/5 - this->GroupBoxFormat->Height/2;
	this->ComFormat->Width = 4*this->GroupBoxFormat->Width/5;
	this->ComFormat->Left = this->GroupBoxFormat->Width/2 - this->ComFormat->Width/2;
	this->ComFormat->Top = 3*this->GroupBoxFormat->Height/5 - this->ComFormat->Height/2;
	this->GroupBoxRawData->Width = this->Panel211->Width;
	this->GroupBoxRawData->Height = 3*this->Panel211->Height/5;
	this->GroupBoxRawData->Left = 0;
	this->GroupBoxRawData->Top = 2*this->Panel211->Height/5;
	this->BtnInFileView->Left = this->GroupBoxRawData->Width - this->BtnInFileView->Width -2;
	this->BtnInFileView->Top = 3*this->GroupBoxRawData->Height/5 - this->BtnInFileView->Height/2;
	this->InFile->Width = this->GroupBoxRawData->Width - this->BtnInFileView->Width -7;
	this->InFile->Left = 3;
	this->InFile->Top = 3*this->GroupBoxRawData->Height/5 - this->InFile->Height/2;

	this->GroupBoxConvData->Width = this->Panel212->Width;
	this->GroupBoxConvData->Height = this->Panel212->Height;
	this->GroupBoxConvData->Left = 0;
	//this->GroupBoxConvData->Top = 2;
	this->OutFileEna1->Left = 2;
	this->OutFileEna2->Left = 2;
	this->OutFileEna3->Left = 2;
	this->OutFileEna4->Left = 2;
	this->OutFileEna5->Left = 2;
	this->OutFileEna6->Left = 2;
	this->OutFileEna7->Left = 2;
	double AllH = 9.5*this->GroupBoxConvData->Height/10;
	double ConstH = 0.5*this->GroupBoxConvData->Height/10;
	double tempH = AllH/7;
	this->OutFileEna1->Top = tempH/2 - this->OutFileEna1->Height/2+ConstH;
	this->OutFileEna2->Top = tempH + tempH/2 - this->OutFileEna2->Height/2+ConstH;
	this->OutFileEna3->Top = 2*tempH + tempH/2 - this->OutFileEna3->Height/2+ConstH;
	this->OutFileEna4->Top = 3*tempH + tempH/2 - this->OutFileEna4->Height/2+ConstH;
	this->OutFileEna5->Top = 4*tempH + tempH/2 - this->OutFileEna5->Height/2+ConstH;
	this->OutFileEna6->Top = 5*tempH + tempH/2 - this->OutFileEna6->Height/2+ConstH;
	this->OutFileEna7->Top = 6*tempH + tempH/2 - this->OutFileEna7->Height/2+ConstH;

	this->BtnOutFileView1->Left = this->GroupBoxConvData->Width - this->BtnOutFileView1->Width -2;
	this->BtnOutFileView2->Left = this->GroupBoxConvData->Width - this->BtnOutFileView2->Width -2;
	this->BtnOutFileView3->Left = this->GroupBoxConvData->Width - this->BtnOutFileView3->Width -2;
	this->BtnOutFileView4->Left = this->GroupBoxConvData->Width - this->BtnOutFileView4->Width -2;
	this->BtnOutFileView5->Left = this->GroupBoxConvData->Width - this->BtnOutFileView5->Width -2;
	this->BtnOutFileView6->Left = this->GroupBoxConvData->Width - this->BtnOutFileView6->Width -2;
	this->BtnOutFileView7->Left = this->GroupBoxConvData->Width - this->BtnOutFileView7->Width -2;
	this->BtnOutFileView1->Top = tempH/2 - this->BtnOutFileView1->Height/2+ConstH;
	this->BtnOutFileView2->Top = tempH + tempH/2 - this->BtnOutFileView2->Height/2+ConstH;
	this->BtnOutFileView3->Top = 2*tempH + tempH/2 - this->BtnOutFileView3->Height/2+ConstH;
	this->BtnOutFileView4->Top = 3*tempH + tempH/2 - this->BtnOutFileView4->Height/2+ConstH;
	this->BtnOutFileView5->Top = 4*tempH + tempH/2 - this->BtnOutFileView5->Height/2+ConstH;
	this->BtnOutFileView6->Top = 5*tempH + tempH/2 - this->BtnOutFileView6->Height/2+ConstH;
	this->BtnOutFileView7->Top = 6*tempH + tempH/2 - this->BtnOutFileView7->Height/2+ConstH;

	this->OutFile1->Width = this->GroupBoxConvData->Width - this->OutFileEna1->Width - this->BtnOutFileView1->Width - 8;
	this->OutFile2->Width = this->GroupBoxConvData->Width - this->OutFileEna2->Width - this->BtnOutFileView2->Width - 8;
	this->OutFile3->Width = this->GroupBoxConvData->Width - this->OutFileEna3->Width - this->BtnOutFileView3->Width - 8;
	this->OutFile4->Width = this->GroupBoxConvData->Width - this->OutFileEna4->Width - this->BtnOutFileView4->Width - 8;
	this->OutFile5->Width = this->GroupBoxConvData->Width - this->OutFileEna5->Width - this->BtnOutFileView5->Width - 8;
	this->OutFile6->Width = this->GroupBoxConvData->Width - this->OutFileEna6->Width - this->BtnOutFileView6->Width - 8;
	this->OutFile7->Width = this->GroupBoxConvData->Width - this->OutFileEna7->Width - this->BtnOutFileView7->Width - 8;
	this->OutFile1->Left = this->OutFileEna1->Width +4;
	this->OutFile2->Left = this->OutFileEna2->Width +4;
	this->OutFile3->Left = this->OutFileEna3->Width +4;
	this->OutFile4->Left = this->OutFileEna4->Width +4;
	this->OutFile5->Left = this->OutFileEna5->Width +4;
	this->OutFile6->Left = this->OutFileEna6->Width +4;
	this->OutFile7->Left = this->OutFileEna7->Width +4;
	this->OutFile1->Top = tempH/2 - this->OutFile1->Height/2+ConstH;
	this->OutFile2->Top = tempH + tempH/2 - this->OutFile2->Height/2+ConstH;
	this->OutFile3->Top = 2*tempH + tempH/2 - this->OutFile3->Height/2+ConstH;
	this->OutFile4->Top = 3*tempH + tempH/2 - this->OutFile4->Height/2+ConstH;
	this->OutFile5->Top = 4*tempH + tempH/2 - this->OutFile5->Height/2+ConstH;
	this->OutFile6->Top = 5*tempH + tempH/2 - this->OutFile6->Height/2+ConstH;
	this->OutFile7->Top = 6*tempH + tempH/2 - this->OutFile7->Height/2+ConstH;

	this->GroupBoxConvOpt->Width = this->Panel22->Width-2;
	this->GroupBoxConvOpt->Height = this->Panel22->Height-1;
	this->GroupBoxConvOpt->Left = 0;
	this->GroupBoxConvOpt->Top = 0;

	double OptAllH1 = 4.7*this->GroupBoxConvOpt->Height/10;
	double OptConstH = 0.4*this->GroupBoxConvOpt->Height/10;
	double OpttempH1 = (OptAllH1 - this->PanelRnxVer->Height - this->PanelMarker->Height - this->PanelROA->Height -
					this->PanelRec->Height - this->PanelAnt->Height - this->PanelXYZ->Height -
					this->PanelHEN->Height)/6;

	this->PanelRnxVer->Top = OptConstH;this->PanelRnxCode->Top = OptConstH;this->PanelRnxFile->Top = OptConstH;
	this->PanelMarker->Top = this->PanelRnxVer->Top + this->PanelRnxVer->Height + OpttempH1;
	this->EditMarker->Top =  this->PanelRnxVer->Top + this->PanelRnxVer->Height + OpttempH1;
	this->EditMarkerNo->Top = this->PanelRnxVer->Top + this->PanelRnxVer->Height + OpttempH1;
	this->EditMarkerType->Top = this->PanelRnxVer->Top + this->PanelRnxVer->Height + OpttempH1;
	this->PanelROA->Top = this->PanelMarker->Top + this->PanelMarker->Height + OpttempH1;
	this->EditRunBy->Top = this->PanelMarker->Top + this->PanelMarker->Height + OpttempH1;
	this->EditName0->Top = this->PanelMarker->Top + this->PanelMarker->Height + OpttempH1;
	this->EditName1->Top = this->PanelMarker->Top + this->PanelMarker->Height + OpttempH1;
	this->PanelRec->Top = this->PanelROA->Top + this->PanelROA->Height + OpttempH1;
	this->EditRec0->Top = this->PanelROA->Top + this->PanelROA->Height + OpttempH1;
	this->EditRec1->Top = this->PanelROA->Top + this->PanelROA->Height + OpttempH1;
	this->EditRec2->Top = this->PanelROA->Top + this->PanelROA->Height + OpttempH1;
	this->PanelAnt->Top = this->PanelRec->Top + this->PanelRec->Height + OpttempH1;
	this->EditAnt0->Top = this->PanelRec->Top + this->PanelRec->Height + OpttempH1;
	this->EditAnt1->Top = this->PanelRec->Top + this->PanelRec->Height + OpttempH1;
	this->EditAnt2->Top = this->PanelRec->Top + this->PanelRec->Height + OpttempH1;
	this->PanelXYZ->Top = this->PanelAnt->Top + this->PanelAnt->Height + OpttempH1;
	this->EditAppPos0->Top = this->PanelAnt->Top + this->PanelAnt->Height + OpttempH1;
	this->EditAppPos1->Top = this->PanelAnt->Top + this->PanelAnt->Height + OpttempH1;
	this->EditAppPos2->Top = this->PanelAnt->Top + this->PanelAnt->Height + OpttempH1;
	this->PanelHEN->Top = this->PanelXYZ->Top + this->PanelXYZ->Height + OpttempH1;
	this->EditAntDel0->Top = this->PanelXYZ->Top + this->PanelXYZ->Height + OpttempH1;
	this->EditAntDel1->Top = this->PanelXYZ->Top + this->PanelXYZ->Height + OpttempH1;
	this->EditAntDel2->Top = this->PanelXYZ->Top + this->PanelXYZ->Height + OpttempH1;

	double OptAllH2 = 4.2*this->GroupBoxConvOpt->Height/10;
	double OpttempH2 =(OptAllH2-this->GroupBoxTimeFirst->Height - this->GroupBoxNavSys->Height -
					this->GroupBoxObsType->Height)/2;

	this->GroupBoxTimeFirst->Top = 0.4*this->GroupBoxConvOpt->Height/10 + this->PanelHEN->Top + this->PanelHEN->Height;
	this->GroupBoxTimeLast->Top = 0.4*this->GroupBoxConvOpt->Height/10 + this->PanelHEN->Top + this->PanelHEN->Height;
	this->PanelIL->Top = 0.4*this->GroupBoxConvOpt->Height/10 + this->PanelHEN->Top + this->PanelHEN->Height;

	this->GroupBoxNavSys->Top = this->GroupBoxTimeFirst->Top + this->GroupBoxTimeFirst->Height + OpttempH2;
	this->GroupBoxFre->Top = this->GroupBoxTimeFirst->Top + this->GroupBoxTimeFirst->Height + OpttempH2;

	this->GroupBoxObsType->Top = this->GroupBoxFre->Top + this->GroupBoxFre->Height + OpttempH2;
	this->PanelBtn->Top = this->GroupBoxObsType->Top+5;

	this->PanelRnxVer->Left = 12;
	double tempval1 = (this->GroupBoxConvOpt->Width - 2*this->PanelRnxVer->Left - this->PanelRnxVer->Width
					- this->PanelRnxCode->Width	- this->PanelRnxFile->Width)/2;
	this->PanelRnxCode->Left = this->PanelRnxVer->Left + this->PanelRnxVer->Width + tempval1;
	this->PanelRnxFile->Left = this->PanelRnxCode->Left + this->PanelRnxCode->Width + tempval1;

	this->PanelMarker->Left = 12;
	this->EditMarker->Left = this->PanelMarker->Left + this->PanelMarker->Width + 12;
	this->EditMarker->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditMarkerNo->Left = this->EditMarker->Left + this->EditMarker->Width + 12;
	this->EditMarkerNo->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditMarkerType->Left = this->EditMarkerNo->Left + this->EditMarkerNo->Width + 12;
	this->EditMarkerType->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;

	this->PanelROA->Left = 12;
	this->EditRunBy->Left = this->PanelMarker->Left + this->PanelMarker->Width + 12;
	this->EditRunBy->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditName0->Left =  this->EditMarker->Left + this->EditMarker->Width + 12;
	this->EditName0->Width =  (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditName1->Left = this->EditMarkerNo->Left + this->EditMarkerNo->Width + 12;
	this->EditName1->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;

	this->PanelRec->Left = 12;
	this->EditRec0->Left = this->PanelMarker->Left + this->PanelMarker->Width + 12;
	this->EditRec0->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditRec1->Left =  this->EditMarker->Left + this->EditMarker->Width + 12;
	this->EditRec1->Width =  (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditRec2->Left = this->EditMarkerNo->Left + this->EditMarkerNo->Width + 12;
	this->EditRec2->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;

	this->PanelAnt->Left = 12;
	this->EditAnt0->Left = this->PanelMarker->Left + this->PanelMarker->Width + 12;
	this->EditAnt0->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditAnt1->Left =  this->EditMarker->Left + this->EditMarker->Width + 12;
	this->EditAnt1->Width =  (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditAnt2->Left = this->EditMarkerNo->Left + this->EditMarkerNo->Width + 12;
	this->EditAnt2->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;

	this->PanelXYZ->Left = 12;
	this->EditAppPos0->Left = this->PanelMarker->Left + this->PanelMarker->Width + 12;
	this->EditAppPos0->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditAppPos1->Left =  this->EditMarker->Left + this->EditMarker->Width + 12;
	this->EditAppPos1->Width =  (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditAppPos2->Left = this->EditMarkerNo->Left + this->EditMarkerNo->Width + 12;
	this->EditAppPos2->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;

	this->PanelHEN->Left = 12;
	this->EditAntDel0->Left = this->PanelMarker->Left + this->PanelMarker->Width + 12;
	this->EditAntDel0->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditAntDel1->Left =  this->EditMarker->Left + this->EditMarker->Width + 12;
	this->EditAntDel1->Width =  (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;
	this->EditAntDel2->Left = this->EditMarkerNo->Left + this->EditMarkerNo->Width + 12;
	this->EditAntDel2->Width = (this->GroupBoxConvOpt->Width - 12*5 - this->PanelMarker->Width)/3;

	this->GroupBoxTimeFirst->Left = 12;
	double tempval2 = (this->GroupBoxConvOpt->Width - 2*this->GroupBoxTimeFirst->Left - this->GroupBoxTimeFirst->Width-
					this->GroupBoxTimeLast->Width - this->PanelIL->Width)/2;
	this->GroupBoxTimeLast->Left = this->GroupBoxTimeFirst->Left + this->GroupBoxTimeFirst->Width + tempval2;
	this->PanelIL->Left = this->GroupBoxTimeLast->Left + this->GroupBoxTimeLast->Width + tempval2;

	this->GroupBoxNavSys->Left = 12;
	this->GroupBoxNavSys->Width = 3*(this->GroupBoxConvOpt->Width-36)/5;
	double NavSysValH1 = 7.5*this->GroupBoxNavSys->Height/10;
	double NavSysValH2 = 2*this->GroupBoxNavSys->Height/10;
	this->NavSys1->Top = NavSysValH2; this->NavSys2->Top = NavSysValH2;this->NavSys3->Top = NavSysValH2;
	this->NavSys1->Left = 15;
	double NavSysValV_I = (this->GroupBoxNavSys->Width - 30 - 3*this->NavSys1->Width)/2;
	this->NavSys2->Left = this->NavSys1->Left + this->NavSys1->Width+NavSysValV_I;
	this->NavSys3->Left = this->NavSys2->Left + this->NavSys2->Width+NavSysValV_I;

	double NavSysValH_I = (NavSysValH1-this->NavSys1->Height - this->NavSys6->Height- this->EditExSats->Height)/2;
	this->NavSys6->Top = this->NavSys1->Top + this->NavSys1->Height + NavSysValH_I;
	this->NavSys4->Top = this->NavSys1->Top + this->NavSys1->Height + NavSysValH_I;
	this->NavSys5->Top = this->NavSys1->Top + this->NavSys1->Height + NavSysValH_I;
    this->NavSys6->Left = 15;
	this->NavSys4->Left = this->NavSys1->Left + this->NavSys1->Width+NavSysValV_I;
	this->NavSys5->Left = this->NavSys2->Left + this->NavSys2->Width+NavSysValV_I;

	this->LabelExSats->Top = this->NavSys6->Top + this->NavSys6->Height + NavSysValH_I+3;
	this->EditExSats->Top = this->NavSys6->Top + this->NavSys6->Height + NavSysValH_I;
	this->LabelExSats->Left = 15;
	this->EditExSats->Left = this->LabelExSats->Left + this->LabelExSats->Width + 15;
	this->EditExSats->Width = this->NavSys5->Left+this->NavSys5->Width-this->EditExSats->Left;

	this->GroupBoxFre->Left = this->GroupBoxNavSys->Left + this->GroupBoxNavSys->Width + 12;
	this->GroupBoxFre->Width =  2*(this->GroupBoxConvOpt->Width-36)/5;
	double FreValH1 = 7.5*this->GroupBoxFre->Height/10;
	double FreValH2 = 2*this->GroupBoxFre->Height/10;
	this->Freq1->Top = FreValH2; this->Freq2->Top = FreValH2; this->Freq3->Top = FreValH2;
	this->Freq1->Left = 5;
	double FreqValV_I = (this->GroupBoxFre->Width-10-3*this->Freq1->Width)/2;
	this->Freq2->Left = this->Freq1->Left + this->Freq1->Width + FreqValV_I;
	this->Freq3->Left = this->Freq2->Left + this->Freq2->Width + FreqValV_I;

	double FreqValH_I = (FreValH1-this->Freq1->Height-this->Freq6->Height-this->CheckScanObs->Height)/2;
	this->Freq4->Top = this->Freq1->Top + this->Freq1->Height + FreqValH_I;
	this->Freq5->Top = this->Freq1->Top + this->Freq1->Height + FreqValH_I;
	this->Freq6->Top = this->Freq1->Top + this->Freq1->Height + FreqValH_I;
	this->Freq4->Left = 5;
	this->Freq5->Left = this->Freq1->Left + this->Freq1->Width + FreqValV_I;
	this->Freq6->Left = this->Freq2->Left + this->Freq2->Width + FreqValV_I;

	this->CheckScanObs->Left = 5;
	this->CheckScanObs->Top = this->Freq4->Top + this->Freq4->Height + FreqValH_I;
	this->BtnMask->Top = this->Freq4->Top + this->Freq4->Height + FreqValH_I-3;
	this->BtnMask->Left = this->CheckScanObs->Left + this->CheckScanObs->Width + 5;

	this->GroupBoxObsType->Left = 12;
	this->GroupBoxObsType->Width = 13*(this->GroupBoxConvOpt->Width-12-12)/20;
    this->PanelBtn->Left = this->GroupBoxConvOpt->Width - 12 - this->PanelBtn->Width;
	double Obstype_W = (this->GroupBoxObsType->Width - 24 - this->Obs1->Width -
				this->Obs2->Width - this->Obs3->Width - this->Obs4->Width)/3;
	this->Obs1->Left = 10;
	this->Obs2->Left = this->Obs1->Left + this->Obs1->Width + Obstype_W;
	this->Obs3->Left = this->Obs2->Left + this->Obs2->Width + Obstype_W;
	this->Obs4->Left = this->Obs3->Left + this->Obs3->Width + Obstype_W;

}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::BtnInFileClick(TObject *Sender)
{
	this->OpenDialog->Title = "���ļ�";
	this->OpenDialog->FileName = "";
	if(!OpenDialog->Execute())
		return;
	InFile->Text = OpenDialog->FileName;
	SetOutFiles(InFile->Text);
    SetConvOptVal(InFile->Text);
}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::SetConvOptVal(AnsiString infile)
{
	int i,j,k;
	double RNXVER[]={2.10,2.11,2.12,3.00,3.01,3.02,3.03};
	char *ifile,tstr[32];
	ifile = infile.c_str();
    rnxopt_t rnxopt = {0};
	readrnxopt(ifile,&rnxopt);

	for(i=0;i<7;i++) {
		if(fabs(RNXVER[i]-rnxopt.rnxver)<0.000001)
			this->ComRnxVer->ItemIndex = i;
	}
	this->EditRnxCode->Text = rnxopt.staid;
	this->CheckRnxFile->Checked = true;
	this->EditMarker->Text = rnxopt.marker;
	this->EditMarkerNo->Text = rnxopt.markerno;
	this->EditMarkerType->Text = rnxopt.markertype;
	this->EditRunBy->Text = rnxopt.runby;
	this->EditName0->Text = rnxopt.name[0];
	this->EditName1->Text = rnxopt.name[1];
	this->EditRec0->Text = rnxopt.rec[0];
	this->EditRec1->Text = rnxopt.rec[1];
	this->EditRec2->Text = rnxopt.rec[2];
	this->EditAnt0->Text = rnxopt.ant[0];
	this->EditAnt1->Text = rnxopt.ant[1];
	this->EditAnt2->Text = rnxopt.ant[2];
	this->EditAppPos0->Text = rnxopt.apppos[0];
	this->EditAppPos1->Text = rnxopt.apppos[1];
	this->EditAppPos2->Text = rnxopt.apppos[2];
	this->EditAntDel0->Text = rnxopt.antdel[0];
	this->EditAntDel1->Text = rnxopt.antdel[1];
	this->EditAntDel2->Text = rnxopt.antdel[2];
	time2str(rnxopt.tstart,tstr,0); tstr[10]='\0';
	this->FirstTimeY1->Text = tstr; this->FirstTimeH1->Text = tstr+11;
	time2str(rnxopt.tend,tstr,0); tstr[10]='\0';
	this->LastTimeY1->Text = tstr; this->LastTimeH1->Text = tstr+11;

	this->EditInterval->Text = rnxopt.tint;
	this->EditLeapSec->Text = rnxopt.outleaps;

	//��ϵͳ���۲����͡�Ƶ�㡢ͨ������������
	char gpsoptcodes[21][3],glooptcodes[7][3],galoptcodes[19][3],qzssoptcodes[14][3],cmpoptcodes[9][3],sbasoptcodes[4][3];
    for(i=0;i<21;i++)
		strcpy(gpsoptcodes[i],CodeOptDialog->gpscodes[i].c_str());
	for(i=0;i<7;i++)
		strcpy(glooptcodes[i],CodeOptDialog->glocodes[i].c_str());
	for(i=0;i<19;i++)
		strcpy(galoptcodes[i],CodeOptDialog->galcodes[i].c_str());
	for(i=0;i<14;i++)
		strcpy(qzssoptcodes[i],CodeOptDialog->qzsscodes[i].c_str());
	for(i=0;i<9;i++)
		strcpy(cmpoptcodes[i],CodeOptDialog->cmpcodes[i].c_str());
	for(i=0;i<4;i++)
		strcpy(sbasoptcodes[i],CodeOptDialog->sbascodes[i].c_str());
	for(i=0;i<6;i++){
		for(j=0;j<MAXOBSTYPE;j++) {
			if(rnxopt.tobs[i][j][0]!='\0') {
				switch(i){
					case 0: {
						this->NavSys1->Checked = true;
						for(k=0;k<21;k++)
							if(strstr(rnxopt.tobs[i][j],gpsoptcodes[k])) CodeOptDialog->gpscodeopt[k]=1;
						break;
					}
					case 1: {
						this->NavSys2->Checked = true;
                        for(k=0;k<7;k++)
							if(strstr(rnxopt.tobs[i][j],glooptcodes[k])) CodeOptDialog->glocodeopt[k]=1;
						break;
					}
					case 2: {
						this->NavSys3->Checked = true;
                        for(k=0;k<19;k++)
							if(strstr(rnxopt.tobs[i][j],galoptcodes[k])) CodeOptDialog->galcodeopt[k]=1;
						break;
					}
					case 3: {
						this->NavSys4->Checked = true;
                        for(k=0;k<14;k++)
							if(strstr(rnxopt.tobs[i][j],qzssoptcodes[k])) CodeOptDialog->qzsscodeopt[k]=1;
						break;
					}
					case 4: {
						this->NavSys5->Checked = true;
						for(k=0;k<4;k++)
							if(strstr(rnxopt.tobs[i][j],sbasoptcodes[k])) CodeOptDialog->sbascodeopt[k]=1;
						break;
					}
					case 5: {
						this->NavSys6->Checked = true;
						for(k=0;k<9;k++)
                            if(strstr(rnxopt.tobs[i][j],cmpoptcodes[k])) CodeOptDialog->cmpcodeopt[k]=1;
						break;
					}
				}
				switch(rnxopt.tobs[i][j][0]) {
					case 'C': {this->Obs1->Checked = true; break; }
					case 'L': {this->Obs2->Checked = true; break; }
					case 'D': {this->Obs3->Checked = true; break; }
					case 'S': {this->Obs4->Checked = true; break; }
				}
				switch(rnxopt.tobs[i][j][1]) {
					case '1': {this->Freq1->Checked = true; break; }
					case '2': {this->Freq2->Checked = true; break; }
					case '3': {this->Freq3->Checked = true; break; }
					case '5': {this->Freq3->Checked = true; break; }
					case '6': {this->Freq4->Checked = true; break; }
					case '7': {this->Freq5->Checked = true; break; }
					case '8': {this->Freq6->Checked = true; break; }
                }

			}
		}
	}

	//��ͨ����������
    CodeOptDialog->NavSys=0;
	CodeOptDialog->FreqType=0;
	if (NavSys1->Checked) CodeOptDialog->NavSys|=SYS_GPS;
	if (NavSys2->Checked) CodeOptDialog->NavSys|=SYS_GLO;
	if (NavSys3->Checked) CodeOptDialog->NavSys|=SYS_GAL;
	if (NavSys4->Checked) CodeOptDialog->NavSys|=SYS_QZS;
	if (NavSys5->Checked) CodeOptDialog->NavSys|=SYS_SBS;
	if (NavSys6->Checked) CodeOptDialog->NavSys|=SYS_CMP;
	if (Freq1->Checked) CodeOptDialog->FreqType|=FREQTYPE_L1;
	if (Freq2->Checked) CodeOptDialog->FreqType|=FREQTYPE_L2;
	if (Freq3->Checked) CodeOptDialog->FreqType|=FREQTYPE_L5;
	if (Freq4->Checked) CodeOptDialog->FreqType|=FREQTYPE_L6;
	if (Freq5->Checked) CodeOptDialog->FreqType|=FREQTYPE_L7;
	if (Freq6->Checked) CodeOptDialog->FreqType|=FREQTYPE_L8;

}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::SetOutFiles(AnsiString infile)
{
	TEdit *edit[]={
        OutFile1,OutFile2,OutFile3,OutFile4,OutFile5,OutFile6,OutFile7
    };
	AnsiString Format_Text=ComFormat->Text;
	//AnsiString OutDir_Text=OutDir->Text;
    char *ifile,ofile[8][1024],*code,*p;
	int i,lex=strstr(Format_Text.c_str(),"LEX")!=NULL;

    //if (!EventEna) return;

    ifile=infile.c_str();
    /*if (OutDirEna->Checked) {
        if ((p=strrchr(ifile,'\\'))) p++; else p=ifile;
        sprintf(ofile[0],"%s\\%s",OutDir_Text.c_str(),p);
    }
    else {
        strcpy(ofile[0],ifile);
	}*/
	strcpy(ofile[0],ifile);

    for (p=ofile[0];*p;p++) {
        if (*p=='*'||*p=='?') *p='0';
    }
    if (!RnxFile) {
        if ((p=strrchr(ofile[0],'.'))) *p='\0';
        sprintf(ofile[1],"%s.obs" ,ofile[0]);
        sprintf(ofile[2],"%s.nav" ,ofile[0]);
        sprintf(ofile[3],"%s.gnav",ofile[0]);
        sprintf(ofile[4],"%s.hnav",ofile[0]);
        sprintf(ofile[5],"%s.qnav",ofile[0]);
        sprintf(ofile[6],"%s.lnav",ofile[0]);
        sprintf(ofile[7],lex?"%s.lex":"%s.sbs",ofile[0]);
    }
	else {
        if ((p=strrchr(ofile[0],'.'))) *p='\0';
        sprintf(ofile[1],"%s.obs" ,ofile[0]);
        sprintf(ofile[2],"%s.nav" ,ofile[0]);
        sprintf(ofile[3],"%s.gnav",ofile[0]);
        sprintf(ofile[4],"%s.hnav",ofile[0]);
        sprintf(ofile[5],"%s.qnav",ofile[0]);
        sprintf(ofile[6],"%s.lnav",ofile[0]);
        sprintf(ofile[7],lex?"%s.lex":"%s.sbs",ofile[0]);
        /*if ((p=strrchr(ofile[0],'\\'))) *(p+1)='\0';
        else ofile[0][0]='\0';
        sprintf(ofile[1],"%s%%r%%n0.%%yO",ofile[0]);
        if (RnxVer>=3&&NavSys&&(NavSys!=SYS_GPS)) { //ver.3 and mixed system
            sprintf(ofile[2],"%s%%r%%n0.%%yP",ofile[0]);
        }
        else {
            sprintf(ofile[2],"%s%%r%%n0.%%yN",ofile[0]);
        }
        sprintf(ofile[3],"%s%%r%%n0.%%yG",ofile[0]);
        sprintf(ofile[4],"%s%%r%%n0.%%yH",ofile[0]);
        sprintf(ofile[5],"%s%%r%%n0.%%yQ",ofile[0]);
        sprintf(ofile[6],"%s%%r%%n0.%%yL",ofile[0]);
        sprintf(ofile[7],lex?"%s%%r%%n0_%%y.lex":"%s%%r%%n0_%%y.sbs",ofile[0]); */
    }
    for (i=0;i<7;i++) {
        if (!strcmp(ofile[i+1],ifile)) strcat(ofile[i+1],"_");
        edit[i]->Text=ofile[i+1];
    }

}
void __fastcall TconvMainWindow::FormCreate(TObject *Sender)
{
	//AnsiString s;

	//Caption=s.sprintf("%s ver.%s",PRGNAME,VER_RTKLIB);

    //::DragAcceptFiles(Handle,true);
}
//---------------------------------------------------------------------------
static double str2dbl(AnsiString str)
{
	double val=0.0;
	sscanf(str.c_str(),"%lf",&val);
	return val;
}
//---------------------------------------------------------------------------
static double str2int(AnsiString str)
{
	int val=0;
	sscanf(str.c_str(),"%d",&val);
	return val;
}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::FormShow(TObject *Sender)
{
	/*this->RnxVer = this->ComRnxVer->ItemIndex;      //RINEX Version
	this->RnxFile = this->CheckRnxFile->Checked;    //RINEX Name
	this->RnxCode = this->EditRnxCode->Text;        //Station ID
	this->Marker = this->EditMarker->Text;          //Marker Name/Number/Type
	this->MarkerNo = this->EditMarkerNo->Text;
	this->MarkerType = this->EditMarkerType->Text;
	this->RunBy = this->EditRunBy->Text;            //RunBy/Observer/Agency
	this->Name[0] = this->EditName0->Text;
	this->Name[1] = this->EditName1->Text;
	this->Rec[0]= this->EditRec0->Text;   //Rec #/Type/Vers
	this->Rec[1] = this->EditRec1->Text;
	this->Rec[2] = this->EditRec2->Text;
	this->Ant[0] = this->EditAnt0->Text;  //Ant #/Type
	this->Ant[1] = this->EditAnt1->Text;
	this->Ant[2] = this->EditAnt2->Text;
	this->AppPos[0] = str2dbl(this->EditAppPos0->Text); //Apporx position XYZ
	this->AppPos[1] = str2dbl(this->EditAppPos1->Text);
	this->AppPos[2] = str2dbl(this->EditAppPos2->Text);
	this->AntDel[0] = str2dbl(this->EditAntDel0->Text); //Antenna: Delta H/E/N
	this->AntDel[1] = str2dbl(this->EditAntDel1->Text);
	this->AntDel[2] = str2dbl(this->EditAntDel2->Text);

	this->ScanObs = this->CheckScanObs->Checked;
	this->OutIono = true;  //
	this->OutTime = true;
	this->OutLeaps = true;

    int navsys=0,obstype=0,freqtype=0;
	if (Nav1->Checked) navsys|=SYS_GPS;
	if (Nav2->Checked) navsys|=SYS_GLO;
	if (Nav3->Checked) navsys|=SYS_GAL;
	if (Nav4->Checked) navsys|=SYS_QZS;
	if (Nav5->Checked) navsys|=SYS_SBS;
	if (Nav6->Checked) navsys|=SYS_CMP;
	if (Obs1->Checked) obstype|=OBSTYPE_PR;
	if (Obs2->Checked) obstype|=OBSTYPE_CP;
	if (Obs3->Checked) obstype|=OBSTYPE_DOP;
	if (Obs4->Checked) obstype|=OBSTYPE_SNR;
	if (Freq1->Checked) freqtype|=FREQTYPE_L1;
	if (Freq2->Checked) freqtype|=FREQTYPE_L2;
	if (Freq3->Checked) freqtype|=FREQTYPE_L5;
	if (Freq4->Checked) freqtype|=FREQTYPE_L6;
	if (Freq5->Checked) freqtype|=FREQTYPE_L7;
	if (Freq6->Checked) freqtype|=FREQTYPE_L8;
	this->NavSys = navsys;
	this->ObsType = obstype;
	this->FreqType = freqtype;
	this->ExSats = this->EditExSats->Text;   */

	char *p,*argv[32],buff[1024];
    int argc=0;

    strcpy(buff,GetCommandLine());

    for (p=buff;*p&&argc<32;p++) {
        if (*p==' ') continue;
        if (*p=='"') {
            argv[argc++]=p+1;
            if (!(p=strchr(p+1,'"'))) break;
        }
        else {
            argv[argc++]=p;
            if (!(p=strchr(p+1,' '))) break;
        }
        *p='\0';
    }
    for (int i=1;i<argc;i++) {
        if (!strcmp(argv[i],"-i")&&i+1<argc) IniFile=argv[++i];
    }
    LoadOpt();

    for (int i=1;i<argc;i++) {
        if (!strcmp(argv[i],"-t")&&i+1<argc) Caption=argv[++i];
    }
	EventEna=1;

	this->ComRnxVer->Enabled = false; this->EditRnxCode->Enabled = false;this->CheckRnxFile->Enabled = false;
	this->EditMarker->Enabled = false;this->EditMarkerNo->Enabled = false;this->EditMarkerType->Enabled = false;
	this->EditRunBy->Enabled = false;this->EditName0->Enabled = false;this->EditName1->Enabled = false;
	this->EditRec0->Enabled = false; this->EditRec1->Enabled = false; this->EditRec2->Enabled = false;
	this->EditAnt0->Enabled = false; this->EditAnt1->Enabled = false;this->EditAnt2->Enabled = false;
	this->EditAppPos0->Enabled = false; this->EditAppPos1->Enabled = false; this->EditAppPos2->Enabled = false;
	this->EditAntDel0->Enabled = false; this->EditAntDel1->Enabled = false; this->EditAntDel2->Enabled = false;
	this->FirstTimeH1->Enabled = false; this->FirstTimeH1UD->Enabled = false;
	this->FirstTimeY1->Enabled = false; this->FirstTimeY1UD->Enabled = false;
	this->LastTimeH1->Enabled = false; this->LastTimeH1UD->Enabled = false;
	this->LastTimeY1->Enabled = false; this->LastTimeY1UD->Enabled = false;
	this->EditInterval->Enabled = false; this->EditLeapSec->Enabled = false;

}

// undate enable/disable of widgets -----------------------------------------
void __fastcall TconvMainWindow::UpdateEnable(void)
{
	RnxVer = str2dbl(this->ComRnxVer->Text.Trim());
	AnsiString FormatText=ComFormat->Text;
	int rnx=strstr(FormatText.c_str(),"RINEX")!=NULL;
	//TimeY1         ->Enabled=TimeStartF ->Checked;
	//TimeH1         ->Enabled=TimeStartF ->Checked;
	//TimeY1UD       ->Enabled=TimeStartF ->Checked;
	//TimeH1UD       ->Enabled=TimeStartF ->Checked;
	//BtnTime1       ->Enabled=TimeStartF ->Checked;
	//TimeY2         ->Enabled=TimeEndF   ->Checked;
	//TimeH2         ->Enabled=TimeEndF   ->Checked;
	//TimeY2UD       ->Enabled=TimeEndF   ->Checked;
	//TimeH2UD       ->Enabled=TimeEndF   ->Checked;
	//BtnTime2       ->Enabled=TimeEndF   ->Checked;
	//TimeInt        ->Enabled=TimeIntF   ->Checked;
	//LabelTimeInt   ->Enabled=TimeInt    ->Enabled;
	//TimeUnitF      ->Enabled=TimeStartF->Checked&&TimeEndF->Checked;
	//TimeUnit       ->Enabled=TimeStartF->Checked&&TimeEndF->Checked&&TimeUnitF->Checked;
    //LabelTimeUnit  ->Enabled=TimeUnit  ->Enabled;
	OutFileEna3    ->Enabled=RnxVer<3&&(NavSys&SYS_GLO);
	OutFileEna4    ->Enabled=RnxVer<3&&(NavSys&SYS_SBS);
	OutFileEna5    ->Enabled=RnxVer<3&&(NavSys&SYS_QZS);
	OutFileEna6    ->Enabled=RnxVer<3&&(NavSys&SYS_GAL);
	OutFileEna7    ->Enabled=!rnx;
	//OutDir         ->Enabled=OutDirEna  ->Checked;
	//LabelOutDir    ->Enabled=OutDirEna  ->Checked;
	OutFile1       ->Enabled=OutFileEna1->Checked;
	OutFile2       ->Enabled=OutFileEna2->Checked;
	OutFile3       ->Enabled=OutFileEna3->Checked&&RnxVer<3&&(NavSys&SYS_GLO);
	OutFile4       ->Enabled=OutFileEna4->Checked&&RnxVer<3&&(NavSys&SYS_SBS);
	OutFile5       ->Enabled=OutFileEna5->Checked&&RnxVer<3&&(NavSys&SYS_QZS);
	OutFile6       ->Enabled=OutFileEna6->Checked&&RnxVer<3&&(NavSys&SYS_GAL);
	OutFile7       ->Enabled=OutFileEna7->Checked&&!rnx;
	//BtnOutDir      ->Enabled=OutDirEna  ->Checked;
	//BtnOutFile1    ->Enabled=OutFile1->Enabled;
	//BtnOutFile2    ->Enabled=OutFile2->Enabled;
	//BtnOutFile3    ->Enabled=OutFile3->Enabled;
	//BtnOutFile4    ->Enabled=OutFile4->Enabled;
	//BtnOutFile5    ->Enabled=OutFile5->Enabled;
	//BtnOutFile6    ->Enabled=OutFile6->Enabled;
	//BtnOutFile7    ->Enabled=OutFile7->Enabled;
	BtnOutFileView1->Enabled=OutFile1->Enabled;
	BtnOutFileView2->Enabled=OutFile2->Enabled;
	BtnOutFileView3->Enabled=OutFile3->Enabled;
	BtnOutFileView4->Enabled=OutFile4->Enabled;
	BtnOutFileView5->Enabled=OutFile5->Enabled;
	BtnOutFileView6->Enabled=OutFile6->Enabled;
	BtnOutFileView7->Enabled=OutFile7->Enabled;

	/*if(!rnx){
		this->ComRnxVer->Enabled = false; this->EditRnxCode->Enabled = false;this->CheckRnxFile->Enabled = false;
		this->EditMarker->Enabled = false;this->EditMarkerNo->Enabled = false;this->EditMarkerType->Enabled = false;
		this->EditRunBy->Enabled = false;this->EditName0->Enabled = false;this->EditName1->Enabled = false;
		this->EditRec0->Enabled = false; this->EditRec1->Enabled = false; this->EditRec2->Enabled = false;
		this->EditAnt0->Enabled = false; this->EditAnt1->Enabled = false;this->EditAnt2->Enabled = false;
		this->EditAppPos0->Enabled = false; this->EditAppPos1->Enabled = false; this->EditAppPos2->Enabled = false;
		this->EditAntDel0->Enabled = false; this->EditAntDel1->Enabled = false; this->EditAntDel2->Enabled = false;
		this->FirstTimeH1->Enabled = false; this->FirstTimeH1UD->Enabled = false;
		this->FirstTimeY1->Enabled = false; this->FirstTimeY1UD->Enabled = false;
		this->LastTimeH1->Enabled = false; this->LastTimeH1UD->Enabled = false;
		this->LastTimeY1->Enabled = false; this->LastTimeY1UD->Enabled = false;
		this->EditInterval->Enabled = false; this->EditLeapSec->Enabled = false;
		this->NavSys1->Enabled = false;this->NavSys2->Enabled = false;this->NavSys3->Enabled = false;
		this->NavSys4->Enabled = false; this->NavSys5->Enabled = false; this->NavSys6->Enabled = false;
		this->EditExSats->Enabled  = false;
		this->Freq1->Enabled = false; this->Freq2->Enabled = false; this->Freq3->Enabled = false;
		this->Freq4->Enabled = false; this->Freq5->Enabled = false; this->Freq6->Enabled = false;
		this->CheckScanObs->Enabled = false; this->BtnMask->Enabled = false;
		this->Obs1->Enabled = false; this->Obs2->Enabled = false; this->Obs3->Enabled = false;
		this->Obs4->Enabled = false;
		this->BtnOk->Enabled = false; this->BtnCancel->Enabled = false;
	}*/

}

// load options -------------------------------------------------------------
void __fastcall TconvMainWindow::LoadOpt(void)
{
    TIniFile *ini=new TIniFile(IniFile);
    AnsiString mask="1111111111111111111111111111111111111111111";

    RnxVer              =ini->ReadInteger("opt","rnxver",      0);
    RnxFile             =ini->ReadInteger("opt","rnxfile",     0);
    RnxCode             =ini->ReadString ("opt","rnxcode","0000");
    RunBy               =ini->ReadString ("opt","runby",      "");
    Marker              =ini->ReadString ("opt","marker",     "");
    MarkerNo            =ini->ReadString ("opt","markerno",   "");
    MarkerType          =ini->ReadString ("opt","markertype", "");
    Name[0]             =ini->ReadString ("opt","name0",      "");
    Name[1]             =ini->ReadString ("opt","name1",      "");
    Rec[0]              =ini->ReadString ("opt","rec0",       "");
    Rec[1]              =ini->ReadString ("opt","rec1",       "");
    Rec[2]              =ini->ReadString ("opt","rec2",       "");
    Ant[0]              =ini->ReadString ("opt","ant0",       "");
    Ant[1]              =ini->ReadString ("opt","ant1",       "");
    Ant[2]              =ini->ReadString ("opt","ant2",       "");
    AppPos[0]           =ini->ReadFloat  ("opt","apppos0",   0.0);
    AppPos[1]           =ini->ReadFloat  ("opt","apppos1",   0.0);
    AppPos[2]           =ini->ReadFloat  ("opt","apppos2",   0.0);
    AntDel[0]           =ini->ReadFloat  ("opt","antdel0",   0.0);
    AntDel[1]           =ini->ReadFloat  ("opt","antdel1",   0.0);
    AntDel[2]           =ini->ReadFloat  ("opt","antdel2",   0.0);
    Comment[0]          =ini->ReadString ("opt","comment0",   "");
    Comment[1]          =ini->ReadString ("opt","comment1",   "");
    RcvOption           =ini->ReadString ("opt","rcvoption",  "");
    NavSys              =ini->ReadInteger("opt","navsys",    0x3);
    ObsType             =ini->ReadInteger("opt","obstype",   0xF);
    FreqType            =ini->ReadInteger("opt","freqtype",  0x3);
    ExSats              =ini->ReadString ("opt","exsats",     "");
    TraceLevel          =ini->ReadInteger("opt","tracelevel",  0);
    RnxTime.time        =ini->ReadInteger("opt","rnxtime",     0);
    CodeMask[0]         =ini->ReadString ("opt","codemask_1",mask);
    CodeMask[1]         =ini->ReadString ("opt","codemask_2",mask);
    CodeMask[2]         =ini->ReadString ("opt","codemask_3",mask);
    CodeMask[3]         =ini->ReadString ("opt","codemask_4",mask);
    CodeMask[4]         =ini->ReadString ("opt","codemask_5",mask);
    CodeMask[5]         =ini->ReadString ("opt","codemask_6",mask);
    AutoPos             =ini->ReadInteger("opt","autopos",     0);
    ScanObs             =ini->ReadInteger("opt","scanobs",     0);
    OutIono             =ini->ReadInteger("opt","outiono",     0);
    OutTime             =ini->ReadInteger("opt","outtime",     0);
    OutLeaps            =ini->ReadInteger("opt","outleaps",    0);

	//TimeStartF ->Checked=ini->ReadInteger("set","timestartf",  0);
	//TimeEndF   ->Checked=ini->ReadInteger("set","timeendf",    0);
	//TimeIntF   ->Checked=ini->ReadInteger("set","timeintf",    0);
	//TimeY1     ->Text   =ini->ReadString ("set","timey1",     "2000/01/01");
	//TimeH1     ->Text   =ini->ReadString ("set","timeh1",     "00:00:00"  );
	//TimeY2     ->Text   =ini->ReadString ("set","timey2",     "2000/01/01");
	//TimeH2     ->Text   =ini->ReadString ("set","timeh2",     "00:00:00"  );
	//TimeInt    ->Text   =ini->ReadString ("set","timeint",   "1");
	//TimeUnitF  ->Checked=ini->ReadInteger("set","timeunitf",   0);
    //TimeUnit   ->Text   =ini->ReadString ("set","timeunit", "24");
    InFile     ->Text   =ini->ReadString ("set","infile",     "");
	//OutDir     ->Text   =ini->ReadString ("set","outdir",     "");
    OutFile1   ->Text   =ini->ReadString ("set","outfile1",   "");
    OutFile2   ->Text   =ini->ReadString ("set","outfile2",   "");
    OutFile3   ->Text   =ini->ReadString ("set","outfile3",   "");
    OutFile4   ->Text   =ini->ReadString ("set","outfile4",   "");
    OutFile5   ->Text   =ini->ReadString ("set","outfile5",   "");
    OutFile6   ->Text   =ini->ReadString ("set","outfile6",   "");
    OutFile7   ->Text   =ini->ReadString ("set","outfile7",   "");
	//OutDirEna  ->Checked=ini->ReadInteger("set","outdirena",   0);
    OutFileEna1->Checked=ini->ReadInteger("set","outfileena1", 1);
    OutFileEna2->Checked=ini->ReadInteger("set","outfileena2", 1);
    OutFileEna3->Checked=ini->ReadInteger("set","outfileena3", 1);
    OutFileEna4->Checked=ini->ReadInteger("set","outfileena4", 1);
    OutFileEna5->Checked=ini->ReadInteger("set","outfileena5", 1);
    OutFileEna6->Checked=ini->ReadInteger("set","outfileena6", 1);
    OutFileEna7->Checked=ini->ReadInteger("set","outfileena7", 1);
    ComFormat   ->ItemIndex=ini->ReadInteger("set","format",      0);

	//InFile->Items=ReadList(ini,"hist","inputfile");
    InFile->Text = ini->ReadString("hist","inputfile","");

    /*TTextViewer::Color1=(TColor)ini->ReadInteger("viewer","color1",(int)clBlack);
    TTextViewer::Color2=(TColor)ini->ReadInteger("viewer","color2",(int)clWhite);
    TTextViewer::FontD=new TFont;
    TTextViewer::FontD->Name=ini->ReadString ("viewer","fontname","Courier New");
	TTextViewer::FontD->Size=ini->ReadInteger("viewer","fontsize",9); */

    CmdPostExe         =ini->ReadString  ("set","cmdpostexe","rtkpost_mkl");

    delete ini;

    UpdateEnable();
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnInFileViewClick(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString InFile_Text=InFile->Text;

	if(InFile_Text.IsEmpty())
		return;
	try{
    	char *ext=strrchr(InFile_Text.c_str(),'.');
		if (!(*ext)||strlen(ext)<4)
			return;
		if (!strcmp(ext,".obs" )||!strcmp(ext,".OBS" )||!strcmp(ext,".nav")||
			!strcmp(ext,".NAV" )||!strcmp(ext+2,"nav")||!strcmp(ext,"NAV" )||
			!strcmp(ext+3,"o"  )||!strcmp(ext+3,"O"  )||!strcmp(ext+3,"n" )||
			!strcmp(ext+3,"N"  )||!strcmp(ext+3,"p"  )||!strcmp(ext+3,"P" )||
			!strcmp(ext+3,"g"  )||!strcmp(ext+3,"G"  )||!strcmp(ext+3,"h" )||
			!strcmp(ext+3,"H"  )||!strcmp(ext+3,"q"  )||!strcmp(ext+3,"Q" )||
			!strcmp(ext+3,"l"  )||!strcmp(ext+3,"L"  )) {
			viewer->Show();
			viewer->Read(RepPath(InFile_Text));
		}
	}
	catch(Exception &ex){
		Application->MessageBoxA(L"�޷��鿴�������ļ�",L"��ʾ",MB_OK);
	}
	catch (...){
		try{
			throw Exception("");
		}
		catch (Exception &ex){
			Application->MessageBoxA(L"�޷��鿴�������ļ�",L"��ʾ",MB_OK);
		}
	}
}
// replace keywords in file path --------------------------------------------
AnsiString __fastcall TconvMainWindow::RepPath(AnsiString File)
{
    AnsiString Path;
    char path[1024];
    reppath(File.c_str(),path,timeadd(RnxTime,TSTARTMARGIN),RnxCode.c_str(),"");
    return Path=path;
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnConvertClick(TObject *Sender)
{
	int i;
	if(this->InFile->Text.Trim().IsEmpty()) {
        Application->MessageBoxA(L"û����Ҫת�����ļ�",L"��ʾ",MB_OK);
		return;
    }

	if(this->ComRnxVer->ItemIndex==-1) {
		Application->MessageBoxA(L"��ѡ�����RINEX�汾",L"��ʾ",MB_OK);
		return;
	}
	else {
		RnxVer = this->ComRnxVer->ItemIndex;
	}
    RnxFile = this->CheckRnxFile->Checked;
	RnxCode = this->EditRnxCode->Text.Trim();
	RunBy = this->EditRunBy->Text.Trim();
	Marker = this->EditMarker->Text.Trim();
	MarkerNo = this->EditMarkerNo->Text.Trim();
	MarkerType = this->EditMarkerType->Text.Trim();
	Name[0]=this->EditName0->Text.Trim();
	Name[1] = this->EditName1->Text.Trim();
	Rec[0] = this->EditRec0->Text.Trim();
	Rec[1] = this->EditRec1->Text.Trim();
	Rec[2] = this->EditRec2->Text.Trim();
	Ant[0] = this->EditAnt0->Text.Trim();
	Ant[1] = this->EditAnt1->Text.Trim();
	Ant[2] = this->EditAnt2->Text.Trim();
    AutoPos = 1;
	AppPos[0] = str2dbl(this->EditAppPos0->Text.Trim());
	AppPos[1] = str2dbl(this->EditAppPos1->Text.Trim());
	AppPos[2] = str2dbl(this->EditAppPos2->Text.Trim());
	AntDel[0] = str2dbl(this->EditAntDel0->Text.Trim());
	AntDel[1] = str2dbl(this->EditAntDel1->Text.Trim());
	AntDel[2] = str2dbl(this->EditAntDel2->Text.Trim());
	Comment[0] = ""; Comment[1] = "";
	//MainWindow->RcvOption=RcvOption->Text;
	//for (int i=0;i<6;i++) MainWindow->CodeMask[i]=CodeMask[i];
	//MainWindow->AutoPos=AutoPos->Checked;
	ScanObs=this->CheckScanObs->Checked;
	OutIono=1;
	OutTime=1;
	OutLeaps=str2int(this->EditLeapSec->Text.Trim());

    int navsys=0,obstype=0,freqtype=0;
	if (NavSys1->Checked) navsys|=SYS_GPS;
	if (NavSys2->Checked) navsys|=SYS_GLO;
	if (NavSys3->Checked) navsys|=SYS_GAL;
	if (NavSys4->Checked) navsys|=SYS_QZS;
	if (NavSys5->Checked) navsys|=SYS_SBS;
	if (NavSys6->Checked) navsys|=SYS_CMP;
	if (Obs1->Checked) obstype|=OBSTYPE_PR;
	if (Obs2->Checked) obstype|=OBSTYPE_CP;
	if (Obs3->Checked) obstype|=OBSTYPE_DOP;
	if (Obs4->Checked) obstype|=OBSTYPE_SNR;
	if (Freq1->Checked) freqtype|=FREQTYPE_L1;
	if (Freq2->Checked) freqtype|=FREQTYPE_L2;
	if (Freq3->Checked) freqtype|=FREQTYPE_L5;
	if (Freq4->Checked) freqtype|=FREQTYPE_L6;
	if (Freq5->Checked) freqtype|=FREQTYPE_L7;
	if (Freq6->Checked) freqtype|=FREQTYPE_L8;

	NavSys = navsys;
	ObsType = obstype;
	FreqType = freqtype;
	ExSats = this->EditExSats->Text.Trim();

	for (int i=0;i<6;i++)
		CodeMask[i] = convMainWindow->CodeMask[i];

	ConvertFile();

	Application->MessageBoxA(L"ת�����",L"��ʾ",MB_OK);
}
// convert file -------------------------------------------------------------
void __fastcall TconvMainWindow::ConvertFile(void)
{
	obsd_t ttt = {0};

	rnxopt_t rnxopt={0};
    AnsiString InFile_Text=InFile->Text;
    AnsiString OutFile1_Text=OutFile1->Text,OutFile2_Text=OutFile2->Text;
    AnsiString OutFile3_Text=OutFile3->Text,OutFile4_Text=OutFile4->Text;
    AnsiString OutFile5_Text=OutFile5->Text,OutFile6_Text=OutFile6->Text;
    AnsiString OutFile7_Text=OutFile7->Text;
    int i,format,sat;
    char file[1024]="",*ofile[7],ofile_[7][1024]={""},msg[256],*p;
    char buff[256],tstr[32];
    double RNXVER[]={2.10,2.11,2.12,3.00,3.01,3.02};
    FILE *fp;

    // abort conversion
    if (BtnConvert->Caption=="�ж�") {
        abortf=1;
        return;
    }
    for (i=0;i<7;i++) ofile[i]=ofile_[i];

    // recognize input file format
    strcpy(file,InFile_Text.c_str());
    if (!(p=strrchr(file,'.'))) p=file;
    /*if (ComFormat->ItemIndex==0) { // auto
		if      (!strcmp(p,".rtcm2")) format=STRFMT_RTCM2;
        else if (!strcmp(p,".rtcm3")) format=STRFMT_RTCM3;
        else if (!strcmp(p,".gps"  )) format=STRFMT_OEM4;
        else if (!strcmp(p,".ubx"  )) format=STRFMT_UBX;
        else if (!strcmp(p,".log"  )) format=STRFMT_SS2;
        else if (!strcmp(p,".bin"  )) format=STRFMT_CRES;
        else if (!strcmp(p,".jps"  )) format=STRFMT_JAVAD;
        else if (!strcmp(p,".bnx"  )) format=STRFMT_BINEX;
        else if (!strcmp(p,".binex")) format=STRFMT_BINEX;
        else if (!strcmp(p,".rt17" )) format=STRFMT_RT17;
        else if (!strcmp(p,".obs"  )) format=STRFMT_RINEX;
        else if (!strcmp(p,".OBS"  )) format=STRFMT_RINEX;
        else if (!strcmp(p,".nav"  )) format=STRFMT_RINEX;
        else if (!strcmp(p,".NAV"  )) format=STRFMT_RINEX;
        else if (!strcmp(p+2,"nav" )) format=STRFMT_RINEX;
        else if (!strcmp(p+2,"NAV" )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"o"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"O"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"n"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"N"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"p"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"P"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"g"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"G"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"h"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"H"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"q"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"Q"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"l"   )) format=STRFMT_RINEX;
        else if (!strcmp(p+3,"L"   )) format=STRFMT_RINEX;
        else {
			//showmsg("file format can not be recognized");
			Application->MessageBoxA(L"���ݸ�ʽ����ȷ",L"��ʾ",MB_OK);
			return;
		}
    }
    else {
        for (i=0;formatstrs[i];i++) {
            if (ComFormat->Text==formatstrs[i]) break;
		}
		if (formatstrs[i]) format=i; else return;
	} */
	for(i=0;formatstrs[i];i++) {
		if(ComFormat->Text==formatstrs[i])
			break;
	}
	if (formatstrs[i])
		format=i;
	else {
        showmsg_conv("�ļ���ʽ����ʶ��");
    	return;
    }


    rnxopt.rnxver=RNXVER[RnxVer];

	/*if (format==STRFMT_RTCM2||format==STRFMT_RTCM3||format==STRFMT_RT17) {
        // input start date/time for rtcm 2 ro rtcm 3
		if (StartDialog->ShowModal()!=mrOk) return;
        rnxopt.trtcm=StartDialog->Time;
	}*/
    if (OutFile1->Enabled&&OutFileEna1->Checked) strcpy(ofile[0],OutFile1_Text.c_str());
    if (OutFile2->Enabled&&OutFileEna2->Checked) strcpy(ofile[1],OutFile2_Text.c_str());
    if (OutFile3->Enabled&&OutFileEna3->Checked) strcpy(ofile[2],OutFile3_Text.c_str());
    if (OutFile4->Enabled&&OutFileEna4->Checked) strcpy(ofile[3],OutFile4_Text.c_str());
    if (OutFile5->Enabled&&OutFileEna5->Checked) strcpy(ofile[4],OutFile5_Text.c_str());
    if (OutFile6->Enabled&&OutFileEna6->Checked) strcpy(ofile[5],OutFile6_Text.c_str());
    if (OutFile7->Enabled&&OutFileEna7->Checked) strcpy(ofile[6],OutFile7_Text.c_str());

    // check overwrite output file
    for (i=0;i<6;i++) {
		if (!*ofile[i]||!(fp=fopen(ofile[i],"r")))
			continue;
        fclose(fp);
        ConfDialog->Label2->Caption=ofile[i];
        if (ConfDialog->ShowModal()!=mrOk) return;
    }
	//GetTime(&rnxopt.ts,&rnxopt.te,&rnxopt.tint,&rnxopt.tunit);
	strncpy(rnxopt.staid,RnxCode.c_str(),31);
	//sprintf(rnxopt.prog,"%s %s",PRGNAME,VER_RTKLIB);
	strncpy(rnxopt.runby,RunBy.c_str(),31);
	strncpy(rnxopt.marker,Marker.c_str(),63);
	strncpy(rnxopt.markerno,MarkerNo.c_str(),31);
	strncpy(rnxopt.markertype,MarkerType.c_str(),31);
	for (i=0;i<2;i++) strncpy(rnxopt.name[i],Name[i].c_str(),31);
	for (i=0;i<3;i++) strncpy(rnxopt.rec [i],Rec [i].c_str(),31);
	for (i=0;i<3;i++) strncpy(rnxopt.ant [i],Ant [i].c_str(),31);
	if (AutoPos) {
		for (i=0;i<3;i++) rnxopt.apppos[i]=AppPos[i];
	}
	for (i=0;i<3;i++) rnxopt.antdel[i]=AntDel[i];
	strncpy(rnxopt.rcvopt,RcvOption.c_str(),255);
	rnxopt.navsys=NavSys;
	rnxopt.obstype=ObsType;
	rnxopt.freqtype=FreqType;
	p=rnxopt.comment[0];
	sprintf(p,"log: %-53.53s",file);
	p=rnxopt.comment[1];
	p+=sprintf(p,"format: %s",formatstrs[format]);
	if (*rnxopt.rcvopt) sprintf(p,", option: %s",rnxopt.rcvopt);
	for (i=0;i<2;i++) strncpy(rnxopt.comment[i+2],Comment[i].c_str(),63);
	for (i=0;i<6;i++) strcpy(rnxopt.mask[i],CodeMask[i].c_str());
	rnxopt.autopos=AutoPos;
	rnxopt.scanobs=ScanObs;
	rnxopt.outiono=OutIono;
	rnxopt.outtime=OutTime;
	rnxopt.outleaps=OutLeaps;

	rnxopt.tint = StrToFloat(this->EditInterval->Text);

	AnsiString as_tstr1=this->FirstTimeY1->Text,as_tstr2= this->FirstTimeH1->Text;
	char *s_tstr1 = as_tstr1.c_str() ,*s_tstr2= as_tstr2.c_str();
	double ep1[6]={0.0};
	sscanf(s_tstr1,"%lf/%lf/%lf",ep1,ep1+1,ep1+2);
	sscanf(s_tstr2,"%lf:%lf:%lf",ep1+3,ep1+4,ep1+5);
	rnxopt.tstart = epoch2time(ep1);
	rnxopt.ts=epoch2time(ep1);

	AnsiString ae_tstr1 = this->LastTimeY1->Text,ae_tstr2 =this->LastTimeH1->Text;
	char *e_tstr1 = ae_tstr1.c_str() ,*e_tstr2= ae_tstr2.c_str();
	double ep2[6] = {0.0};
	sscanf(e_tstr1,"%lf/%lf/%lf",ep2,ep2+1,ep2+2);
	sscanf(e_tstr2,"%lf:%lf:%lf",ep2+3,ep2+4,ep2+5);
	rnxopt.tend = epoch2time(ep2);
	rnxopt.te = epoch2time(ep2);

	strcpy(buff,ExSats.c_str());
	for (p=strtok(buff," ");p;p=strtok(NULL," ")) {
		if (!(sat=satid2no(p))) continue;
		rnxopt.exsats[sat-1]=1;
	}
	abortf=0;
	BtnConvert  ->Caption="�ж�";
	Panel1      ->Enabled=false;
	Panel2      ->Enabled=false;
	//BtnPlot     ->Enabled=false;
	//BtnPost     ->Enabled=false;
	//BtnOptions  ->Enabled=false;
	//BtnExit     ->Enabled=false;
	ComFormat      ->Enabled=false;
	//BtnKey      ->Enabled=false;
	//LabelInFile ->Enabled=false;
	//LabelOutDir ->Enabled=false;
	//LabelOutFile->Enabled=false;
	//LabelFormat ->Enabled=false;
	Message     ->Caption="";

	if (TraceLevel>0) {
		traceopen(TRACEFILE);
		tracelevel(TraceLevel);
	}
	// convert to rinex
	(void)convrnx(format,&rnxopt,file,ofile);

	if (TraceLevel>0) {
		traceclose();
	}
	//BtnConvert  ->Caption="&Convert";
    BtnConvert->Caption = "ת��";
	Panel1      ->Enabled=true;
	Panel2      ->Enabled=true;
	//BtnPlot     ->Enabled=true;
	//BtnPost     ->Enabled=true;
	//BtnOptions  ->Enabled=true;
	//BtnExit     ->Enabled=true;
	ComFormat      ->Enabled=true;
	//BtnKey      ->Enabled=true;
	//LabelInFile ->Enabled=true;
	//LabelOutDir ->Enabled=true;
	//LabelOutFile->Enabled=true;
	//LabelFormat ->Enabled=true;

	RnxTime=rnxopt.tstart;

	//AddHist(InFile);
}

//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnOutFileView1Click(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString OutFile1_Text=OutFile1->Text;

	if(OutFile1_Text.IsEmpty())
		return;

	viewer->Show();
    viewer->Read(RepPath(OutFile1_Text));
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnOutFileView2Click(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString OutFile2_Text=OutFile2->Text;

	if(OutFile2_Text.IsEmpty())
		return;

    viewer->Show();
	viewer->Read(RepPath(OutFile2_Text));
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnOutFileView3Click(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString OutFile3_Text=OutFile3->Text;

	if(OutFile3_Text.IsEmpty())
		return;

	viewer->Show();
	viewer->Read(RepPath(OutFile3_Text));
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnOutFileView4Click(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString OutFile4_Text=OutFile4->Text;

	if(OutFile4_Text.IsEmpty())
		return;

    viewer->Show();
	viewer->Read(RepPath(OutFile4_Text));
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnOutFileView5Click(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString OutFile5_Text=OutFile5->Text;

	if(OutFile5_Text.IsEmpty())
		return;

    viewer->Show();
	viewer->Read(RepPath(OutFile5_Text));
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnOutFileView6Click(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString OutFile6_Text=OutFile6->Text;

	if(OutFile6_Text.IsEmpty())
		return;

    viewer->Show();
	viewer->Read(RepPath(OutFile6_Text));
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnOutFileView7Click(TObject *Sender)
{
	TTextViewer *viewer=new TTextViewer(Application);
	AnsiString OutFile7_Text=OutFile7->Text;

	if(OutFile7_Text.IsEmpty())
		return;

    viewer->Show();
    viewer->Read(RepPath(OutFile7_Text));
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::InFileChange(TObject *Sender)
{
	SetOutFiles(InFile->Text);
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::ComFormatChange(TObject *Sender)
{
	UpdateEnable();

	if(this->ComFormat->Text.Trim()=="RINEX") {
		BtnCancelClick(Sender);
		this->BtnOk->Enabled = true;
		this->BtnCancel->Enabled = true;
	}
	else{
		this->ComRnxVer->Enabled = true; this->EditRnxCode->Enabled = true;this->CheckRnxFile->Enabled = true;
		this->EditMarker->Enabled = true;this->EditMarkerNo->Enabled = true;this->EditMarkerType->Enabled = true;
		this->EditRunBy->Enabled = true;this->EditName0->Enabled = true;this->EditName1->Enabled = true;
		this->EditRec0->Enabled = true; this->EditRec1->Enabled = true; this->EditRec2->Enabled = true;
		this->EditAnt0->Enabled = true; this->EditAnt1->Enabled = true;this->EditAnt2->Enabled = true;
		this->EditAppPos0->Enabled = true; this->EditAppPos1->Enabled = true; this->EditAppPos2->Enabled = true;
		this->EditAntDel0->Enabled = true; this->EditAntDel1->Enabled = true; this->EditAntDel2->Enabled = true;
		this->FirstTimeH1->Enabled = true; this->FirstTimeH1UD->Enabled = true;
		this->FirstTimeY1->Enabled = true; this->FirstTimeY1UD->Enabled = true;
		this->LastTimeH1->Enabled = true; this->LastTimeH1UD->Enabled = true;
		this->LastTimeY1->Enabled = true; this->LastTimeY1UD->Enabled = true;
		this->EditInterval->Enabled = true; this->EditLeapSec->Enabled = true;

		this->ComRnxVer->ItemIndex=-1;this->EditRnxCode->Text="";this->CheckRnxFile->Checked=false;
		this->EditMarker->Text="";this->EditMarkerNo->Text="";this->EditMarkerType->Text="";
		this->EditRunBy->Text="";this->EditName0->Text="";this->EditName1->Text="";
		this->EditRec0->Text="";this->EditRec1->Text="";this->EditRec2->Text="";
		this->EditAnt0->Text="";this->EditAnt1->Text="";this->EditAnt2->Text="";
		this->EditAppPos0->Text="";this->EditAppPos1->Text="";this->EditAppPos2->Text="";
		this->EditAntDel0->Text="";this->EditAntDel1->Text="";this->EditAntDel2->Text="";
		this->FirstTimeY1->Text="2000/01/01";this->FirstTimeH1->Text="00:00:00";
		this->LastTimeY1->Text="2000/01/01";this->LastTimeH1->Text="00:00:00";
		this->EditInterval->Text="";this->EditLeapSec->Text="";

		this->BtnOk->Enabled = false;
		this->BtnCancel->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::FirstTimeY1UDChangingEx(TObject *Sender, bool &AllowChange,
          short NewValue, TUpDownDirection Direction)
{
	AnsiString TimeY1_Text=FirstTimeY1->Text,s;
    double ep[]={2000,1,1,0,0,0};
    int p=FirstTimeY1->SelStart,ud=Direction==updUp?1:-1;
    sscanf(TimeY1_Text.c_str(),"%lf/%lf/%lf",ep,ep+1,ep+2);
    if (4<p&&p<8) {
        ep[1]+=ud;
        if (ep[1]<=0) {ep[0]--; ep[1]+=12;}
        else if (ep[1]>12) {ep[0]++; ep[1]-=12;}
    }
    else if (p>7||p==0) ep[2]+=ud; else ep[0]+=ud;
    time2epoch(epoch2time(ep),ep);
    FirstTimeY1->Text=s.sprintf("%04.0f/%02.0f/%02.0f",ep[0],ep[1],ep[2]);
    FirstTimeY1->SelStart=p>7||p==0?10:(p>4?7:4);
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::FirstTimeH1UDChangingEx(TObject *Sender, bool &AllowChange,
          short NewValue, TUpDownDirection Direction)
{
	AnsiString TimeH1_Text=FirstTimeH1->Text,s;
    int hms[3]={0},sec,p=FirstTimeH1->SelStart,ud=Direction==updUp?1:-1;
    sscanf(TimeH1_Text.c_str(),"%d:%d:%d",hms,hms+1,hms+2);
    if (p>5||p==0) hms[2]+=ud; else if (p>2) hms[1]+=ud; else hms[0]+=ud;
    sec=hms[0]*3600+hms[1]*60+hms[2];
    if (sec<0) sec+=86400; else if (sec>=86400) sec-=86400;
    FirstTimeH1->Text=s.sprintf("%02d:%02d:%02d",sec/3600,(sec%3600)/60,sec%60);
    FirstTimeH1->SelStart=p>5||p==0?8:(p>2?5:2);
}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::LastTimeY1UDChangingEx(TObject *Sender, bool &AllowChange,
          short NewValue, TUpDownDirection Direction)
{
	AnsiString TimeY2_Text=LastTimeY1->Text,s;
    double ep[]={2000,1,1,0,0,0};
    int p=LastTimeY1->SelStart,ud=Direction==updUp?1:-1;
    sscanf(TimeY2_Text.c_str(),"%lf/%lf/%lf",ep,ep+1,ep+2);
    if (4<p&&p<8) {
        ep[1]+=ud;
        if (ep[1]<=0) {ep[0]--; ep[1]+=12;}
        else if (ep[1]>12) {ep[0]++; ep[1]-=12;}
    }
    else if (p>7||p==0) ep[2]+=ud; else ep[0]+=ud;
    time2epoch(epoch2time(ep),ep);
	LastTimeY1->Text=s.sprintf("%04.0f/%02.0f/%02.0f",ep[0],ep[1],ep[2]);
    LastTimeY1->SelStart=p>7||p==0?10:(p>4?7:4);
}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::LastTimeH1UDChangingEx(TObject *Sender, bool &AllowChange,
          short NewValue, TUpDownDirection Direction)
{
	AnsiString TimeH2_Text=LastTimeH1->Text,s;
    int hms[3]={0},sec,p=LastTimeH1->SelStart,ud=Direction==updUp?1:-1;
    sscanf(TimeH2_Text.c_str(),"%d:%d:%d",hms,hms+1,hms+2);
    if (p>5||p==0) hms[2]+=ud; else if (p>2) hms[1]+=ud; else hms[0]+=ud;
    sec=hms[0]*3600+hms[1]*60+hms[2];
    if (sec<0) sec+=86400; else if (sec>=86400) sec-=86400;
    LastTimeH1->Text=s.sprintf("%02d:%02d:%02d",sec/3600,(sec%3600)/60,sec%60);
    LastTimeH1->SelStart=p>5||p==0?8:(p>2?5:2);
}
//---------------------------------------------------------------------------
void __fastcall TconvMainWindow::BtnOkClick(TObject *Sender)
{
	this->ComRnxVer->Enabled = true; this->EditRnxCode->Enabled = true;this->CheckRnxFile->Enabled = true;
	this->EditMarker->Enabled = true;this->EditMarkerNo->Enabled = true;this->EditMarkerType->Enabled = true;
	this->EditRunBy->Enabled = true;this->EditName0->Enabled = true;this->EditName1->Enabled = true;
	this->EditRec0->Enabled = true; this->EditRec1->Enabled = true; this->EditRec2->Enabled = true;
	this->EditAnt0->Enabled = true; this->EditAnt1->Enabled = true;this->EditAnt2->Enabled = true;
	this->EditAppPos0->Enabled = true; this->EditAppPos1->Enabled = true; this->EditAppPos2->Enabled = true;
	this->EditAntDel0->Enabled = true; this->EditAntDel1->Enabled = true; this->EditAntDel2->Enabled = true;
	this->FirstTimeH1->Enabled = true; this->FirstTimeH1UD->Enabled = true;
	this->FirstTimeY1->Enabled = true; this->FirstTimeY1UD->Enabled = true;
	this->LastTimeH1->Enabled = true; this->LastTimeH1UD->Enabled = true;
	this->LastTimeY1->Enabled = true; this->LastTimeY1UD->Enabled = true;
	this->EditInterval->Enabled = true; this->EditLeapSec->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnCancelClick(TObject *Sender)
{
	if(!InFile->Text.IsEmpty())
		SetConvOptVal(InFile->Text);

	this->ComRnxVer->Enabled = false; this->EditRnxCode->Enabled = false;this->CheckRnxFile->Enabled = false;
	this->EditMarker->Enabled = false;this->EditMarkerNo->Enabled = false;this->EditMarkerType->Enabled = false;
	this->EditRunBy->Enabled = false;this->EditName0->Enabled = false;this->EditName1->Enabled = false;
	this->EditRec0->Enabled = false; this->EditRec1->Enabled = false; this->EditRec2->Enabled = false;
	this->EditAnt0->Enabled = false; this->EditAnt1->Enabled = false;this->EditAnt2->Enabled = false;
	this->EditAppPos0->Enabled = false; this->EditAppPos1->Enabled = false; this->EditAppPos2->Enabled = false;
	this->EditAntDel0->Enabled = false; this->EditAntDel1->Enabled = false; this->EditAntDel2->Enabled = false;
	this->FirstTimeH1->Enabled = false; this->FirstTimeH1UD->Enabled = false;
	this->FirstTimeY1->Enabled = false; this->FirstTimeY1UD->Enabled = false;
	this->LastTimeH1->Enabled = false; this->LastTimeH1UD->Enabled = false;
	this->LastTimeY1->Enabled = false; this->LastTimeY1UD->Enabled = false;
	this->EditInterval->Enabled = false; this->EditLeapSec->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::BtnMaskClick(TObject *Sender)
{
	/*CodeOptDialog->NavSys=0;
	CodeOptDialog->FreqType=0;
	if (NavSys1->Checked) CodeOptDialog->NavSys|=SYS_GPS;
	if (NavSys2->Checked) CodeOptDialog->NavSys|=SYS_GLO;
	if (NavSys3->Checked) CodeOptDialog->NavSys|=SYS_GAL;
	if (NavSys4->Checked) CodeOptDialog->NavSys|=SYS_QZS;
	if (NavSys5->Checked) CodeOptDialog->NavSys|=SYS_SBS;
	if (NavSys6->Checked) CodeOptDialog->NavSys|=SYS_CMP;
	if (Freq1->Checked) CodeOptDialog->FreqType|=FREQTYPE_L1;
	if (Freq2->Checked) CodeOptDialog->FreqType|=FREQTYPE_L2;
	if (Freq3->Checked) CodeOptDialog->FreqType|=FREQTYPE_L5;
	if (Freq4->Checked) CodeOptDialog->FreqType|=FREQTYPE_L6;
	if (Freq5->Checked) CodeOptDialog->FreqType|=FREQTYPE_L7;
	if (Freq6->Checked) CodeOptDialog->FreqType|=FREQTYPE_L8; */
	CodeOptDialog->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TconvMainWindow::ComRnxVerChange(TObject *Sender)
{
	UpdateEnable();
}
//---------------------------------------------------------------------------



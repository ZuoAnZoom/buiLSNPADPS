//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LSNMAIN.h"

#include "strsvrmain.h"
#include "convmain.h"
#include "rtkplotmain.h"
#include "aboutdlg.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	strsvrMainWindow = new TstrsvrMainWindow(this->strsvrgroup);
	strsvrMainWindow->Parent = this->strsvrgroup;
	strsvrMainWindow->Show();

	convMainWindow = new TconvMainWindow(this->rtkconvgroup);
	convMainWindow->Parent = this->rtkconvgroup;
	convMainWindow->Show();

	rtkplotMainWindow = new TrtkplotMainWindow(this->rtkplotgroup);
	rtkplotMainWindow->Parent = this->rtkplotgroup;
	rtkplotMainWindow->Show();

	//rtkpostMainWindow = new TrtkpostMainWindow(this->rtkpostgroup);
	//rtkpostMainWindow->Parent = this->rtkpostgroup;
	//rtkpostMainWindow->Show();

	//rtknavMainWindow = new TrtknavMainWindow(this->rtknavgroup);
	//rtknavMainWindow->Parent = this->rtknavgroup;
	//rtknavMainWindow->Show();

	this->StatusBar1->Panels->Items[1]->Text = Now().FormatString("YYYY-MM-DD HH:MM:SS    ");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
	this->StatusBar1->Panels->Items[1]->Text = Now().FormatString("yyyy-mm-dd hh:mm:ss    ");
}
// callback on drag-and-drop files ------------------------------------------
void __fastcall TMainForm::DropFiles(TWMDropFiles msg)
{
	int pageIndex = this->aogroup->ActivePageIndex;
	if(pageIndex!=2)
		return;

    TStringList *files=new TStringList;
    AnsiString s;
    int i,n;
    char buff[1024],file[1024],*ext;

	trace(3,"DropFiles\n");

	if ((n=DragQueryFile((HDROP)msg.Drop,0xFFFFFFFF,NULL,0))<=0) {
		delete files;
		return;
	}
    for (i=0;i<n;i++) {
		DragQueryFile((HDROP)msg.Drop,i,buff,sizeof(buff));
		files->Add(buff);
    }
	strcpy(file,rtkplotMainWindow->U2A(files->Strings[0]).c_str());

	AnsiString IniFile;
	if(rtkplotMainWindow->CheckObs((s=file))){
		rtkplotMainWindow->ReadObs(files);
	}

	delete files;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	//int pageIndex = this->aogroup->ActivePageIndex;
	//if(pageIndex==2)

	//::DragAcceptFiles(Handle,true);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actQuitClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::ExecCmd(AnsiString cmd,int show)
{
	PROCESS_INFORMATION info;
	STARTUPINFO si={0};
	si.cb = sizeof(si);
	char *p = cmd.c_str();
    if (!CreateProcess(NULL,p,NULL,NULL,false,show?0:CREATE_NO_WINDOW,NULL,
                       NULL,&si,&info)) return 0;
    CloseHandle(info.hProcess);
    CloseHandle(info.hThread);
    return 1;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actHelpClick(TObject *Sender)
{
	AnsiString cmd1 = "hh.exe ",opts="GNSS数据质量评估软件.CHM";
	if(FileExists(opts)) {
        if(!ExecCmd(cmd1+opts,1)) MessageBox(Handle,"打开CHM文件错误！","提示",MB_OK);
	}
	else {
        MessageBox(Handle,"CHM文件不存在！","提示",MB_OK);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actAboutClick(TObject *Sender)
{
	AboutDialog->ShowModal();
}
//---------------------------------------------------------------------------



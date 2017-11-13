//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("strsvr\strsvrmain.cpp", strsvrMainWindow);
USEFORM("rtkconv\codeopt.cpp", CodeOptDialog);
USEFORM("rtkconv\convmain.cpp", convMainWindow);
USEFORM("appcmn\fileoptdlg.cpp", FileOptDialog);
USEFORM("appcmn\aboutdlg.cpp", AboutDialog);
USEFORM("appcmn\confdlg.cpp", ConfDialog);
USEFORM("appcmn\viewer.cpp", TextViewer);
USEFORM("LSNMAIN.cpp", MainForm);
USEFORM("appcmn\serioptdlg.cpp", SerialOptDialog);
USEFORM("appcmn\tcpoptdlg.cpp", TcpOptDialog);
USEFORM("rtkplot\rtkplotmain.cpp", rtkplotMainWindow);
USEFORM("rtkplot\rtkplotopt.cpp", rtkplotOptDialog);
USEFORM("rtkplot\rtkplotallassess.cpp", rtkplotallassessDialog);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TconvMainWindow), &convMainWindow);
		Application->CreateForm(__classid(TrtkplotMainWindow), &rtkplotMainWindow);
		Application->CreateForm(__classid(TrtkplotOptDialog), &rtkplotOptDialog);
		Application->CreateForm(__classid(TstrsvrMainWindow), &strsvrMainWindow);
		Application->CreateForm(__classid(TTextViewer), &TextViewer);
		Application->CreateForm(__classid(TConfDialog), &ConfDialog);
		Application->CreateForm(__classid(TSerialOptDialog), &SerialOptDialog);
		Application->CreateForm(__classid(TFileOptDialog), &FileOptDialog);
		Application->CreateForm(__classid(TTcpOptDialog), &TcpOptDialog);
		Application->CreateForm(__classid(TCodeOptDialog), &CodeOptDialog);
		Application->CreateForm(__classid(TAboutDialog), &AboutDialog);
		Application->CreateForm(__classid(TrtkplotallassessDialog), &rtkplotallassessDialog);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

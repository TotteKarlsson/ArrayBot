#pragma hdrstop
#include "TMainForm.h"
#include "mtkVCLUtils.h"
#include "mtkLogger.h"
#pragma package(smart_init)
using Poco::DateTimeFormatter;

using namespace mtk;

static HWND         gOtherAppWindow             = NULL;

void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TMainForm::ClearMemoAExecute(TObject *Sender)
{
    infoMemo->Clear();
}

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	static TCHAR buffer[50];
	GetWindowText(hwnd, buffer, 50);

	if(_tcsstr(buffer, "iBot"))
	{
		// do something with hwnd here
		gOtherAppWindow = hwnd;
		return FALSE;
	}

	return TRUE;
}




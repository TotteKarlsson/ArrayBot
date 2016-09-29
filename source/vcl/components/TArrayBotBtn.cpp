#include <vcl.h>
#pragma hdrstop
#include "TArrayBotBtn.h"
#include "mtkLogger.h"
#include "sound/abDirectSound.h"
#include "abCore.h"
#include "mtkVCLUtils.h"


#pragma package(smart_init)

using namespace mtk;

//---------------------------------------------------------------------------
__fastcall TArrayBotButton::TArrayBotButton(TComponent* Owner)
	: TBitBtn(Owner),
    FSoundID("BUTTON_CLICK_4")
{
	initABCoreLib();
}

void __fastcall	TArrayBotButton::CreateWnd()
{
	TWinControl::CreateWnd();
    if(!this->Handle)
    {
    	Log(lError) << "The button does not have a handle";
    }

    if(!mSound.Create(stdstr(FSoundID), this->Handle))
    {
    	Log(lError) << "Failed creating sound for button";
    }
}

void __fastcall	TArrayBotButton::DestroyWnd()
{
}

//void __fastcall TArrayBotButton::setSoundID(const String& snd)
//{
//	FSoundID = snd;
////	HWND hWnd = this->Handle;
////    if(!mSound.Create(FSoundID.c_str(), hWnd))
////    {
////    	MessageDlg("Failed creating that sound..", mtWarning, TMsgDlgButtons() << mbOK, 0);
////    }
//}
//
//String __fastcall TArrayBotButton::getSoundID()
//{
//	return FSoundID;
//}

bool TArrayBotButton::init(HWND wnd)
{
	return true;
}

void __fastcall TArrayBotButton::WndProc(TMessage& msg)
{
	const int WM_POINTERDOWN 	= 0x0246;
    const int WM_POINTERUP 		= 0x247;

    switch (msg.Msg)
    {
    	case WM_POINTERDOWN:
        	Log(lDebug) << "Touch Down";
        break;
        case WM_POINTERUP:
        	Log(lDebug) << "Touch Up";
        break;
        case WM_LBUTTONUP:
            mSound.Play(0, false);
		break;

        case WM_LBUTTONDOWN:
//            mSound.Play(0, false);
		break;
    }

    TBitBtn::WndProc(msg);
}

static inline void ValidCtrCheck(TArrayBotButton *)
{
	new TArrayBotButton(NULL);
}

//---------------------------------------------------------------------------
namespace Tarraybotbtn
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TArrayBotButton)};
		RegisterComponents(L"AI", classes, 0);
	}
}


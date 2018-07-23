#include <vcl.h>
#pragma hdrstop
#include "TArrayBotBtn.h"
#include "dslLogger.h"
//#include "sound/atDirectSound.h"
#include "core/atCore.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)

using namespace dsl;
using namespace at;
//---------------------------------------------------------------------------
__fastcall TArrayBotButton::TArrayBotButton(TComponent* Owner)
	: TBitBtn(Owner),
    FSoundID("BUTTON_CLICK_4"),
    mSound("", NULL)
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

    if(!mSound.create(stdstr(FSoundID), this->Handle))
    {
    	Log(lError) << "Failed creating sound for button";
    }
}

void __fastcall	TArrayBotButton::DestroyWnd()
{
}

bool TArrayBotButton::init(HWND wnd)
{
	return true;
}

void __fastcall TArrayBotButton::WndProc(TMessage& msg)
{
    switch (msg.Msg)
    {
    	case WM_POINTERDOWN:        	Log(lDebug) << "Touch Down";        break;
        case WM_POINTERUP:        		Log(lDebug) << "Touch Up";        	break;
        case WM_LBUTTONUP:            	mSound.play(0, false);				break;
//        case WM_LBUTTONDOWN:            mSound.Play(0, false);       		break;
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


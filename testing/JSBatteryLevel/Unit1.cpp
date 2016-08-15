#include <vcl.h>
#pragma hdrstop
#include <XInput.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

	HINSTANCE l = LoadLibrary("xinput1_3.dll");
    if(l)
    {
    	MessageDlg("Loaded dll", mtWarning, TMsgDlgButtons() << mbOK, 0);
    }

//    // Dummy call to ensure the system activates the controller
    XINPUT_STATE state;

//DWORD WINAPI XInputGetState
//(
//    DWORD         dwUserIndex,  // [in] Index of the gamer associated with the device
//    XINPUT_STATE* pState        // [out] Receives the current state
//);


    typedef DWORD (CALLBACK* XInputGetStateFP)(DWORD, XINPUT_STATE*);
	XInputGetStateFP test = NULL;
    test = (XInputGetStateFP) (GetProcAddress(l, "XInputGetState"));

    if(test)
    {
    	MessageDlg("Loaded dll", mtWarning, TMsgDlgButtons() << mbOK, 0);
    }

    XInputGetStateFP(0, &state);

//    if(stateGamepad)
//    {
//    	MessageDlg("Loaded dll", mtWarning, TMsgDlgButtons() << mbOK, 0);
//    }
	if(state.dwPacketNumber != 0)
    {
    	MessageDlg("Loaded dll", mtWarning, TMsgDlgButtons() << mbOK, 0);
    }



    // Get the actual battery info
//    XINPUT_BATTERY_INFORMATION info;
//    if (XInputGetBatteryInformation(0, BATTERY_DEVTYPE_GAMEPAD, &info) != ERROR_SUCCESS)
//    {
//        info.BatteryType = BATTERY_TYPE_DISCONNECTED;
//    }

////    const wchar_t *tip = icon_label;
////    wired_ = false;
//    switch (info.BatteryType)
//    {
//        case BATTERY_TYPE_WIRED:
////            batlevel_ = 1;
////            nocontroller_ = false;
////            unknown_ = false;
////            wired_ = true;
////            tip = L"Wired Controller";
//            break;
//
//        case BATTERY_TYPE_ALKALINE:
//        case BATTERY_TYPE_NIMH:
////            switch (info.BatteryLevel)
////            {
////                case BATTERY_LEVEL_EMPTY:
//////                    batlevel_ = 0;
//////                    tip = L"Controller battery is empty";
////                    break;
////                case BATTERY_LEVEL_LOW:
////                    batlevel_ = 0.3f;
////                    tip = L"Controller battery is getting low";
////                    break;
////                case BATTERY_LEVEL_MEDIUM:
////                    batlevel_ = 0.6f;
////                    tip = L"Controller battery is OK";
////                    break;
////                case BATTERY_LEVEL_FULL:
////                    batlevel_ = 1;
////                    tip = L"Controller battery is full";
////                    break;
////            }
////            nocontroller_ = false;
////            unknown_ = false;
//            break;
//
//        case BATTERY_TYPE_UNKNOWN:
////            batlevel_ = 0;
////            nocontroller_ = false;
////            unknown_ = true;
////            tip = L"Battery level couldn't be read";
//
//        case BATTERY_TYPE_DISCONNECTED:
//        default:
////            batlevel_ = 0;
////            nocontroller_ = true;
////            unknown_ = false;
////            wired_ = true;
////            tip = L"No controller connected";
//            break;
//    }
//
////    NOTIFYICONDATAW idata = { sizeof(idata) };
////    idata.hWnd = hwnd_;
////    idata.uID = icon_id;
////    idata.hIcon = MakeIcon(true);
////    idata.uFlags = NIF_ICON | NIF_TIP;
////    wcscpy_s(idata.szTip, tip);

}
//---------------------------------------------------------------------------

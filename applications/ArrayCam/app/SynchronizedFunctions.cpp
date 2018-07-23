#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "atVCLUtils.h"
#include "dslStringList.h"

using namespace dsl;

class TLocalArgs
{
    public:
    	string msg;

    void __fastcall onLightsArduinoMessage()
    {
        //If mouse is down.. do not update certain UI objects
        bool isMouseBtnDown = (bool) GetAsyncKeyState(VK_LBUTTON);

        if(startsWith("AB_LIGHTS_DATA", msg) && isMouseBtnDown == false)
        {
            StringList l(msg,',');
            if(l.size() == 3)
            {
            	StringList val(l[1], '=');
                MainForm->FrontLEDTB->Tag = 1;
                MainForm->FrontLEDTB->Position = toInt(val[1]);
                MainForm->FrontLEDTB->Tag = 0;
            }
        }
    }
};

void TMainForm::onLightsArduinoMessageReceived(const string& msg)
{
    TLocalArgs args;
    args.msg = msg;

    //This causes this fucntion to be called in the UI thread
	TThread::Synchronize(NULL, &args.onLightsArduinoMessage);
}




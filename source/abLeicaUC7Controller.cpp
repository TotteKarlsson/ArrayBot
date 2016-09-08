#pragma hdrstop
#include "abLeicaUC7Controller.h"
#include "abPufferArduino.h"
//---------------------------------------------------------------------------

using namespace mtk;

LeicaUC7Controller::LeicaUC7Controller(PufferArduino& p)
:
mPufferArduino(p)
{}


bool LeicaUC7Controller::setCutPreset(int cutPreset)
{
	//There are five cut presets, 1-5. Requests for any is
    //send trough the puffer Arduino
    stringstream msg;
    msg <<"P"<<cutPreset<<'\n';

    bool res = mPufferArduino.send(msg.str());
    if(res)
    {
    	Log(lDebug) << "Cut Preset "<<cutPreset<<" requested";
    }
    else
    {
    	Log(lError) << "Failed to request cut preset: "<<cutPreset;
    }
    return res;
}

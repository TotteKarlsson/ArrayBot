#pragma hdrstop
#include "abLeicaUC7Controller.h"
#include "abPufferArduino.h"
//---------------------------------------------------------------------------

using namespace mtk;

LeicaUC7Controller::LeicaUC7Controller(PufferArduino& p)
:
mPufferArduino(p),
mLastSetCutThicknessPreset(-1)
{}

bool LeicaUC7Controller::setCutThicknessPreset(int cutPreset)
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
    	Log(lError) << "Failed Request: P"<<cutPreset;
    }
    mLastSetCutThicknessPreset = cutPreset;
    return res;
}

bool LeicaUC7Controller::setDeltaY(int dy)
{
	//The deltaY sets the step for the
    //mouse when moving between presets
    stringstream msg;
    msg <<"Y"<<dy<<'\n';

    bool res = mPufferArduino.send(msg.str());
    if(res)
    {
    	Log(lDebug) << "Delta Y "<<dy<<" requested";
    }
    else
    {
    	Log(lError) << "Failed Request: Y"<<dy;
    }
    return res;
}

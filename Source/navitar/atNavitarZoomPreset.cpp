#pragma hdrstop
#include "atNavitarZoomPreset.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{
    NavitarZoomPreset::NavitarZoomPreset(NavitarMotorController& mc, const string& name, const int& z)
    :
    Preset<int>(name, z),
    mController(mc)
    {}

    NavitarZoomPreset::~NavitarZoomPreset()
    {}

    bool NavitarZoomPreset::set()
    {
    	Log(lInfo) << "Setting preset: " << mKey << " value = " << getValue();
    	return mController.getZoom().setPosition(getValue());
    }
}

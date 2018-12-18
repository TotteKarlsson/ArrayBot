#pragma hdrstop
#include "atNavitarPreset.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;


namespace at
{
    NavitarPreset::NavitarPreset(NavitarMotorController& mc, const string& name, const int& z, const int& f)
    :
    mName(name),
    mZoom(mc, "Zoom", z),
    mFocus(mc, "Focus", f),
    mController(mc)
    {}

    NavitarPreset::~NavitarPreset()
    {}

    string NavitarPreset::getName()
    {
    	return mName;
    }

    bool NavitarPreset::setName(const string& n)
    {
    	mName = n;
        return true;
    }

    int NavitarPreset::getFocusPreset()
    {
    	return mFocus.getValue();
    }

    int NavitarPreset::getZoomPreset()
    {
    	return mZoom.getValue();
    }

    bool NavitarPreset::set()
    {
    	mZoom.set();
        mFocus.set();
        return true;
    }

    bool NavitarPreset::setup(const string& iniSection, IniFile& iniFile)
    {
    	setSectionName(iniSection);
        setIniFile(&iniFile);

       	add((BaseProperty*)  &mZoom.setup( 	    	                    "ZOOM",    						0));
       	add((BaseProperty*)  &mFocus.setup( 	   	                    "FOCUS",    					0));
        return true;
    }

    bool NavitarPreset::setValue(const int& z, const int& f)
    {
    	mZoom.setValue(z);
        mFocus.setValue(f);
        return true;
    }

    bool NavitarPreset::setZoom(const int& z)
    {
    	mZoom.setValue(z);
        return true;
    }

    bool NavitarPreset::setFocus(const int& f)
    {
        mFocus.setValue(f);
        return true;
    }

}

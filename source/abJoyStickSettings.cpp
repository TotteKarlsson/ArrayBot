#pragma hdrstop
#include "abJoyStickSettings.h"
//---------------------------------------------------------------------------

JoyStickSettings::JoyStickSettings()
{
}

JoyStickSettings::~JoyStickSettings()
{}


bool JoyStickSettings::add(const JoyStickSetting& pos)
{
	//Check label
    mSettings.push_front(pos);
    return true;
}

bool JoyStickSettings::remove(const string& lbl)
{
	//Find item
    return false;
}

JoyStickSetting* JoyStickSettings::getFirst() const
{
    mSettingsIter = mSettings.begin();
    if(mSettingsIter != mSettings.end())
    {
        return &(*mSettingsIter);
    }
    return NULL;
}

JoyStickSetting* JoyStickSettings::getCurrent() const
{
    if(mSettingsIter != mSettings.end())
    {
        return &(*mSettingsIter);
    }
    return NULL;
}

JoyStickSetting* JoyStickSettings::getNext() const
{
    if(mSettingsIter != mSettings.end())
    {
        mSettingsIter++;
        if(mSettingsIter != mSettings.end())
        {
            return &(*mSettingsIter);
        }
    }
    return NULL;
}

JoyStickSetting* JoyStickSettings::getPrevious() const
{
    if(mSettingsIter != mSettings.end())
    {
        mSettingsIter--;
        if(mSettingsIter != mSettings.end())
        {
            return &(*mSettingsIter);
        }
    }
    return NULL;
}


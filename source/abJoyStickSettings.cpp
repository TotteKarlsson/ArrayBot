#pragma hdrstop
#include "abJoyStickSettings.h"
#include "mtkStringList.h"
//---------------------------------------------------------------------------
using namespace mtk;

JoyStickSettings::JoyStickSettings(const string& iniSection, IniFile& iniFile)
:
mIniSection(iniSection),
mIniFile(iniFile)
{
	IniSection* sec =  mIniFile.getSection(mIniSection, true);

    if(sec)
    {
    	IniKey* aKey = sec->getFirst();
        while(aKey)
        {
        	StringList vals(aKey->mValue,',');
        	JoyStickSetting jss(aKey->mKey, toDouble(vals[0]), toDouble(vals[1]), toDouble(vals[2]), toDouble(vals[3]));
	        add(jss);
            aKey = sec->getNext();
        }
    }
}

JoyStickSettings::~JoyStickSettings()
{
	//For each setting, create a iniKey and write to inifile
	JoyStickSetting* jss = getFirst();
	IniSection* sec =  mIniFile.getSection(mIniSection, true);
    while(jss && sec)
    {
        IniKey* key = sec->getKey(jss->getLabel(), true);
        if(key)
        {
            key->mValue = jss->asIniRecord();
        }
		jss = getNext();
    }
}


JoyStickSetting* JoyStickSettings::add(const JoyStickSetting& pos)
{
	//Check label
    mSettings.push_front(pos);

    return &(*(mSettings.begin()));
}

bool JoyStickSettings::remove(const string& lbl)
{
	//Find item
    return false;
}

JoyStickSetting* JoyStickSettings::getSetting(const string& name)
{
	JoyStickSetting* jss = getFirst();
    while(jss)
    {
        if(compareNoCase(jss->getLabel(), name))
        {
        	return jss;
        }
		jss = getNext();
    }
	return NULL;
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
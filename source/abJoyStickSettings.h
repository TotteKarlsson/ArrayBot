#ifndef abJoyStickSettingsH
#define abJoyStickSettingsH
#include "abExporter.h"
#include "abABObject.h"
#include "abJoyStickSetting.h"
#include <list>
#include "mtkINIFile.h"
//---------------------------------------------------------------------------
using std::list;
using mtk::IniFile;

typedef list<JoyStickSetting> JSSettings;

class AB_CORE JoyStickSettings : public ABObject
{
    public:
                            			JoyStickSettings(const string& iniSection, IniFile& iniFile);
                            			~JoyStickSettings();
		JoyStickSetting*				add(const JoyStickSetting& s);
        bool							remove(const string& lbl);
		JoyStickSetting*				getSetting(const string& name);
        JoyStickSetting*        		getFirst() const;
        JoyStickSetting*                getNext() const;
        JoyStickSetting*                getPrevious() const;
        JoyStickSetting*                getCurrent() const;
        bool							readINIParameters();
        bool							writeINIParameters();

    protected:
		string							mIniSection;
        IniFile&						mIniFile;
		mutable JSSettings   			mSettings;
    	mutable JSSettings::iterator 	mSettingsIter;
};
#endif

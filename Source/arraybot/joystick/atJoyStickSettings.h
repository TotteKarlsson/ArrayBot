#ifndef atJoyStickSettingsH
#define atJoyStickSettingsH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "atJoyStickSetting.h"
#include <list>
#include "dslINIFile.h"
//---------------------------------------------------------------------------
using std::list;
using dsl::IniFile;

namespace at
{
    typedef list<JoyStickSetting> JSSettings;

    class AT_AB JoyStickSettings : public ATObject
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
}
#endif

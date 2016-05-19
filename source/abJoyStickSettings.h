#ifndef abJoyStickSettingsH
#define abJoyStickSettingsH
#include "abExporter.h"
#include "abABObject.h"
#include "abJoyStickSetting.h"
#include <list>
//---------------------------------------------------------------------------
using std::list;

typedef list<JoyStickSetting> JSSettings;

class AB_CORE JoyStickSettings : public ABObject
{
    public:
                            			JoyStickSettings();
                            			~JoyStickSettings();
		bool							add(const JoyStickSetting& s);
        bool							remove(const string& lbl);
        JoyStickSetting*        		getFirst() const;
        JoyStickSetting*                getNext() const;
        JoyStickSetting*                getPrevious() const;
        JoyStickSetting*                getCurrent() const;

    protected:

		mutable JSSettings   			mSettings;
    	mutable JSSettings::iterator 	mSettingsIter;



};
#endif

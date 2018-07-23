#ifndef atNavitarPresetH
#define atNavitarPresetH
#include "atATObject.h"
#include "atNavitarZoomPreset.h"
#include "atNavitarFocusPreset.h"
#include "atNavitarMotorController.h"
#include "dslINIFileProperties.h"
//---------------------------------------------------------------------------

using dsl::ObjectType;
using dsl::IniFile;
using dsl::IniFileProperties;

namespace at
{
    class AT_NAVITAR NavitarPreset	: public IniFileProperties
    {
        public:
    		                                        NavitarPreset(NavitarMotorController& mc, const string& name, const int& z = 0, const int& f = 0);
            				                        ~NavitarPreset();
    		string									getName();
    		bool									setName(const string& n);
    		bool									setup(const string& iniSection, IniFile& iniFile);

    		bool	 								set();
            bool									setZoom(const int& z);
            bool									setFocus(const int& f);
            bool									setValue(const int& z, const int& f);

            int										getFocusPreset();
            int										getZoomPreset();


        protected:
        	string									mName;
    		NavitarMotorController&					mController;
            NavitarZoomPreset						mZoom;
            NavitarFocusPreset						mFocus;

    };
}
#endif

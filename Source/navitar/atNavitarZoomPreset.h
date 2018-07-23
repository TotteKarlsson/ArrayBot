#ifndef atNavitarZoomPresetH
#define atNavitarZoomPresetH
#include "atATObject.h"
#include "atPreset.h"
#include "atNavitarMotorController.h"
//---------------------------------------------------------------------------

using dsl::ObjectType;
using dsl::IniFile;

namespace at
{
    class AT_NAVITAR NavitarZoomPreset	: public Preset<int>
    {
        public:
    		                                        NavitarZoomPreset(NavitarMotorController& mc, const string& name, const int& z = 0);
            				                        ~NavitarZoomPreset();
    		bool	 								set();

        protected:
    		NavitarMotorController&					mController;


    };
}

#endif

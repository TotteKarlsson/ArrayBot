#ifndef abPairedMoveH
#define abPairedMoveH
#include "abExporter.h"
#include "abABObject.h"
#include "mtkINIFileProperties.h"
//---------------------------------------------------------------------------
using mtk::Property;
using mtk::IniFileProperties;
using mtk::IniFile;

class AB_CORE CombinedMove : public ABObject
{
    public:
                                        CombinedMove(const string& name);
                                        ~CombinedMove();

        Property<double>		        mVerticalDistance;
        Property<double>		        mVerticalVelocity;
        Property<double>		        mVerticalAcceleration;
        Property<double>		        mAngle;
		double					        getHorizontalDistance();
        double					        getHorizontalAcceleration();
		void 					        calculate();
        bool					        readProperties(IniFile& i);
        bool					        writeProperties();

    protected:
		double					        mHorizontalDistance;
        double					        mHorizontalVelocity;
        double					        mHorizontalAcceleration;

    private:
        IniFileProperties	   	        mProperties;
};

#endif


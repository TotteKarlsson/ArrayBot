#ifndef atMotorWigglerH
#define atMotorWigglerH
#include "atABObject.h"
#include "mtkProperty.h"
#include "mtkTimer.h"
//---------------------------------------------------------------------------

using mtk::Property;
using mtk::Timer;
class APTMotor;

typedef void (__closure *OnTimer)();

class MotorWiggler : public ABObject
{
	public:
    							MotorWiggler(APTMotor* xmtr, APTMotor* ymtr);
    							~MotorWiggler();
		void					assignMotors(APTMotor* xmtr, APTMotor* ymtr);
        bool					isRunning(){return mTimer.isRunning();}

		bool					startWiggle();
		bool					stopWiggle();
        bool					pull(double distance);
        bool					relax(double distance);
		bool					setCenterPosition(double pos){mCenterPosition = pos; return true;}
		double  				getCenterPosition(){return mCenterPosition;}

        bool					setAmplitude(double a){mAmplitude.setValue(a); return true;}
        bool					setMaxAcceleration(double a){mMaxAcceleration.setValue(a);return true;}
        bool					setMaxVelocity(double v){mMaxVelocity.setValue(v);return true;}


    	mtk::Property<double> 	mMaxVelocity;
        Property<double>		mMaxAcceleration;
        Property<double>		mAmplitude;

	protected:
    	Timer    				mTimer;
        APTMotor*				mXMotor;
        APTMotor*				mYMotor;
        double					mCenterPosition;
        double					mCurrentPosition;
        double					mNextPosition;
        bool					goToNextPosition();
        void					onTimer();
};

#endif

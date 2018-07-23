#ifndef atMotorWigglerH
#define atMotorWigglerH
#include "atATObject.h"
#include "dslProperty.h"
#include "dslTimer.h"
#include "arraybot/atABExporter.h"
//---------------------------------------------------------------------------

using dsl::Property;
using dsl::Timer;
typedef void (__closure *OnTimer)();

namespace at
{
    class APTMotor;
    class AT_AB MotorWiggler : public ATObject
    {
    	public:
        							MotorWiggler(APTMotor* xmtr = NULL, APTMotor* ymtr = NULL);
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

            bool					setPullRelaxAcceleration(double a){mMaxAcceleration.setValue(a);return true;}
            bool					setPullRelaxVelocity(double v){mMaxVelocity.setValue(v);return true;}

        	Property<double> 		mMaxVelocity;
            Property<double>		mMaxAcceleration;
            Property<double>		mAmplitude;

          	Property<double> 		mPullRelaxVelocity;
            Property<double>		mPullRelaxAcceleration;


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
}

#endif

#ifndef abRibbonLifterH
#define abRibbonLifterH
#include "abExporter.h"
#include "abABObject.h"
#include "mtkProperty.h"
#include "mtkIniFile.h"
#include "abArrayBot.h"
#include "mtkINIFileProperties.h"
#include "abCombinedMove.h"

//---------------------------------------------------------------------------
//!The ribbon lifter class encapsulates data and logic for
//!moving a ribbon from an inital pickup location (unknown) to a lifting
//!position (SLP). As the ribbon is placed onto the CS at the
//!lifting position, the process continues with a coordinated lift
//!At one point, the whisker unit is accelerated 'away' and stowed out of
//!position, allowing the coverslip to be fully lifted out of the boat

using mtk::Property;
using mtk::IniFile;
using mtk::IniSection;
using mtk::IniFileProperties;

typedef void (__closure *RibbonLifterOnTimer)();

class AB_CORE RibbonLifter : public ABObject
{
    public:
							        RibbonLifter(ArrayBot& ab, IniFile& ini);
				       		 		~RibbonLifter();

		bool						setupMove1();
		bool						executeMove1();

        bool						start();
        bool						stop();
        bool						isRunning();

									//!Lifting of a ribbon requires many
                                    //parameters
    	Property<double>			mLiftLocationX;
    	Property<double>			mLiftLocationY;
       	Property<double>			mLiftDistanceCS;

       	Property<double>			mMoveToLLVelocity;
       	Property<double>			mMoveToLLAcc;

       	Property<double>			mLiftVelocityZ;
       	Property<double>			mLiftAccZ;


       	Property<double>			mLiftVelocityY;
       	Property<double>			mLiftAccY;

		Property<double>			mWhiskerLiftOffZPosition;
        Property<double>			mWhiskerLiftStowXPosition;


    protected:
		IniFile&					mIniFile;

        							//!Container for all properties
        IniFileProperties 			mProperties;
        ArrayBot&					mArrayBot;
        ProcessSequence				mLiftSequence;
		ProcessSequencer			mSequencer;

		void						onTimer();

        							//!The process timer will check for
                                    //!motor position etc, as the
                                    //!lifter is working
        Timer						mProcessTimer;
		CombinedMove				mMove1;

};
#endif

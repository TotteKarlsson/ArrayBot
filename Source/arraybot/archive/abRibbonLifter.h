#ifndef atRibbonLifterH
#define atRibbonLifterH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include "dslProperty.h"
#include "dslIniFile.h"
#include "atArrayBot.h"
#include "dslINIFileProperties.h"
#include "atParallelProcess.h"

//---------------------------------------------------------------------------
//!The ribbon lifter class encapsulates data and logic for
//!moving a ribbon from an inital pickup location (unknown) to a lifting
//!position (SLP). As the ribbon is placed onto the CS at the
//!lifting position, the process continues with a coordinated lift
//!At one point, the whisker unit is accelerated 'away' and stowed out of
//!position, allowing the coverslip to be fully lifted out of the boat
using dsl::Property;
using dsl::IniFile;
using dsl::IniSection;
using dsl::IniFileProperties;

//typedef void (__closure *RibbonLifterOnTimer)();

class AT_AB RibbonLifter : public ATObject
{
    public:
							            RibbonLifter(ArrayBot& ab, IniFile& ini);
				       		 		    ~RibbonLifter();

		bool						    setupMove1();
		bool						    executeMove1();

		bool						    setupMove2();
		bool						    executeMove2();

        bool						    start();
        bool						    stop();
        bool						    isRunning();

									    //!Lifting of a ribbon requires many
                                        //parameters
       	Property<double>			    mLiftDistanceCS;

        								//!The lift location is where the whisker will
                                        //!move the ribbon to at move 1
    	Property<double>			    mLiftLocationX;
    	Property<double>			    mLiftLocationY;

        								//!The velocity used for which the move to the lift location is carried out
       	Property<double>			    mMoveToLLVelocity;

        								//!The acceleration used for which the move to the lift location is carried out
       	Property<double>			    mMoveToLLAcc;

       	Property<double>			    mLiftVelocityZ;
       	Property<double>			    mLiftAccZ;

       	Property<double>			    mLiftVelocityY;
       	Property<double>			    mLiftAccY;

		Property<double>			    mWhiskerLiftOffZPosition;
        Property<double>			    mWhiskerLiftStowXPosition;

    protected:
		IniFile&					    mIniFile;

        							    //!Container for all properties
        IniFileProperties 			    mProperties;
        ArrayBot&					    mArrayBot;
        ProcessSequence				    mLiftSequence;
		ProcessSequencer			    mSequencer;

		void						    onTimer();

        							    //!The process timer will check for
                                        //!motor position etc, as the
                                        //!lifter is working
        Timer						    mProcessTimer;
		ParallelProcess		 	    mMove1;
		ParallelProcess		 	    mMove2;

};
#endif

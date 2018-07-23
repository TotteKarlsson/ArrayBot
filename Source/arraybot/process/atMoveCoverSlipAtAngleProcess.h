#ifndef atMoveCoverSlipAtAngleProcessH
#define atMoveCoverSlipAtAngleProcessH
#include "atProcess.h"
#include "atABExporter.h"
#include "dslXMLUtils.h"
//---------------------------------------------------------------------------

using dsl::XMLElement;

namespace at
{

    //!A LiftAtAngle process is a process combining up to 4 motors to move
    //!the coverslip and the whisker at a predefined angle.
    //!The MoveCoverSlipAtAngleProcess do allow the user to program the whisker to
    //!stay by the beach, allowing inspection, monitoring ribbon as it gets lifted
    //!out of the water
    class APTMotor;
    class AT_AB MoveCoverSlipAtAngleProcess : public Process
    {
        public:
            	   			                            MoveCoverSlipAtAngleProcess(const string& lbl);
        	virtual			                            ~MoveCoverSlipAtAngleProcess(){}
            bool										calculateLift(ArrayBot& ab);
            											//Virtuals
    		virtual void		   		                init(ArrayBot& ab);

            virtual bool	       		                start();
            virtual bool	                        	stop();
            virtual bool	                        	isBeingProcessed();
            bool 						            	isProcessed();
            bool						            	resume();
            virtual	bool	                            undo();
            bool 						            	isDone();
    		virtual bool 			  					write();

    		const string 				                getTypeName() const;
    	    virtual dsl::XMLElement*                    addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);

            void										setLiftVelocity(double l);
            double										getLiftVelocity();

            void										setLiftAcceleration(double l);
            double										getLiftAcceleration();

            void										setLiftAngle(double l);
            double										getLiftAngle();

            void										setLiftHeight(double l);
            double										getLiftHeight();

            void										setYMoveScaling(double l);
            double										getYMoveScaling();

            double										getLateralVelocity(){return mLateralVelocity;}
            double										getLateralAcceleration(){return mLateralAcceleration;}
            bool										getMoveWhiskerInParallel(){return mMoveWhiskerInParallel;}
            bool										setMoveWhiskerInParallel(bool doIt){mMoveWhiskerInParallel = doIt; return true;}

    		bool        								setFetchAngleFromCSAngleMotor(bool doIt){mFetchAngleFromCSAngleMotor = doIt; return true;}
    		bool        								getFetchAngleFromCSAngleMotor(){return mFetchAngleFromCSAngleMotor;}
            bool										assignMotors(APTMotor* csz, APTMotor* csy, APTMotor* wz, APTMotor* wy);

    													//Leave whisker by beach parameters..
    		bool        								setLeaveWhiskerByBeach(bool doIt){mLeaveWhiskerByBeach = doIt; return true;}
            bool										getLeaveWhiskerByBeach(){return mLeaveWhiskerByBeach;}

    		bool        								setLWBBDeltaZ(double dz){mLWBBDeltaZ = dz; return true;}
            double										getLWBBDeltaZ(){return mLWBBDeltaZ;}

    		bool        								setLWBB_Z_Move(double dz){mLWBB_Z_Move = dz; return true;}
            double										getLWBB_Z_Move(){return mLWBB_Z_Move;}

    		bool        								setLWBB_Y_Move(double ym){mLWBB_Y_Move = ym; return true;}
    		double										getLWBB_Y_Move(){return mLWBB_Y_Move;}

            bool										populateFromXML(XMLElement* element);

        protected:
        	APTMotor* 									mCSZMtr;
        	APTMotor* 									mCSYMtr;
        	APTMotor* 									mWHZMtr;
        	APTMotor* 									mWHYMtr;
            bool										mIsWhiskerLogicDone;
    		bool										mMoveWhiskerInParallel;

            											//!Flag indicating if the whisker is to be left by the beach
                                                        //!LWBB is an abbreviation for Leave Whisker By Beach
            bool										mLeaveWhiskerByBeach;

            											//!If mWhiskerStayAtBeach is true, the DeltaZ parameter is used
                                                        //! to determine when the whisker-stay-at-beach mechanism is to be initiated
            double										mLWBBDeltaZ;

            											//!Start Z position for the whisker
            double										mStartWhiskerZ;
            double										mLWBB_Y_Move;
            double										mLWBB_Z_Move;

            											//!Populate angle from current angle motor position?
    		bool										mFetchAngleFromCSAngleMotor;

            double										mLiftVelocity;
            double										mLiftAcceleration;
            double										mLiftAngle;
            double										mLiftHeight;
            double										mLateralVelocity;
            double										mLateralAcceleration;
            double										mYMoveScaling;

            											//!This is the initial z value
                                                        //!Process is done when current Z =< ZStart - mLiftHeight
            double										mTargetCSZ;
            double										mTargetCSY;
            double										mTargetCSZR;
            double										mTargetCSYR;

            double										mTargetWHZ;
            double										mTargetWHY;
            double										mTargetWHZR;
            double										mTargetWHYR;
            double										getCurrentCoverSlipZ();
    };

}

#endif

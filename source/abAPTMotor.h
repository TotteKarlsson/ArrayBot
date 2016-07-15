#ifndef abAPTMotorH
#define abAPTMotorH
#include "abAPTDevice.h"
#include "mtkTimer.h"
#include "abDataStructures.h"
#include "abMotorMessageProcessor.h"
#include "abMotorMessageContainer.h"
#include "mtkRange.h"
//---------------------------------------------------------------------------

class AB_CORE APTMotor : public APTDevice
{
    public:
						                    APTMotor(int serial);
		virtual			                    ~APTMotor();


        double								getMaxPosition();
		bool 	   							switchDirection(bool inThread = true);
		bool	                    		setVelocityForward(double v);
		bool	                    		setVelocityReverse(double v);


        									//!MoveAbsolute takes a position and a velocity parameters
        bool		                		moveAbsolute(double position, double v, double a = 0);

											//!Motor ranges
        virtual Range<double>               getVelocityRange();
		virtual bool	                    setVelocityRange(DoubleRange vr);

        virtual bool		                moveRelative(double position, bool inThread = true);
        virtual bool						setJogMoveParameters(double v, double a);
        MotorCommandEnum					getLastCommand();

        double								getManualJogVelocity();
        double								getManualJogAcceleration();
        void								setManualJogVelocity(double v);
        void								setManualJogAcceleration(double a);

        virtual double	    				getPotentiometerVelocity();

        bool								isMotorCommandPending();
        bool								isAtDesiredPosition();
        double								getDesiredPosition(){return mDesiredPosition;}

        virtual bool	                    connect() = 0;
        virtual bool	                    disconnect() = 0;

        virtual bool	                    enable() = 0;
        virtual bool	                    disable() = 0;

        virtual HardwareInformation 	    getHWInfo() = 0;
        virtual double						getEncoderCounts() = 0;

		virtual bool   		                isActive() = 0;
        virtual bool		                isHomed() = 0;
        virtual bool		                isHoming() = 0;
        virtual bool		                isForwarding() = 0;
        virtual bool		                isReversing() = 0;
        virtual bool		                isEnabled() = 0;

        virtual bool	                    startPolling() = 0;
        virtual bool	                    stopPolling() = 0;



						                    //!General commands
        virtual bool		                identify() = 0;
        virtual double	                    getPosition() = 0;


        virtual double	                    getVelocity() = 0;
        virtual bool	                    setVelocity(double vel, double a = 0, bool inThread = true) = 0;

        virtual double                      getAcceleration() = 0;
        virtual bool                        setAcceleration(double val) = 0;
		virtual unsigned long 	            getStatusBits() = 0;

						                    ///Control commands
		virtual void 		                home() = 0;
        virtual void 		                stop(bool inThread = true) = 0;
        virtual void 		                stopProfiled(bool inThread = true) = 0;

        									///Jogging
		virtual bool	     				setJogMoveMode(JogMoveMode mode) = 0;
		virtual bool	     				setJogStopMode(StopMode stopMode = smProfiled) = 0;
		virtual JogMoveMode	     			getJogMoveMode() = 0;
		virtual StopMode     				getJogStopMode() = 0;

        virtual double	                	getJogVelocity() = 0;
        virtual double	          			getJogAcceleration() = 0;

        virtual void		                jogForward(bool inThread = true) = 0;
        virtual void		                jogReverse(bool inThread = true) = 0;
        virtual bool	                    setJogVelocity(double v) = 0;
        virtual bool	                    setJogAcceleration(double a) = 0;


        virtual void		                forward(bool inThread = true) = 0;
        virtual void		                reverse(bool inThread = true) = 0;
        virtual bool		                moveToPosition(double position, bool inThread = true) = 0;
        virtual void						setPotentiometerVelocity(double v) = 0;

    protected:
    										//!Motor commands are processed in a thread by the
                                            //MotorMessage processer
		double								mDesiredPosition;
       	int									mMotorCommandsPending;
    	Timer				                mStatusTimer;
        unsigned long			            mStatusBits;
        MotorScalingFactors		            mScalingFactors;
		HardwareInformation 	  			mHWInfo;
        bool								applyProperties();

        Property< Range<double> > 			mPositionRange;
        Range<double> 						mVelocityRange;
        Range<double> 						mAccelerationRange;
        Property<double>					mManualJogVelocity;
        Property<double>					mManualJogAcceleration;

        Property<double>					mPotentiometerVelocity;

		void                                post(const MotorCommand& cmd);
        MotorMessageProcessor				mMotorMessageProcessor;
        MotorMessageContainer  				mMotorMessageContainer;
};

#endif

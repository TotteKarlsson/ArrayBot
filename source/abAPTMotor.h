#ifndef abAPTMotorH
#define abAPTMotorH
#include "abAPTDevice.h"
#include "mtkTimer.h"
#include "abDataStructures.h"
#include "abMotorMessageProcessor.h"
#include "abMotorMessageContainer.h"

//---------------------------------------------------------------------------

class AB_CORE APTMotor : public APTDevice
{
    public:
						                    APTMotor(int serial);
		virtual			                    ~APTMotor();
        virtual HardwareInformation     	getHWInfo() = 0;

        virtual double						getEncoderCounts() = 0;

		virtual bool   		                isActive() 	= 0;
        virtual bool		                isHomed() 	= 0;
        virtual bool		                isHoming() 	= 0;
        virtual bool		                isForwarding() 	= 0;
        virtual bool		                isReversing() 	= 0;
		virtual bool 	   					switchDirection() = 0;
        virtual bool	                    connect() = 0;
        virtual bool	                    disconnect() = 0;

        virtual bool	                    startPolling() = 0;
        virtual bool	                    stopPolling() = 0;

						                    //!General commands
        virtual double	                    getPosition() = 0;

        virtual double	                    getVelocity() = 0;
        virtual bool	                    setMaxVelocity(double vel) = 0;
		virtual bool	                    setMaxVelocityForward(double v) = 0;
		virtual bool	                    setMaxVelocityReverse(double v) = 0;

        virtual double                      getAcceleration() = 0;
        virtual bool                        setAcceleration(double val) = 0;
		virtual unsigned long 	            getStatusBits() = 0;

						                    ///Control commands
		virtual void 		                home() = 0;
        virtual void 		                stop() = 0;
        virtual void 		                stopProfiled() = 0;

        									///Jogging
		virtual bool	     				setJogMode(JogModes mode = jmSingleStep, StopModes stopMode = smProfiled) = 0;
        virtual double	                	getJogVelocity() = 0;
        virtual double	          			getJogAcceleration() = 0;

        virtual void		                jogForward() = 0;
        virtual bool	                    setJogVelocity(double v) = 0;
        virtual bool	                    setJogAcceleration(double a) = 0;
        virtual void		                jogReverse() = 0;

        virtual void		                forward() = 0;
        virtual void		                reverse() = 0;
        virtual void		                moveDistance(double distance) = 0;

        virtual bool		                identify() = 0;

    protected:
    	Timer				                mStatusTimer;
        unsigned long			            mStatusBits;
        ScalingFactors			            mScalingFactors;
		HardwareInformation 				mHWInfo;

		void                                post(const MotorCommand& cmd);
        MotorMessageProcessor				mMotorMessageProcessor;
        MotorMessageContainer  				mMotorMessageContainer;

};


#endif

#ifndef abTCubeStepperMotorH
#define abTCubeStepperMotorH
#include "abAPTMotor.h"
//#include "Thorlabs.MotionControl.TCube.StepperMotor.h"
//---------------------------------------------------------------------------

class AB_CORE TCubeStepperMotor : public APTMotor
{
    public:
        						        TCubeStepperMotor(int serial);
		virtual 		                ~TCubeStepperMotor();

		HardwareInformation		        getHWInfo();
        double				 			getEncoderCounts();
		bool							switchDirection();

        						        ///isActive checks if the device is active.
		bool					        isActive();
		bool					        isHoming();
		bool					        isHomed();
        bool		                	isForwarding();
        bool		                	isReversing();
        bool	                        connect();
        bool	                        disconnect();

        bool	                        startPolling();
        bool	                        stopPolling();

				                        //!General commands
        double	                        getPosition();
        double	        		        getVelocity();
		bool	                    	setMaxVelocity(double v);
		bool	                    	setMaxVelocityForward(double v);
		bool	                    	setMaxVelocityReverse(double v);

        double          		        getAcceleration();
		bool	                    	setAcceleration(double a);
        unsigned long	                getStatusBits();

				                        ///Control commands
		void 		                    home();
        void 		                    stop();
        void 		                    stopProfiled();

										///Jogging
        double	                		getJogVelocity();
        double	                		getJogAcceleration();

        void		                    jogForward();
        void		                    jogReverse();
        bool	                		setJogMode(JogModes mode = jmSingleStep, StopModes stopMode = smProfiled);
        bool	                		setJogVelocity(double v);
        bool	                		setJogAcceleration(double a);

        void		                    forward();
        void		                    reverse();
        void		                    moveDistance(double distance);

        bool		                    identify();

    protected:

};
#endif

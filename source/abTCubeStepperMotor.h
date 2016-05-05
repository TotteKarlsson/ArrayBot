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
        bool	                        connect();
        bool	                        disconnect();
        bool	                        startPolling();
        bool	                        stopPolling();

        						        ///Status functions
		bool					        isActive();
		bool					        isHoming();
		bool					        isHomed();
        bool		                	isForwarding();
        bool		                	isReversing();
		bool							switchDirection(bool inThread = true);

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

        void 		                    stop(bool inThread = true);
        void 		                    stopProfiled(bool inThread = true);

										///Jogging
        double	                		getJogVelocity();
        double	                		getJogAcceleration();

        void		                    jogForward(bool inThread = true);
        void		                    jogReverse(bool inThread = true);
        bool	                		setJogMode(JogModes mode = jmSingleStep, StopModes stopMode = smProfiled);
        bool	                		setJogVelocity(double v);
        bool	                		setJogAcceleration(double a);

        void		                    forward(bool inThread = true);
        void		                    reverse(bool inThread = true);
        void		                    moveDistance(double distance, bool inThread = true);

        bool		                    identify();

    protected:
//        void		                    jogForward();
//        void		                    jogReverse();

};
#endif

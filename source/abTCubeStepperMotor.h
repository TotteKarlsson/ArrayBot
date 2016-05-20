#ifndef abTCubeStepperMotorH
#define abTCubeStepperMotorH
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

class AB_CORE TCubeStepperMotor : public APTMotor
{
    public:
        						        TCubeStepperMotor(int serial);
		virtual 		                ~TCubeStepperMotor();

		HardwareInformation	    		getHWInfo();
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

				                        //!General commands
        double	                        getPosition();
        double	        		        getVelocity();
		bool	                    	setVelocity(double v);
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
        bool	                		setJogMoveMode(JogMoveMode mode);
        bool	                		setJogStopMode(StopMode mode);

        JogMoveMode	                   	getJogMoveMode();
		StopMode 						getJogStopMode();

        bool	                		setJogVelocity(double v);
        bool	                		setJogAcceleration(double a);

        void		                    forward(bool inThread = true);
        void		                    reverse(bool inThread = true);
        bool		                	moveAbsolute(double position, bool inThread = true);
        bool		                    identify();
        void							setPotentiometerVelocity(double v);

    protected:

};
#endif

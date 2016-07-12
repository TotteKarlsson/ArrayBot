#ifndef abTCubeDCServoH
#define abTCubeDCServoH
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

class AB_CORE TCubeDCServo : public APTMotor
{
    public:
        						        TCubeDCServo(int serial);
		virtual 		                ~TCubeDCServo();

        bool	                        connect();
        bool	                        disconnect();
        bool	                        enable();
        bool	                        disable();

				                        ///Control commands
		void 		                    home();

		HardwareInformation		        getHWInfo();
        double				 			getEncoderCounts();

        						        ///isActive checks if the device is active.
		bool					        isActive();
		bool					        isHoming();
		bool					        isHomed();
        bool		                	isForwarding();
        bool		                	isReversing();
        bool		                	isEnabled();

        bool	                        startPolling();
        bool	                        stopPolling();

				                        //!General commands
        bool		                    identify();
        double	                        getPosition();
        double	        		        getVelocity();

		bool	                    	setVelocity(double v, double a = 0, bool inThread = true);

        double          		        getAcceleration();
		bool	                    	setAcceleration(double a);
        unsigned long	                getStatusBits();

        void 		                    stop(bool inThread = true);
        void 		                    stopProfiled(bool inThread = true);

										///Jogging
        bool	                		setJogVelocity(double v);
        bool	                		setMaxJogVelocity(double v);
        bool	                		setJogAcceleration(double a);

        double	                		getJogVelocity();
        double	                		getJogAcceleration();

        void		                    jogForward(bool inThread = true);
        void		                    jogReverse(bool inThread = true);

        bool	                		setJogMoveMode(JogMoveMode mode);
        bool	                		setJogStopMode(StopMode mode);

        JogMoveMode	                	getJogMoveMode();
  		StopMode 						getJogStopMode();

        void		                    forward(bool inThread = true);
        void		                    reverse(bool inThread = true);
        bool		                	moveAbsolute(double position, bool inThread = true);
        void							setPotentiometerVelocity(double v);

    protected:


};
#endif

#ifndef abTCubeDCServoH
#define abTCubeDCServoH
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

class AB_CORE TCubeDCServo : public APTMotor
{
    public:
        						        TCubeDCServo(int serial);
		virtual 		                ~TCubeDCServo();

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
        void		                    jogForward();
        void		                    jogReverse();
        void		                    forward();
        void		                    reverse();
        void		                    moveDistance(double distance);

        bool		                    identify();

    protected:

};
#endif

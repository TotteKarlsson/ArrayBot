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
		bool							switchDirection(bool inThread = true);

				                        //!General commands
        double	                        getPosition();
        double	        		        getVelocity();
//        double	        		        getMaxVelocity();
		bool	                    	setVelocity(double v);
		bool	                    	setVelocityForward(double v);
		bool	                    	setVelocityReverse(double v);

        double          		        getAcceleration();
//        double          		        getMaxAcceleration();

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

//        bool	                		setMaxJogVelocity(double v);
//        bool	                		setMaxJogAcceleration(double a);
//        double	        	        	getMaxJogVelocity();
//        double	    	      			getMaxJogAcceleration();

        void		                    forward(bool inThread = true);
        void		                    reverse(bool inThread = true);
        void		                	moveToPosition(double position, bool inThread = true);
        bool		                    identify();

    protected:
//        void		                    jogForward();
//        void		                    jogReverse();

};
#endif

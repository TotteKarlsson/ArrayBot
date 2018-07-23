#ifndef atTCubeStepperMotorH
#define atTCubeStepperMotorH
#include "atAPTMotor.h"
//---------------------------------------------------------------------------

namespace at
{
    class AT_AB TCubeStepperMotor : public APTMotor
    {
        public:
            						        TCubeStepperMotor(int serial);
    		virtual 		                ~TCubeStepperMotor();

            bool	                        connect();
            bool	                        disconnect();
            bool	                        enable();
            bool	                        disable();

    		HardwareInformation	    		getHWInfo();
            double				 			getEncoderCounts();

            bool	                        startPolling();
            bool	                        stopPolling();

            						        ///Status functions
    		bool					        isActive();
    		bool					        isHoming();
    		bool					        isHomed();
            bool		                	isForwarding();
            bool		                	isReversing();
    		bool 							isEnabled();

    				                        //!General commands


            double	                        getPosition() const;
            double	        		        getVelocity();
    		bool	                    	setVelocityParameters(double v, double a = 0, bool inThread = true);
    	    double          		        getAcceleration();

            unsigned long	                getStatusBits();

    				                        ///Control commands
    		void 		                    home(bool inThread = true);

            void 		                    stop(bool inThread = true);
            void 		                    stopProfiled(bool inThread = true);

    										///Jogging
            double              	        getJogStep();
            bool	         	            setJogStep(double step);
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
            bool		                	moveToPosition(double position, bool inThread = true);
            bool		                    identify();
            void							setPotentiometerVelocity(double v);

        protected:

	};
}
#endif

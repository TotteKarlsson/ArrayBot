#ifndef abLongTravelStageH
#define abLongTravelStageH
#include "abAPTMotor.h"
//---------------------------------------------------------------------------

class AB_CORE LongTravelStage : public APTMotor
{
    public:
        						        LongTravelStage(int serial);
		virtual 		                ~LongTravelStage();

		HardwareInformation		        getHWInfo();
        double				 			getEncoderCounts();


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
        bool		                    identify();
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

		bool							switchDirection(bool inThread = true);
        void 		                    stop(bool inThread = true);
        void 		                    stopProfiled(bool inThread = true);

										///Jogging
        double	                		getJogVelocity();
        double	                		getJogAcceleration();

        void		                    jogForward(bool inThread = true);
        void		                    jogReverse(bool inThread = true);

        bool	                		setJogMoveMode(JogMoveMode mode);
        bool	                		setJogStopMode(StopMode mode);

        JogMoveMode	                		getJogMoveMode();
		StopMode 						getJogStopMode();

        bool	                		setJogVelocity(double v);
        bool	                		setJogAcceleration(double a);

        void		                    forward(bool inThread = true);
        void		                    reverse(bool inThread = true);
        void		                    moveDistance(double distance, bool inThread = true);

    protected:

};
#endif

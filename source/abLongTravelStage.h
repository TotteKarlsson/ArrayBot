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

		bool	                    	setVelocity(double v);
		bool	                    	setVelocityForward(double v);
		bool	                    	setVelocityReverse(double v);

        double          		        getAcceleration();
		bool	                    	setAcceleration(double a);
        unsigned long	                getStatusBits();

				                        ///Control commands
		void 		                    home();

		bool							switchDirection(bool inThread = true);
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
        void		                    moveDistance(double distance, bool inThread = true);

    protected:

};
#endif

#ifndef atAPTMotorH
#define atAPTMotorH
#include "atAPTDevice.h"
#include "dslTimer.h"
#include "arraybot/atDataStructures.h"
#include "atMotorMessageProcessor.h"
#include "atMotorMessageContainer.h"
#include "dslRange.h"
#include "atMotorMessageData.h"
//---------------------------------------------------------------------------


class TMotorFrame;

namespace at
{
	AT_AB	string		toString(const JogMoveMode& mode);
	AT_AB	JogMoveMode	toJogMoveMode(const string& mode);

    //!An APT (Advanced Position Technology) Motor is an abstract class encaspulating properties/behaviour of a Thorlabs motor
    //The Thorlabs C API does unfortuntaly not allow a proper abstraction, meaning a lot of repetion of code in descendant
    //classes :(
    class AT_AB APTMotor : public APTDevice
    {
    	friend class TMotorFrame;
        public:
    						                    APTMotor(int serial);
    		virtual			                    ~APTMotor();
            double								getMinPosition();
            double								getMaxPosition();
    		bool 	   							switchDirection(bool inThread = true);
    		bool	                    		setVelocityForward(double v);
    		bool	                    		setVelocityReverse(double v);

            int									getNumberOfQueuedCommands();
            bool								isInDangerZone();

            									//!MoveAbsolute takes a position and velocity parameters
            bool		                		moveAbsolute(double position, double v, double a = 0);

    											//!Motor ranges
            virtual Range<double>               getVelocityRange();
    		virtual bool	                    setVelocityRange(DoubleRange vr);

            virtual bool		                moveRelative(double distance, bool inThread = true);
            virtual bool						setJogMoveParameters(double v, double a);
            MotorCommandEnum					getLastCommand();

            double								getManualJogVelocity();
            double								getManualJogAcceleration();
            void								setManualJogVelocity(double v);
            void								setManualJogAcceleration(double a);

            virtual double	    				getPotentiometerVelocity();

            bool								isMotorCommandPending();
            bool								isAtDesiredPosition();
            double								getDesiredPosition(){return mDesiredPosition;}

            virtual bool	                    connect() = 0;
            virtual bool	                    disconnect() = 0;

            virtual bool	                    enable() = 0;
            virtual bool	                    disable() = 0;

            virtual HardwareInformation 	    getHWInfo() = 0;
            virtual double						getEncoderCounts() = 0;

    		virtual bool   		                isActive() = 0;
            virtual bool		                isHomed() = 0;
            virtual bool		                isHoming() = 0;
            virtual bool		                isForwarding() = 0;
            virtual bool		                isReversing() = 0;
            virtual bool		                isEnabled() = 0;

            virtual bool	                    startPolling() = 0;
            virtual bool	                    stopPolling() = 0;


    						                    //!General commands
            virtual bool		                identify() = 0;
            virtual double	                    getPosition() const = 0;

            virtual double	                    getVelocity() = 0;
            virtual bool	                    setVelocityParameters(double vel, double a = 0, bool inThread = true) = 0;

            virtual double                      getAcceleration() = 0;
    		virtual unsigned long 	            getStatusBits() = 0;

    						                    ///Control commands
    		virtual void 		                home(bool inThread = true) = 0;
            virtual void 		                stop(bool inThread = true) = 0;
            virtual void 		                stopProfiled(bool inThread = true) = 0;

            									///Jogging
    		virtual bool	     				setJogMoveMode(JogMoveMode mode) = 0;
    		virtual bool	     				setJogStopMode(StopMode stopMode = smProfiled) = 0;
    		virtual JogMoveMode	     			getJogMoveMode() = 0;
    		virtual StopMode     				getJogStopMode() = 0;

            virtual double	                	getJogVelocity() = 0;
            virtual double	          			getJogAcceleration() = 0;

            virtual void		                jogForward(bool inThread = true) = 0;
            virtual void		                jogReverse(bool inThread = true) = 0;

            virtual double                      getJogStep() = 0;
            virtual bool	                    setJogStep(double step) = 0;
            virtual bool	                    setJogVelocity(double v) = 0;
            virtual bool	                    setJogAcceleration(double a) = 0;

            virtual void		                forward(bool inThread = true) = 0;
            virtual void		                reverse(bool inThread = true) = 0;
            virtual bool		                moveToPosition(double position, bool inThread = true) = 0;
            virtual void						setPotentiometerVelocity(double v) = 0;

        protected:
        										//!Motor commands are processed in a thread by the
                                                //MotorMessage processer
    		double								mDesiredPosition;
           	int									mMotorCommandsPending;

    											//!The status time checks a motors position
                                                //!If the position gets close to its limits,
                                                //!a message is sent to the main application to
                                                //!let it know. The UI may respond with stopping the motor
                                                //!after an alarm is sounded
        	Timer				                mStatusTimer;
            void								onStatusTimer();


            unsigned long			            mStatusBits;
            MotorScalingFactors		            mScalingFactors;
    		HardwareInformation 	  			mHWInfo;
            bool								applyProperties();

            									//!The position range is the physical position range
                                                //a motor has.
            Property< Range<double> > 			mPositionRange;

    										    //!Position limits may be used to limit a motors range of motion
            Property< Range<double> > 			mPositionLimits;

            									//!The alarm zone allow an application to warn
                                                //!the user before a motor hit a preset positional limit
                                                //The warning zone starts at 10% of full distance by default
    		Property< double >					mWarningZone;

            									//!To be able to move a motor that crossed the limits, disable
                                                //!usage of limits by setting mPositionLimitsEnabled to false
            Property< bool > 					mPositionLimitsEnabled;

            Range<double> 						mVelocityRange;
            Range<double> 						mAccelerationRange;

            Property<double>					mManualJogVelocity;
            Property<double>					mManualJogAcceleration;
            Property<double>					mPotentiometerVelocity;
            Property<double>					mJogStep;
            Property<JogMoveMode>   			mJogMoveMode;

    		void                                post(const MotorCommand& cmd);
            MotorMessageProcessor				mMotorMessageProcessor;
            MotorMessageContainer  				mMotorMessageContainer;

            void								populateMotorMessageData(MotorMessageData* data);
    };

    double getMotorPosition(APTMotor* m);


}
using at::JogMoveMode;
//Enable JogMoveMode property
template<>
inline Property<JogMoveMode>::operator JogMoveMode() const
{
    return (*mValue);
}

//---------------------------------------------------------------------------
template<> inline
std::string Property< JogMoveMode >::getValueAsString() const
{
    return dsl::toString(getValue());
}

template<> inline
bool Property< JogMoveMode >::write(IniFile* iniFile, const string& section)
{
    if(iniFile == NULL)
    {
        return false;
    }

    string toWrite;
    toWrite = dsl::toString(getValue());
    iniFile->writeString(mKey, toWrite, "", section);
    return true;
}

template<> inline
bool Property< JogMoveMode >::read(IniFile* iniFile, const string& section)
{
    if(iniFile == NULL)
    {
        return false;
    }

    string val = iniFile->readString(mKey, section, "");
    JogMoveMode tempVal;

    {
    	tempVal = JogMoveMode(at::toJogMoveMode(val));
    }

    mWasRead = iniFile->wasItFound();
    setValue( mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

template<> inline
bool Property< JogMoveMode >::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property< JogMoveMode >::getTypeName() const
{
    return "jogMoveMode";
}

#endif

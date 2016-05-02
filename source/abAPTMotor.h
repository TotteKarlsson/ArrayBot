#ifndef abAPTMotorH
#define abAPTMotorH
#include "abAPTDevice.h"
#include "mtkTimer.h"
//---------------------------------------------------------------------------

//!Scaling factors are used to convert a motors position, velocity and accelertation
//!expressed in device units, into world physical units.
struct ScalingFactors
{
	double position;
    double velocity;
    double acceleration;
};

struct HardwareInformation
{
	/// <summary> Structure containing the Hardware Information. </summary>
    /// <summary> The device serial number. </summary>
    /// <remarks> The device serial number is a serial number,<br />starting with 2 digits representing the device type<br /> and a 6 digit unique value.</remarks>
    DWORD serialNumber;
    /// <summary> The device model number. </summary>
    /// <remarks> The model number uniquely identifies the device type as a string. </remarks>
    string modelNumber;
    /// <summary> The device type. </summary>
    /// <remarks> Each device type has a unique Type ID: see \ref C_DEVICEID_page "Device serial numbers" </remarks>
    WORD type;
    /// <summary> The number of channels the device provides. </summary>
    short numChannels;
    /// <summary> The device notes read from the device. </summary>
    string notes;
    /// <summary> The device firmware version. </summary>
    DWORD firmwareVersion;
    /// <summary> The device hardware version. </summary>
    WORD hardwareVersion;
    /// <summary> The device dependant data. </summary>
    BYTE deviceDependantData[12];
    /// <summary> The device modification state. </summary>
    WORD modificationState;
};

class AB_CORE APTMotor : public APTDevice
{
    public:
						                    APTMotor(int serial);
		virtual			                    ~APTMotor();
        virtual HardwareInformation     	getHWInfo() = 0;

        virtual double						getEncoderCounts() = 0;

		virtual bool   		                isActive() 	= 0;
        virtual bool		                isHomed() 	= 0;
        virtual bool		                isHoming() 	= 0;
        virtual bool		                isForwarding() 	= 0;
        virtual bool		                isReversing() 	= 0;
		virtual bool 	   					switchDirection() = 0;
        virtual bool	                    connect() = 0;
        virtual bool	                    disconnect() = 0;

        virtual bool	                    startPolling() = 0;
        virtual bool	                    stopPolling() = 0;

						                    //!General commands
        virtual double	                    getPosition() = 0;
        virtual double	                    getVelocity() = 0;
        virtual bool	                    setMaxVelocity(double vel) = 0;

        virtual double                      getAcceleration() = 0;
        virtual bool                        setAcceleration(double val) = 0;
		virtual unsigned long 	            getStatusBits() = 0;

						                    ///Control commands
		virtual void 		                home() = 0;
        virtual void 		                stop() = 0;
        virtual void 		                stopProfiled() = 0;
        virtual void		                jogForward() = 0;
        virtual void		                jogReverse() = 0;
        virtual void		                forward() = 0;
        virtual void		                reverse() = 0;
        virtual void		                moveDistance(double distance) = 0;

        virtual bool		                identify() = 0;

    protected:
    	Timer				                mStatusTimer;
        unsigned long			            mStatusBits;
        ScalingFactors			            mScalingFactors;
		HardwareInformation 				mHWInfo;

};


#endif

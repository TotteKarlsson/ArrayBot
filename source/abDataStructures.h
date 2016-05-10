#ifndef abDataStructuresH
#define abDataStructuresH

//!Scaling factors are used to convert a motors position, velocity and accelertation
//!expressed in device units, into world physical units.
struct MotorScalingFactors : public ABObject
{
	double position;
    double velocity;
    double acceleration;
};

struct HardwareInformation : public ABObject
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

/// <summary> Values that represent the motor Jog Modes. </summary>
enum JogMoveMode : short
{
	jmJogModeUndefined = 0x00,///<Undefined
	jmContinuous = 0x01,///<Continuous jogging
	jmSingleStep = 0x02,///<Jog 1 step at a time
};

/// <summary> Values that represent the motor Stop Modes. </summary>
enum StopMode : short
{
	smStopModeUndefined = 0x00,///<Undefined
	smImmediate = 0x01,///<Stops immediate
	smProfiled = 0x02,///<Stops using a velocity profile
};



#endif

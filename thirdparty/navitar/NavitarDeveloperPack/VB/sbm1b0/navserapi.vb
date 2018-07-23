
Option Strict Off
Option Explicit On 

Imports System
Imports System.Runtime.InteropServices

Module navserapi

    ' Interface routine definitions --------------------------------------------
    Declare Auto Function SerConnectionConnect Lib "navserAPI.dll" (ByVal Port As Integer, ByVal ProductID As Integer) As Integer
    Declare Auto Function SerConnectionEstablished Lib "navserAPI.dll" (ByVal serHandle As Integer, ByVal ProductID As Integer) As Integer
    Declare Auto Function SerConnectionRead Lib "navserAPI.dll" (ByVal serHandle As Integer, ByVal reg As Byte, ByRef Value As Integer) As Integer
    Declare Auto Function SerConnectionWrite Lib "navserAPI.dll" (ByVal serHandle As Integer, ByVal reg As Byte, ByRef Value As Integer) As Integer
    Declare Auto Function SerConnectionDisconnect Lib "navserAPI.dll" (ByVal serHandle As Integer) As Integer
    Declare Auto Function SerConnectionDisconnectAll Lib "navserAPI.dll" () As Integer

    ' Controller definitions----------------------------------------------------
    Public Const DEF_BRIGHTLIGHT = &H4000
    Public Const DEF_MOTOR_CONTROLLER = &H4001

    ' Motor Controller type definitions----------------------------------------------------
    Public Const DEF_MICROMO2PHASE = &H1
    Public Const DEF_VEXTA5PHASE = &H2
    Public Const DEF_DCMOTOR = &H3


    ' Generic registers --------------------------------------------------------
    'These system registers are intended to be read only.
    'Writes to these registers will not survive a power reset.  
    Public Const REG_SYS_PRODUCTID = &H1           '   read only -> returns 0x4001
    Public Const REG_SYS_VERSIONHW = &H2           '   read only 
    Public Const REG_SYS_VERSIONDATE = &H3         '   read only 
    Public Const REG_SYS_VERSIONSW = &H4           '   read only

    Public Const REG_SYS_PRODUCTID_SUBCLASS = &H5  '   read only, motor controller type
    '				1 or 0xffffffd9)	2 phase stepper
    '				2)			5 phase vexta
    '				3)			DC encoder


    ' Bright light register definitions ----------------------------------------

    Public Const REG_PWM_ABSOLUTE = &H40      '		read/write
    ' This value is in 0.1 increments
    ' 0    –> 0%
    ' 1000 -> 100%

    Public Const REG_PWM_INCREMENT = &H41  '		write
    ' +/- change to current PWM value
    ' This value is in 0.1 increments
    ' 10   -> 1%
    ' -10  -> -1%


    ' Motor controller definintions ---------------------------------------------

    'These system registers are intended to be system setup registers.
    'Changing these may result in a system that does not perform properly.

    Public Const REG_SETUP_ACCEL_1 = &H15      '   sets motor 1 acceleration
    Public Const REG_SETUP_ACCEL_2 = &H25  '   sets motor 2 acceleration

    Public Const REG_SETUP_INITVELOCITY_1 = &H16 '   sets initial motor 1 velocity
    Public Const REG_SETUP_INITVELOCITY_2 = &H26 '   sets initial motor 2 velocity

    Public Const REG_SETUP_MAXVELOCITY_1 = &H17    '   	sets maximum motor 1 velocity
    Public Const REG_SETUP_MAXVELOCITY_2 = &H27    '	sets maximum motor 2 velocity

    Public Const REG_SETUP_REVBACKLASH_1 = &H18    '	sets motor 1 reverse backlash value
    Public Const REG_SETUP_REVBACKLASH_2 = &H28 '   sets motor 2 reverse backlash value

    Public Const REG_SETUP_FWDBACKLASH_1 = &H19    '	sets motor 1 forward backlash value
    Public Const REG_SETUP_FWDBACKLASH_2 = &H29 '   sets motor 2 forward backlash value

    Public Const REG_SETUP_CONFIG_1 = &H1B       '	sets motor 1 sensor configuration
    Public Const REG_SETUP_CONFIG_2 = &H2B    '   sets motor 2 sensor configuration

    '			Bit 0:	0 – near sensor is home
    '					1 – far sensor is home
    '			Bit 1:	0 – reverse seek direct
    '					1 – reverse seek thru home
    '			Bit 2:	0 – Axis 2 enabled(only for AXIS 2)
    '					1 – Axis 2 Disabled(only for AXIS 2)

    Public Const REG_SETUP_LIMIT_1 = &H1C     '   returns motor 1 limit value
    Public Const REG_SETUP_LIMIT_2 = &H2C     '   returns motor 2 limit value

    Public Const REG_SETUP_WRITE = &HE               '	writes all the above changes to the EEROM. The value passed in the write must be 1.


    'These user registers are intended for normal operation

    Public Const REG_USER_TARGET_1 = &H10        '	motor 1 seek command
    Public Const REG_USER_TARGET_2 = &H20      '   motor 2 seek command

    Public Const REG_USER_INCREMENT_1 = &H11    '   motor 1 delta seek from current
    Public Const REG_USER_INCREMENT_2 = &H21     '   motor 2 delta seek from current

    Public Const REG_USER_CURRENT_1 = &H12       '	motor 1 current position
    Public Const REG_USER_CURRENT_2 = &H22     '   motor 2 current position

    Public Const REG_USER_LIMIT_1 = &H13        '	motor 1 limit seek command
    Public Const REG_USER_LIMIT_2 = &H23      '   motor 2 limit seek command

    '		The value written drives the motor to one of the limits:
    '			0 – home motor
    '			1 – limit motor
    '			2 – aborts any current motor motion.

    Public Const REG_USER_STATUS_1 = &H14
    Public Const REG_USER_STATUS_2 = &H24

    '		Lower 8 bits (Bit 0 thru 7).
    '			0 – idle
    '			1 – driving to home
    '			2 – coming off home
    '			3 – driving to limit
    '			4 – seeking forward
    '			5 – deaccel in forward direction
    '			6 – forward backlash (i.e. rev after overshoot)
    '			7 – seeking reverse
    '			8 – deaccel in reverse direction
    '			9 – reverse backlash (i.e. forward after overshoot)
    '			11- forward deaccel during an abort
    '			12- reverse deaccel during an abort
    '
    '		Bit 8 – motor on home sensor
    '		Bit 9 – motor on limit sensor


End Module

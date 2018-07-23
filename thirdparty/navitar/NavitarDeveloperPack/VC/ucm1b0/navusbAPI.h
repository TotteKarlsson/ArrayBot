
#ifdef NAVITAR_DLL
#define NAVITAR_USB_API __declspec(dllexport)
#else
#define NAVITAR_USB_API __declspec(dllimport)
#endif

#ifndef USB_INTERFACE
	#undef NAVITAR_USB_API
	#define NAVITAR_USB_API
#endif


#ifdef __cplusplus
extern "C" {
#endif

NAVITAR_USB_API int USBFindUSBinterfaces(void);
NAVITAR_USB_API int USBConnectionConnect(int device,unsigned short ProductID);
NAVITAR_USB_API int USBConnectionConnectSpec(int device,unsigned short ProductID,unsigned short ProductType);
NAVITAR_USB_API int USBConnectionConnectIndex(int device,unsigned short ProductID);
NAVITAR_USB_API int USBConnectionEstablished(int id,unsigned short ProductID);
NAVITAR_USB_API int USBConnectionDisconnect(int id);
NAVITAR_USB_API int USBConnectionDisconnectAll(void);
NAVITAR_USB_API int USBConnectionWrite(int id,unsigned char reg,long *v);
NAVITAR_USB_API int USBConnectionRead(int id,unsigned char reg,long *v);

#ifdef __cplusplus
}
#endif



#define DEF_BRIGHTLIGHT			0x4000
#define DEF_MOTOR_CONTROLLER	0x4001

#define DEF_MICROMO2PHASE		0x0001
#define DEF_VEXTA5PHASE			0x0002
#define DEF_DCMOTOR				0x0003


#define REG_PWM_ABSOLUTE		0x40	//	read/write
// This value is in 0.1 increments
// 0    -> 0%
// 1000 -> 100%

#define REG_PWM_INCREMENT		0x41	//write
// +/- change to current PWM value
// This value is in 0.1 increments
// 10   -> 1%
// -10  -> -1%


#define REG_SYS_PRODUCTID		0x01
#define REG_SYS_VERSIONHW		0x02
#define REG_SYS_VERSIONDATE		0x03
#define REG_SYS_VERSIONSW		0x04
#define REG_SYS_PRODUCTID_SUBCLASS 0x05
                                
#define REG_FLASH				0x0D
#define REG_SETUP_WRITE			0x0E
#define REG_SYS_WRITE			0x0F

#define REG_USER_TARGET_1		0x10
#define REG_USER_TARGET_2		0x20

#define REG_USER_INCREMENT_1	0x11
#define REG_USER_INCREMENT_2	0x21

#define REG_USER_CURRENT_1		0x12
#define REG_USER_CURRENT_2		0x22


#define REG_USER_LIMIT_1		0x13
#define REG_USER_LIMIT_2		0x23 

#define REG_USER_STATUS_1		0x14
#define REG_USER_STATUS_2		0x24

#define REG_SETUP_ACCEL_1		0x15
#define REG_SETUP_ACCEL_2		0x25  

#define REG_SETUP_INITVELOCITY_1 0x16
#define REG_SETUP_INITVELOCITY_2 0x26

#define REG_SETUP_MAXVELOCITY_1	0x17
#define REG_SETUP_MAXVELOCITY_2	0x27

#define REG_SETUP_REVBACKLASH_1	0x18
#define REG_SETUP_REVBACKLASH_2	0x28

#define REG_SETUP_FWDBACKLASH_1	0x19
#define REG_SETUP_FWDBACKLASH_2	0x29

#define REG_SETUP_SENSORTYPE_1	0x1A
#define REG_SETUP_SENSORTYPE_2	0x2A

#define REG_SETUP_CONFIG_1		0x1B
#define REG_SETUP_CONFIG_2		0x2B

#define REG_SETUP_LIMIT_1		0x1C
#define REG_SETUP_LIMIT_2		0x2C



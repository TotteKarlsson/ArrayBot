#ifndef atDS457H
#define atDS457H
#include "atBarcodeReaderExporter.h"
#include "atATObject.h"
#include "../thirdparty/ssidll/SSIDLL.H"
//-------------------------------------------------------------------------

//!The DS457 is a Zebra, former Motorola barcode reader
//!Its lowlevel communication logic is encapsulated in the thirdparty atSSI DLL

//!The DS457 object will need a window handle, comport number and a baudrate to initialize properly


#define MAX_VIDEO_LEN 					5000
#define SWTRIG_PARAMNUM			        0x8a
#define HOST_SWTRIG				        0x08
#define EXTENDED_PARAMNUM		        0xf0
#define IMAGE_FILETYPE_PARAMNUM	        0x30
#define BMP_FILE_SELECTION		        0x03
#define TIFF_FILE_SELECTION		        0x04
#define JPEG_FILE_SELECTION		        0x01
#define VIDEOVIEWFINDER_PARAMNUM		0x44

#define WM_USER_GETSWTRIGPARAM 			(WM_USER + 100)
#define WM_USER_GETIMAGETYPES 			(WM_USER_GETSWTRIGPARAM + 1)
#define WM_USER_GETVIEWFINDERPARAM 		(WM_USER_GETIMAGETYPES + 1)
#define WM_SENDGETVERSIONMSG			(WM_USER_GETVIEWFINDERPARAM + 1)
#define WM_SENDGETCAPABILITIESMSG		(WM_SENDGETVERSIONMSG + 1)
#define BITMAP_TYPE				         0	// for m_ImageType
#define TIFF_TYPE				         1
#define JPEG_TYPE				         2
#define IMAGE_TYPE_UNKNOWN		         3


class AT_BCR DS457 : public at::ATObject
{
	public:
								            DS457();
                                            ~DS457();

		bool					            connect(int port, int baudRate, HWND handle = NULL);
		bool					            disconnect();
        bool								isConnected();

        bool					            scanEnable();
        bool					            scanDisable();

        bool					            startDecodeSession();
        bool					            stopDecodeSession();

		bool								beep(int b);
		bool					            aimOn();
		bool					            aimOff();
		bool					            illuminationOn();
		bool					            illuminationOff();

		bool					            LEDsOn();
		bool					            LEDsOff();

		const unsigned char*			   	getMemoryBuffer() const;

    private:
    	HWND					            mHandle;
        int						            mCOMPort;
        int						            mBaudRate;

		unsigned char 						mVideoData[MAX_VIDEO_LEN];
		unsigned char*						g_pImageData;
};

#endif

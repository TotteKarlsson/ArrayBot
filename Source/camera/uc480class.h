// usb2cameraclass.h: interface for the Cuc480 class.
// August-2016 TK modified this file, and associated files in order to incorporate camera vision to the
// ArrayBot project
//////////////////////////////////////////////////////////////////////

#ifndef uc480classH
#define uc480classH

#if _MSC_VER > 1000
 #pragma once
#endif // _MSC_VER > 1000

#include "uc480.h"
#include "uc480_deprecated.h"
#include "camera/dynamic_uc480.h"

#include "atCameraExporter.h"

enum _disp_mode
{
  e_disp_mode_bitmap = 0,
  e_disp_mode_direct3D
};

class AT_CAMERA Cuc480 : public Cuc480Dll
{
	public:
                                            Cuc480();
        virtual 							~Cuc480();
        bool								openCamera(HWND hwnd, int cameraIndex = 0);
        bool								exitCamera();

        HCAM                                GetCameraHandle(){ return m_hu; }
        HWND                                GetWindowHandle(){ return m_hwnd; }
        HWND                                GetNotifyWindowHandle(){ return m_hwndNotify; }
        BOOL                                IsInit(){ return m_hu != NULL; }
        int                                 EnableDeviceStateNotification(BOOL boEnable, HWND hwnd = NULL);

                                            // init/exit functions
        int   	                            InitCamera(int nId = 0, HWND hwnd = NULL);
        int   	                            ExitCamera();
        int   	                            SetErrorReport(int lMode);
        int   	                            GetErrorText(int lErr, char* pcErrText);

                                            // inquire functions
        int   	                            GetNumberOfCameras(int* plNumCameras);
        int   	                            GetDllVersion(int* plDllVers);
        int   	                            GetPciSlot(int* plSlot);
        int   	                            GetIRQ(int* plIRQ);
        int   	                            GetColorDepth(int* plBpp, int* plColFormat);
        int   	                            CameraStatus(int lInfo, long lValue);
        int   	                            GetCameraType();
        int   	                            GetOsVersion(void);

                                            // image parameter functions
        int   	                            SetBrightness(int lBright);
        int   	                            SetContrast(int lCont);
        int   	                            SetGamma(int lGamma);
        int   	                            SetSaturation(int lSatU, int lSatV);
        int   	                            SetHue(int lHue);
        int   	                            SetColorMode(int lMode);
        int   	                            SetWhiteBalance(int nMode );
        int   	                            SetWhiteBalanceMultipliers(double dblRed, double dblGreen, double dblBlue );

                                            // callback functions
        int   	                            InitEvent(HANDLE hEv, int nWhich);
        int   	                            EnableEvent(int nWhich);
        int   	                            ExitEvent(int nWhich);
        int   	                            DisableEvent(int nWhich);
        int   	                            EnableAutoExit(int nMode);
        int   	                            EnableMessage(int nWhich, HWND hwnd);

                                            // display functions
        int   	                            SetImageSize(int lWidth, int lHeight);
        int   	                            SetImagePos(int lPosX, int lPosY);
        int   	                            SetScrollPos(int lPosX, int lPosY);
        int   	                            SetDisplayOffset(int lOffsetX, int lOffsetY);
        int   	                            SetDisplayMode(int Mode);
        int   	                            SetDisplayWindow(HWND hWnd);
        int   	                            SetDisplayKeyColor(int lKeyCol);
        int   	                            SetMainDisplayWindow(HWND hWnd);
        int   	                            UpdateDisplay();
        int   	                            SetDisplayHook(int lMode);
        int   	                            SetScaler(int nMode);

                                            // video capture functions
        int   	                            CaptureVideo(int lWait);
        int   	                            StopLiveVideo(int lWait);
        int   	                            FreezeVideo(int lWait);
        int   	                            CaptureFrame(BITMAPINFOHEADER* pbmih, char* pcImage);
        int   	                            SetCaptureMode(int lMode);

                                            // memory handling functions
        int   	                            AllocImageMem(int lWidth, int lHeight, int lBpp, char** ppcImgMem, int* plID);
        int   	                            FreeImageMem(char* pcMem, int lID);
        int   	                            SetImageMem(char* pcMem, int lID);
        int   	                            GetActiveImageMem(char** ppcImgMem, int* plID);
        int   	                            InquireImageMem(char* pcMem, int lID, int* plX, int* plY, int* plBpp, int* plPitch);

                                            // digital I/O and trigger input functions
        int   	                            ReadTriggerPort(int* plIn);
        int   	                            ReadDigitalPort(int* plIn);
        int   	                            WriteDigitalPort(int lOut);
        int   	                            SetExternalTrigger(int lMode);

                                            // EEPROM access functions
        int   	                            GetCameraInfo(CAMINFO* pInfo);
        int   	                            ReadEEPROM(int lAdr, char* pcBuf, int lCount);
        int   	                            WriteEEPROM(int lAdr, char* pcBuf, int lCount);

                                            // bitmap load and save functions
        int   	                            SaveImage(const char* pcFile);
        int   	                            LoadImage(char* pcFile);
        int   	                            SaveImageMem(char* pcFile, char* pcMem, int lID);

                                            // bitmap render functions
        int   	                            RenderBitmap(int nMemID, HWND hwnd, int nMode);

                                            // timing functions
        int   	                            GetPixelClockRange( int *nMin, int *nMax );
        int   	                            SetPixelClock(int nClock);
        int   	                            SetFrameRate(double dFr, double* pdFrNew);
        int   	                            SetExposureTime(double EXP, double* newEXP );

        int   	                            Renumerate( int reserved );
        int   	                            GetSensorInfo( PSENSORINFO pInfo );
        int   	                            LoadParameters( char* pFilename);
        int   	                            DirectRenderer(UINT nMode, void* pParam, UINT nSizeOfParam);
        void  	                            GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);

        INT		                            mColorMode;		// Y8/RGB16/RGB24/RGB32
        INT		                            mBitsPerPixel;	// number of bits needed store one pixel
        INT		                            mSizeX;			// width of video
        INT		                            mSizeY;			// height of video
        char*                               mImageMemory;	// image memory - pointer to buffer
        INT                                 mMemoryId;    	// image memory - buffer ID

        _disp_mode 				            mDispModeSel;

		int 					            InitDisplayMode();

	private:
        HCAM                              	m_hu;
        HWND                              	m_hwnd;
        HWND                              	m_hwndNotify;
		SENSORINFO 							mSensorInfo;     // sensor info struct
};

#endif

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>

#define __AFXWIN_H__
#include "uc480Class.h"
#include "mtkLogFileReader.h"

enum _disp_mode
{
  e_disp_mode_bitmap = 0,
  e_disp_mode_direct3D
};


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
	__published:	// IDE-managed Components
		TPanel *Panel1;
	TButton *Button1;
	TTimer *Timer1;
	TMemo *infoMemo;
	TTimer *mShutDownTimer;
	TTrackBar *TrackBar1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall mShutDownTimerTimer(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);


    private:	// User declarations
        LogFileReader                   mLogFileReader;
        void __fastcall                 logMsg();

		Cuc480   				m_camera;
		SENSORINFO 				m_sInfo;     // sensor info struct

        // Camera varibles
        HWND	                m_hDisplay;			// handle to diplay window
        INT		                m_Ret;			// return value of SDK functions
        INT		                m_nColorMode;	// Y8/RGB16/RGB24/RGB32
        INT		                m_nBitsPerPixel;// number of bits needed store one pixel
        INT		                m_nSizeX;		// width of video
        INT		                m_nSizeY;		// height of video
        char*                   m_pcImageMemory;// image memory - pointer to buffer
        INT                     m_lMemoryId;    // image memory - buffer ID

        _disp_mode 				m_nDispModeSel;
		int 					InitDisplayMode();
        HWND 					GetSafeHwnd();

		bool					openCamera();
		void					exitCamera();



    public:		// User declarations
 			       __fastcall TForm1(TComponent* Owner);

	LRESULT 				OnUSBCameraMessage(WPARAM wParam);//, LPARAM lParam );

//        ON_WM_SYSCOMMAND()
//        ON_WM_PAINT()
//        ON_WM_QUERYDRAGICON()
//        ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
//        ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
//        ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
//        ON_MESSAGE(IS_UC480_MESSAGE, OnUSBCameraMessage)
//            MESSAGE_HANDLER(UWM_MESSAGE,        mlxStructMessage,         AppInBox);

    BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(IS_UC480_MESSAGE, unsigned int, OnUSBCameraMessage);
    END_MESSAGE_MAP(TForm)

//        ON_BN_CLICKED(IDC_BUTTON_LOAD_PARAMETER, OnBnClickedButtonLoadParameter)
//        ON_BN_CLICKED(IDC_DISP_DIB, OnBnClickedDispModeChange)
//        ON_BN_CLICKED(IDC_DISP_DD, OnBnClickedDispModeChange)

//        ON_WM_CLOSE()



};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>

#define __AFXWIN_H__
#include "camera/uc480Class.h"
#include "mtkLogFileReader.h"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
	__published:	// IDE-managed Components
	TPanel *mCameraStreamPanel;
	TButton *mCameraStartLiveBtn;
	TTimer *Timer1;
	TMemo *infoMemo;
	TTimer *mShutDownTimer;
	TTrackBar *TrackBar1;
	TButton *Button2;
	TCheckBox *mAutoGainCB;
	TPanel *Panel2;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
	TPanel *mCameraBackPanel;
	TGroupBox *GroupBox1;
	TRadioGroup *RadioGroup1;
	void __fastcall mCameraStartLiveBtnClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall mShutDownTimerTimer(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall mAutoGainCBClick(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);


    private:	// User declarations
        LogFileReader                   mLogFileReader;
        void __fastcall                 logMsg();

		Cuc480   				mCamera;


        // Camera variables
        HWND	                mDisplayHandle;	// handle to diplay window


        HWND 					GetSafeHwnd();

		bool					openCamera();

    public:		// User declarations
 			       __fastcall TMainForm(TComponent* Owner);

	LRESULT 				OnUSBCameraMessage(TMessage msg);

    BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(IS_UC480_MESSAGE, TMessage, OnUSBCameraMessage);
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

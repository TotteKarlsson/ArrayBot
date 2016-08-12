#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "TPropertyCheckBox.h"
#include <Vcl.Menus.hpp>

#include "mtkLogFileReader.h"
#include "mtkIniFileProperties.h"
#include "mtkIniFile.h"
#include "mtkLogger.h"
#include "TRegistryForm.h"
#include "camera/uc480Class.h"

#include "abArduinoClient.h"
#include "mtkFloatLabel.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ToolWin.hpp>


using Poco::Timestamp;
using mtk::IniFileProperties;
using mtk::IniFile;


class TSettingsForm;
//---------------------------------------------------------------------------
class TMainForm  : public TRegistryForm
{
	friend TSettingsForm;

	__published:	// IDE-managed Components
	TMemo *infoMemo;
	TTimer *mShutDownTimer;
	TPanel *Panel2;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
	TButton *mOneToTwoBtn;
	TButton *mOneToOneBtn;
	TButton *mFitToScreenButton;
	TPanel *mMainPanel;
	TPanel *mCameraBackPanel;
	TPanel *mCameraStreamPanel;
	TButton *mToggleLogPanelBtn;
	TButton *mRecordMovieBtn;
	TButton *mSnapShotBtn;
	TTimer *Timer1;
	TPanel *mBottomPanel;
	TPanel *Panel1;
	TListBox *mMoviesLB;
	TPopupMenu *mMediaPopup;
	TMenuItem *Delete1;
	TMenuItem *DeleteAll1;
	TListBox *mShotsLB;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TButton *Button2;
	TButton *mSettingsBtn;
	TGroupBox *GroupBox6;
	mtkFloatLabel *mHumidityE;
	TGroupBox *GroupBox5;
	mtkFloatLabel *mTemperatureLbl;
	TButton *mFrontBackLEDBtn;
	TButton *mToggleCoaxBtn;
	TGroupBox *GroupBox7;
	TTrackBar *mCoaxTB;
	TTrackBar *mBackLEDTB;
	TTrackBar *mFrontLEDTB;
	TGroupBox *GroupBox8;
	TToolBar *ToolBar1;
	TBitBtn *mClearLogMemoBtn;
	TComboBox *LogLevelCB;
	void __fastcall mCameraStartLiveBtnClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall mShutDownTimerTimer(TObject *Sender);
	void __fastcall mOneToTwoBtnClick(TObject *Sender);
	void __fastcall mOneToOneBtnClick(TObject *Sender);
	void __fastcall mFitToScreenButtonClick(TObject *Sender);
	void __fastcall mMainPanelResize(TObject *Sender);
	void __fastcall mToggleLogPanelClick(TObject *Sender);
	void __fastcall mSnapShotBtnClick(TObject *Sender);
	void __fastcall mRecordMovieBtnClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall mMoviesLBDblClick(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
	void __fastcall DeleteAll1Click(TObject *Sender);
	void __fastcall mCameraStreamPanelDblClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall mSettingsBtnClick(TObject *Sender);
	void __fastcall mFrontBackLEDBtnClick(TObject *Sender);
	void __fastcall LightTBChange(TObject *Sender);
	void __fastcall LogLevelCBChange(TObject *Sender);

    private:
        LogFileReader                           mLogFileReader;
        void __fastcall                         logMsg();


        IniFile						            mIniFile;
        IniFileProperties  			            mProperties;
		mtk::Property<mtk::LogLevel>            mLogLevel;
        mtk::Property<bool>						mAutoGain;
        mtk::Property<bool>						mAutoExposure;
        mtk::Property<bool>						mVerticalMirror;
        mtk::Property<bool>						mHorizontalMirror;

								                // Camera variables

        								        //!The camera class
		Cuc480   						        mCamera;
        long							        mRenderMode;
        HWND	                		        mDisplayHandle;	// handle to diplay window
        HWND 							        GetSafeHwnd();
		bool							        openCamera();

        								        //!Boolean to check if we are
                                                //capturing video to file
        bool							        mCaptureVideo;

        								        //!AVI ID is a handle for a
                                                //underlying avi object
		int 							        mAVIID;

        void							        updateVideoFileLB();
		void  							        updateShotsLB();

        										//!The arduino client connects to
                                                //an arduino server. The client processes
                                                //incoming messages over a socket, in
                                                //onArduinoMessageReceived
		ArduinoClient 					        mArduinoClient;

        										//Callback
		void 									onArduinoMessageReceived(const string& msg);

    public:
 			       __fastcall 					TMainForm(TComponent* Owner);
 			       __fastcall 					~TMainForm();

												//!Camera stuff is processed in the message loop
	LRESULT 									OnUSBCameraMessage(TMessage msg);

    BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(IS_UC480_MESSAGE, TMessage, OnUSBCameraMessage);
    END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif

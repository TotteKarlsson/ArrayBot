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
#include "arduino/abLightsArduinoClient.h"
#include "mtkFloatLabel.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ToolWin.hpp>
#include "TArrayBotBtn.h"
#include "sound/abSoundPlayer.h"
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include "abATDBClientDBSession.h"
#include <Vcl.Imaging.jpeg.hpp>

#include "TATDBDataModule.h"
#include "TATDBImagesAndMoviesDataModule.h"

using Poco::Timestamp;
using mtk::IniFileProperties;
using mtk::IniFile;
using mtk::Property;

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
	TPanel *mMainPanel;
	TPanel *mCameraBackPanel;
	TPanel *mCameraStreamPanel;
	TTimer *mCaptureVideoTimer;
	TPanel *mBottomPanel;
	TPanel *Panel1;
	TListBox *mMoviesLB;
	TPopupMenu *mMediaPopup;
	TMenuItem *Delete1;
	TMenuItem *DeleteAll1;
	TListBox *mShotsLB;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox6;
	mtkFloatLabel *mHumidityE;
	TGroupBox *GroupBox5;
	mtkFloatLabel *mTemperatureLbl;
	TGroupBox *GroupBox8;
	TToolBar *ToolBar1;
	TBitBtn *mClearLogMemoBtn;
	TComboBox *LogLevelCB;
	TScrollBox *ScrollBox1;
	TArrayBotButton *Button2;
	TArrayBotButton *mFitToScreenButton;
	TArrayBotButton *mFrontBackLEDBtn;
	TArrayBotButton *mOneToOneBtn;
	TArrayBotButton *mOneToTwoBtn;
	TArrayBotButton *mRecordMovieBtn;
	TArrayBotButton *mSettingsBtn;
	TArrayBotButton *mSnapShotBtn;
	TArrayBotButton *mToggleCoaxBtn;
	TArrayBotButton *mToggleLogPanelBtn;
	TGroupBox *LightIntensitiesGB;
	TTrackBar *mCoaxTB;
	TTrackBar *mBackLEDTB;
	TTrackBar *mFrontLEDTB;
	TPanel *Panel3;
	TLabel *mCoaxLbl;
	TLabel *mBackLEDLbl;
	TLabel *mFrontLEDLbl;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TDBGrid *mImagesGrid;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid2;
	TButton *mAddImageFileBtn;
	TDBMemo *DBMemo1;
	TButton *mUpdateNoteBtn;
	TButton *mNewNoteBtn;
	TButton *mDeleteNoteBtn;
	TImage *Image1;
	TGroupBox *GroupBox1;
	TPanel *Panel4;
	TComboBox *mUsersCB;
	TLabel *Label1;
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
	void __fastcall mCaptureVideoTimerTimer(TObject *Sender);
	void __fastcall ClearLogMemo(TObject *Sender);
	void __fastcall mMoviesLBDblClick(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
	void __fastcall DeleteAll1Click(TObject *Sender);
	void __fastcall mCameraStreamPanelDblClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall mSettingsBtnClick(TObject *Sender);
	void __fastcall mFrontBackLEDBtnClick(TObject *Sender);
	void __fastcall LogLevelCBChange(TObject *Sender);
	void __fastcall mAddImageFileBtnClick(TObject *Sender);
	void __fastcall IntensityChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DBMemo1Change(TObject *Sender);
	void __fastcall mUpdateNoteBtnClick(TObject *Sender);
	void __fastcall DBNavigator2Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall DBNavigator2BeforeAction(TObject *Sender, TNavigateBtn Button);
	void __fastcall mNewNoteBtnClick(TObject *Sender);
	void __fastcall DBMemo1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mImagesGridMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall mImagesGridCellClick(TColumn *Column);
	void __fastcall mImagesGridDblClick(TObject *Sender);



    private:
        LogFileReader                           mLogFileReader;

        void __fastcall                         logMsg();

		ATDBClientDBSession						mClientDBSession;
        IniFile						            mIniFile;
        IniFileProperties  			            mProperties;
		Property<mtk::LogLevel>            		mLogLevel;
        Property<bool>						    mAutoGain;
        Property<bool>						    mAutoExposure;
        Property<bool>						    mVerticalMirror;
        Property<bool>						    mHorizontalMirror;
        Property<bool>						    mPairLEDs;
        Property<string>						mSnapShotFolder;
        Property<string>						mMoviesFolder;
        Property<string>						mLocalDBFile;

								                // Camera variables
        								        //!The camera class
		Cuc480   						        mCamera;
        long							        mRenderMode;
        HWND	                		        mDisplayHandle;	// handle to diplay window
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
		LightsArduinoClient    			        mLightsArduinoClient;

        										//Callbacks
        void									onArduinoClientConnected();
        void									onArduinoClientDisconnected();

        										//Callback
		void 									onArduinoMessageReceived(const string& msg);
        void									enableDisableClientControls(bool enable);
		void    								populateUsers();

    public:
 			       __fastcall 					TMainForm(TComponent* Owner);
 			       __fastcall 					~TMainForm();

		SoundPlayer								mGetReadyForZeroCutSound;
        SoundPlayer								mSetZeroCutSound;
        SoundPlayer								mRestoreFromZeroCutSound;
        void									stopSounds();

												//!Camera stuff is processed in the message loop
	LRESULT 									OnUSBCameraMessage(TMessage msg);

    BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(IS_UC480_MESSAGE, TMessage, OnUSBCameraMessage);
    END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif

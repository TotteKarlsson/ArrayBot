#ifndef MainFormH
#define MainFormH
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "arraybot/apt/atDeviceManager.h"
#include "dslIniFileProperties.h"
#include "dslTLogMemoFrame.h"
#include "dslTRegistryForm.h"
#include "frames/TMotorFrame.h"

using dsl::IniFileProperties;

//---------------------------------------------------------------------------
class TMain : public TRegistryForm
{
    __published:	// IDE-managed Components
        TActionList *ActionList1;
        TAction *checkForDevices;
        TAction *addDevicesToListBox;
        TTimer *ShutDownTimer;
        TAction *identifyCurrent;
        TAction *homeDevice;
        TAction *jogForward;
        TAction *jogBackwards;
        TAction *moveForward;
        TAction *moveBackward;
        TAction *stopAllA;
        TButton *Button7;
		TAction *initBotA;
        TAction *ShutDownA;
	    TPanel *Btnpanel;
	    TButton *Button5;
	    TFileExit *FileExit1;
	    TPanel *TopPanel;
	    TPageControl *PageControl1;
	    TTabSheet *TabSheet4;
	    TScrollBox *ScrollBox1;
	    TSplitter *Splitter1;
	    TPanel *MainPanel;
	    TLogMemoFrame *TLogMemoFrame1;
		TButton *Button1;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall checkForDevicesExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall ShutDownTimerTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
		void __fastcall FormShow(TObject *Sender);

    private:
        IniFileProperties  			        mProperties;
        IniFile						        mIniFile;
	    DeviceManager 						mDeviceManager;

		void __fastcall		                OnException();
		bool 						        createMotorFrame(APTMotor* mtr);
//		 void __fastcall 					WndProc(TMessage& Message);

	public:
		__fastcall 					        TMain(TComponent* Owner);
		__fastcall 					        ~TMain();
//		void __fastcall                     AppInBox(TMessage& Msg);
//
//        BEGIN_MESSAGE_MAP
//
//        END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMain *Main;
#endif

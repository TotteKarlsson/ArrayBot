#ifndef TWatchDogServerFrameH
#define TWatchDogServerFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include "core/WatchDogServer.h"
#include "EnvironmentalSensorReadThread.h"
#include "SNMPWalkThread.h"
#include "dslTIntegerLabeledEdit.h"
//---------------------------------------------------------------------------


class TWatchDogSensorFrame;

class TWatchDogServerFrame : public TFrame
{
	friend WatchDogServer;
    __published:	// IDE-managed Components
		TSTDStringLabeledEdit *ServerIPE;
        TGroupBox *GroupBox1;
		TArrayBotButton *WalkBtn;
		TArrayBotButton *ReadSensorsBtn;
		TArrayBotButton *StartReadsBtn;
		TTimer *EnvSensorsReadsTimer;
		TIntegerLabeledEdit *PeriodicReadE;
		TScrollBox *SensorPanel;
		void __fastcall WalkBtnClick(TObject *Sender);
		void __fastcall ReadSensorsBtnClick(TObject *Sender);
		void __fastcall EnvSensorsReadsTimerTimer(TObject *Sender);
		void __fastcall StartReadsBtnClick(TObject *Sender);

    private:
    	WatchDogServer*						mWatchDogServer;
	    EnvironmentalSensorReadThread		mReadSensorsThread;
	    SNMPWalkThread						mSNMPWalkThread;
		vector<TWatchDogSensorFrame*>		mSensorFrames;
        void __fastcall						onSensorReadStart(int, int);
        void __fastcall						onSensorReadProgress(int, int);
        void __fastcall						onSensorReadExit(int, int);
        string								mEnvSensorDataString;
		void __fastcall						consumeEnvironmentSensorData();

    public:
        __fastcall 			                TWatchDogServerFrame(TComponent* Owner);
        void				                assignWatchDogServer(WatchDogServer* s);
        void				                allocateSensorFrames();
        bool								canClose();
        void								shutDown();
};

extern PACKAGE TWatchDogServerFrame *WatchDogServerFrame;
#endif

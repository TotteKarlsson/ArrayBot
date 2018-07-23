#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTPluginManager.h"
#include "dslTLogFileReader.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslTLogFileReader.h"
#include "dslTPluginManager.h"
#include "dslTAboutFrame.h"
#include "dslTPluginInfoFrame.h"
#include "PythonPlugins/dslPythonPluginManager.h"
//---------------------------------------------------------------------------

using dsl::TPluginInfoFrame;
typedef void (*PluginEvent)(void* data1, void* data2);

void                        onPluginStarted(void* a, void* b);
void                        onPluginRunning(void* a, void* b);
void                        onPluginExit(void* a, void* b);

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
    __published:	// IDE-managed Components
        TMemo *Memo1;
        TLogFileReader *LogFileReader1;
		TTimer *ShutDownTimer;
		TPluginManager *PluginManager1;
		TPanel *Panel1;
		TControlBar *ControlBar1;
		TPanel *Panel2;
		TPanel *Panel3;
		TButton *ExecuteBtn;
	TButton *LoadPluginsBtn;
	TButton *GetPluginsInfoBtn;
	TGroupBox *PythonGB;
	TListBox *PluginsLB;
        void __fastcall LoadPluginsBtnClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
		void __fastcall ShutDownTimerTimer(TObject *Sender);
		void __fastcall PluginsLBClick(TObject *Sender);
		void __fastcall ExecuteBtnClick(TObject *Sender);
	void __fastcall PythonPluginsLBClick(TObject *Sender);

    private:
        TPluginInfoFrame*   		PluginInfoFrame;
		Plugin*						getSelectedPlugin();
        dsl::PythonPluginManager    mPythonPM;
        void       					loadPlugins();
        void     					loadPythonPlugins();

    public:
        				__fastcall 	TMainForm(TComponent* Owner);
        				__fastcall 	~TMainForm();
};

extern PACKAGE TMainForm *MainForm;
#endif

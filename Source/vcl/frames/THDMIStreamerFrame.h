#ifndef THDMIStreamerFrameH
#define THDMIStreamerFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TArrayBotBtn.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTPropertyCheckBox.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "atHDMIStreamerProcess.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------

class PACKAGE THDMIStreamerFrame : public TFrame
{
    __published:
	TGroupBox *SettingsGB;
        TIntegerLabeledEdit *BitrateE;
	TSTDStringLabeledEdit *OutputFileFolderE;
	TSTDStringLabeledEdit *OutputFileNameE;
	TTimer *CheckStatus;
	TArrayBotButton *StartRecordingBtn;
	void __fastcall StartStreamerBtnClick(TObject *Sender);

    private:
		HDMIStreamerProcess			   	mStreamer;
  	    void 				            onEnter(int i, int j);
	    void 				            onProgress(int i, int j);
	    void 				            onExit(int i, int j);

        								//!Typically block ID
        string							mPathPostFix;

    public:
        		__fastcall 				THDMIStreamerFrame(TComponent* Owner);
        		__fastcall 				~THDMIStreamerFrame();
		bool							isStreamerAlive();
        void							setPathPostFix(const string& f);
		bool							shutDownStreamer();
        void							enableSettings();
        void							disableSettings();
		HDMIStreamerProcess&			getStreamer();

};

extern PACKAGE THDMIStreamerFrame *HDMIStreamerFrame;
#endif

#ifndef TFFMPEGFrameH
#define TFFMPEGFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "dslTPropertyCheckBox.h"
#include "dslIniFileProperties.h"
#include "dslTPropertyCheckBox.h"
//---------------------------------------------------------------------------

using dsl::IniFileProperties;
using dsl::IniFile;

class PACKAGE TFFMPEGFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TIntegerLabeledEdit *FFMPEGThreads;
	TIntegerLabeledEdit *CRFValue;
	TComboBox *PresetCB;
	TLabel *Label1;
	TPropertyCheckBox *DeleteSourceFileCB;
	TPropertyCheckBox *RenameSourceFileCB;
	void __fastcall CBClick(TObject *Sender);


	private:
        IniFileProperties 	 	mFrameProperties;
        Property<string>		mH264Preset;

	public:
		__fastcall 		        TFFMPEGFrame(TComponent* Owner);
        string 			        getOutFileArguments();
        string 			        getInFileArguments();
		void 					setupProperties(dsl::IniFile& ini);
        void			        readFromINI();
        void			        writeToINI();

};

extern PACKAGE TFFMPEGFrame *FFMPEGFrame;
#endif

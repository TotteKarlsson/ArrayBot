#ifndef TATDBConnectionFrameH
#define TATDBConnectionFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TSTDStringLabeledEdit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslIniFile.h"
#include "dslIniFileProperties.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "TArrayBotBtn.h"
//---------------------------------------------------------------------------

using dsl::IniFile;
using dsl::IniFileProperties;
class PACKAGE TATDBConnectionFrame : public TFrame
{
    __published:	// IDE-managed Components
		TGroupBox *GBox1;
        TSTDStringLabeledEdit *mServerIPE;
        TSTDStringLabeledEdit *mDBUserE;
        TSTDStringLabeledEdit *mPasswordE;
        TSTDStringLabeledEdit *mDatabaseE;
		TActionList *ActionList1;
		TAction *ConnectA;
		TArrayBotButton *ArrayBotButton1;
		void __fastcall ConnectAExecute(TObject *Sender);

    private:
		IniFile*				mIniFile;
		IniFileProperties       mProperties;

    public:
                __fastcall 		TATDBConnectionFrame(TComponent* Owner);
    	bool					init(IniFile* inifile, const string& iniFileSection);
    	bool					writeParameters();
        void					afterConnect();
        void					afterDisconnect();
};

extern PACKAGE TATDBConnectionFrame *ATDBConnectionFrame;
#endif

#ifndef TPGConnectionFrameH
#define TPGConnectionFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslIniFile.h"
#include "dslIniFileProperties.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "TArrayBotBtn.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Data.DB.hpp>
#include <Data.SqlExpr.hpp>
#include "database/atDBCredentials.h"

//---------------------------------------------------------------------------

using dsl::IniFile;
using dsl::IniFileProperties;

class PACKAGE TPGConnectionFrame : public TFrame
{
    __published:	// IDE-managed Components
		TGroupBox *GBox1;
        TSTDStringLabeledEdit *mServerIPE;
        TSTDStringLabeledEdit *mDBUserE;
        TSTDStringLabeledEdit *mPasswordE;
        TSTDStringLabeledEdit *mDatabaseE;
		TActionList *PGConnectionsActions;
		TAction *ConnectA;
		TArrayBotButton *ArrayBotButton1;
		void __fastcall ConnectAExecute(TObject *Sender);
		void __fastcall GBox1Click(TObject *Sender);

    private:
		IniFile*				mIniFile;
        TSQLConnection*         mDBConnection;
		IniFileProperties       mProperties;
        void					updateUI();

    public:
                __fastcall 		TPGConnectionFrame(TComponent* Owner);
    	bool					init(IniFile* inifile, const string& iniFileSection, TSQLConnection* dbConnection);
        DBCredentials			getCredentials();
    	bool					writeParameters();
        void					afterConnect();
        void					afterDisconnect();
};

extern PACKAGE TPGConnectionFrame *PGConnectionFrame;
#endif

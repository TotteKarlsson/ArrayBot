#ifndef TSSHFrameH
#define TSSHFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "ScBridge.hpp"
#include "ScSSHChannel.hpp"
#include "ScSSHClient.hpp"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------

class PACKAGE TSSHFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TButton *ConnectBtn;
	TScFileStorage *ScFileStorage;
	TScSSHShell *ScSSHShell1;
	TScSSHChannel *ScSSHChannel;
	TScSSHClient *ScSSHClient;
	TSTDStringLabeledEdit *edSSHHost;
	TIntegerLabeledEdit *seSSHPort;
	TSTDStringLabeledEdit *edSSHUserName;
	TSTDStringLabeledEdit *edSSHPassword;
	void __fastcall ScSSHClientAfterConnect(TObject *Sender);
	void __fastcall ScSSHClientServerKeyValidate(TObject *Sender, TScKey *NewServerKey,
          bool &Accept);
	void __fastcall ScSSHClientAfterDisconnect(TObject *Sender);
	void __fastcall ScSSHClientBeforeConnect(TObject *Sender);
	void __fastcall ConnectBtnClick(TObject *Sender);
	void __fastcall ScSSHShell1AsyncError(TObject *Sender, Exception *E);
private:	// User declarations

        bool 				FRandomized;
        void 				SaveState();
        void 				LoadState();
        String 				KeyPath();


public:		// User declarations
				__fastcall  TSSHFrame(TComponent* Owner);
        bool				isConnected();
        void				disconnect();

};
//---------------------------------------------------------------------------
extern PACKAGE TSSHFrame *SSHFrame;
//---------------------------------------------------------------------------
#endif

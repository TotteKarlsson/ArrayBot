//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Joystick.hpp"
//---------------------------------------------------------------------------
class TMain : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TPanel *Panel2;
	TMemo *infoMemo;
	TGroupBox *GroupBox3;
	TActionList *ActionList1;
	TAction *initializeCoverSlipPosition;
	TAction *initializeAll;
	TAction *initializeWhiskerPosition;
	TAction *stowCoverSlip;
	TAction *stowWhisker;
	TButton *Button5;
	TButton *Button6;
	TAction *stowAll;
	TAction *systemCheck;
	TButton *Button7;
	TGroupBox *GroupBox4;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	void __fastcall Joystick1Move(TObject *Sender, TButtons Pressed, int X, int Y);

private:	// User declarations
public:		// User declarations
	__fastcall TMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
#ifndef MAINFORMH
#define MAINFORMH
//---------------------------------------------------------------------------
#include <system.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.StdCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <vcl.Controls.hpp>
#include <vcl.StdCtrls.hpp>
#include <vcl.Forms.hpp>
#include <vcl.ExtCtrls.hpp>
#include <mmsystem.h>
#include <deque>
//---------------------------------------------------------------------------
using std::deque;

class TForm1 : public TForm
{
	__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *JoystickCount;
        TLabel *JoysticksConnected;
        TLabel *CurrentJoystick;
        TLabel *JoystickMid;
        TLabel *JoystickPid;
        TLabel *JoystickXMin;
        TLabel *JoystickXMax;
        TLabel *JoystickYMin;
        TLabel *JoystickYMax;
        TLabel *JoystickNumButtons;
        TLabel *JoystickName;
        TLabel *JoystickMinPoll;
        TLabel *JoystickMaxPoll;
        TLabel *Label2;
        TLabel *JoystickXPosition;
        TLabel *JoystickYPosition;
        TLabel *JoystickButton1;
        TLabel *JoystickButton2;
        TLabel *JoystickButton3;
        TLabel *JoystickButton4;
        TImageList *ImageList1;
        TTimer *Timer1;
        TLabel *JoystickZPosition;
        TPanel *TargetPanel;
        TChart *Chart1;
        TFastLineSeries *Series1;
	TTimer *Timer2;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TMemo *infoMemo;
	TLabel *JoystickButton5;
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


	private:	// User declarations
        TPoint Position;
        int DriverCount;
        bool Connected;
        int JoystickID;
        JOYCAPS JoyCaps;
        int YDivider;
        int XDivider;
        void ShowDeviceInfo(void);
        void ShowStatusInfo(void);
        void __fastcall JMButtonUpdate(TMessage &msg);
        void __fastcall JMMove(TMessage &msg);
        void __fastcall JMZMove(TMessage &msg);

	public:							// User declarations
  		__fastcall 					TForm1(TComponent* Owner);

        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(MM_JOY1BUTTONDOWN,TMessage,		JMButtonUpdate)
          MESSAGE_HANDLER(MM_JOY1BUTTONUP,	TMessage,		JMButtonUpdate)
          MESSAGE_HANDLER(JOY_BUTTON1CHG,	TMessage,		JMButtonUpdate)

          MESSAGE_HANDLER(MM_JOY2BUTTONDOWN,TMessage,		JMButtonUpdate)
          MESSAGE_HANDLER(MM_JOY2BUTTONUP,	TMessage,		JMButtonUpdate)

          MESSAGE_HANDLER(MM_JOY1MOVE,		TMessage,       JMMove)
          MESSAGE_HANDLER(MM_JOY2MOVE,		TMessage,       JMMove)

          MESSAGE_HANDLER(MM_JOY1ZMOVE,		TMessage,		JMZMove)
//          MESSAGE_HANDLER(MM_JOY2ZMOVE +1,	TMessage,		JMZMove)
        END_MESSAGE_MAP(TForm)

		deque<double>			mXPos;
		deque<double>			mYPos;
		deque<double>			mZPos;

};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

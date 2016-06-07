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
#include "TFloatLabeledEdit.h"
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
        TImageList *ImageList1;
        TTimer *Timer1;
        TChart *Chart1;
        TFastLineSeries *Series1;
	TTimer *Timer2;
	TLabel *JoystickZPosition;
	TFastLineSeries *Series2;
	TLabel *JoystickAvgZPos;
	TMemo *Memo1;
	TFloatLabeledEdit *mAlpha;
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
        double mRunningZAverage;
//        double mAlpha;

        void ShowDeviceInfo(void);
        void ShowStatusInfo(void);
        void __fastcall JMZMove(TMessage &msg);

	public:							// User declarations
  		__fastcall 					TForm1(TComponent* Owner);

        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(MM_JOY1ZMOVE,TMessage,JMZMove)
        END_MESSAGE_MAP(TForm)

		deque<double>			mZPos;
		deque<double>			mZAvgPos;
        double 					mValCommand;

};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

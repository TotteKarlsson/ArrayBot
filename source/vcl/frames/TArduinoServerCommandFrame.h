#ifndef TArduinoServerCommandFrameH
#define TArduinoServerCommandFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "TSTDStringLabeledEdit.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------

class ArduinoServerCommand;
class ArrayBot;


class PACKAGE TArduinoServerCommandFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *mMainGB;
	TLabel *Label1;
	TLabel *mActionInfo;
	TPanel *Panel2;
	TComboBox *mCommandCB;
	void __fastcall mActionInfoClick(TObject *Sender);

    private:	// User declarations
        ArduinoServerCommand* 		mProcess;
        ArrayBot*					mAB;

    public:		// User declarations
                        __fastcall TArduinoServerCommandFrame(TComponent* Owner);
        void            		   populate(ArrayBot* ab, ArduinoServerCommand* m);
        void            		   rePopulate(ArduinoServerCommand* m);
};

extern PACKAGE TArduinoServerCommandFrame *ArduinoServerCommandFrame;
#endif

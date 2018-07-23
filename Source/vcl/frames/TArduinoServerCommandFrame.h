#ifndef TArduinoServerCommandFrameH
#define TArduinoServerCommandFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTFloatLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------

namespace at
{
class ArduinoServerCommand;
class ArrayBot;
}
using at::ArrayBot;
using at::ArduinoServerCommand;


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
        ArrayBot&					mAB;

    public:		// User declarations
                        __fastcall TArduinoServerCommandFrame(ArrayBot& ab, TComponent* Owner);
        void            		   populate(ArduinoServerCommand* m);
        void            		   rePopulate(ArduinoServerCommand* m);
};

extern PACKAGE TArduinoServerCommandFrame *ArduinoServerCommandFrame;
#endif

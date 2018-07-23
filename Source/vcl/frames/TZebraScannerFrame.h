#ifndef TZebraScannerFrameH
#define TZebraScannerFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "barcodereader/atDS457.h"
#include "dslProperty.h"
//---------------------------------------------------------------------------

using dsl::Property;

class PACKAGE TZebraScannerFrame : public TFrame
{
    __published:	// IDE-managed Components
        TPanel *mMiddleLeftPanel;
        TGroupBox *GroupBox3;
        TPanel *mTopPanel;
        TComboBox *mComportCB;
        TButton *mConnectZebraBtn;
        TComboBox *mBaudRateCB;
        TGroupBox *GroupBox1;
        TButton *mBeepBtn;
        TGroupBox *GroupBox2;
        TButton *mDecodeSessionBtn;
        TRadioGroup *mScannerEnabledRG;
        TPanel *Panel1;
        TRadioGroup *mScannerIllumRG;
        TRadioGroup *mScannerAimRG;
        void __fastcall BtnClick(TObject *Sender);
        void __fastcall SettingsRGClick(TObject *Sender);
        void __fastcall mConnectZebraBtnClick(TObject *Sender);

    private:
                                    //!The barcode reader
            DS457					mZebra;
			dsl::Property<int>	    mZebraCOMPort;
			dsl::Property<int>	    mZebraBaudRate;

	        int						getZebraCOMPortNumber();
			void __fastcall 		onConnectedToZebra();
    	    void __fastcall 		onDisConnectedToZebra();

    public:
        	__fastcall 				TZebraScannerFrame(TComponent* Owner);
};

extern PACKAGE TZebraScannerFrame *ZebraScannerFrame;
#endif

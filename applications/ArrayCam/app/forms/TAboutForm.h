#ifndef TAboutFormH
#define TAboutFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------

class PACKAGE TAboutForm : public TForm
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TMemo *Memo1;
        TPanel *Panel1;
        TImage *Image1;
        TLabel *Label1;
        TLabel *logLabel;
        TLabel *versionLabel;
		void __fastcall FormCreate(TObject *Sender);
		void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:

    public:
        			__fastcall 	TAboutForm(TComponent* Owner);
        void 					populate();
};

extern PACKAGE TAboutForm *AboutForm;
#endif

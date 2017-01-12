#ifndef TAboutATDBFormH
#define TAboutATDBFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TAboutATDBForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TMemo *Memo1;
	TPanel *Panel1;
	TImage *Image1;
	TPanel *Panel2;
	TButton *CloseBtn;
	TLabel *versionLabel;
	TLabel *Label1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TAboutATDBForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutATDBForm *AboutATDBForm;
//---------------------------------------------------------------------------
#endif

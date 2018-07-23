#ifndef TShowFileContentFormH
#define TShowFileContentFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class PACKAGE TShowFileContentForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TShowFileContentForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TShowFileContentForm *ShowFileContentForm;
//---------------------------------------------------------------------------
#endif

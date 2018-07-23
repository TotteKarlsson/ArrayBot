#ifndef TSelectProcessTypeDialogH
#define TSelectProcessTypeDialogH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------


class PACKAGE TSelectProcessTypeDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button1;
	TButton *mOkBtn;
	TRadioGroup *mProcTypeRG;
	void __fastcall FormShow(TObject *Sender);
	private:
		bool	mIsOpenedForParallelProcess;

	public:
    		__fastcall 	TSelectProcessTypeDialog(TComponent* Owner);
		void			setOpenedForParallelProcess();
};

extern PACKAGE TSelectProcessTypeDialog *SelectProcessTypeDialog;
#endif

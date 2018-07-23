#ifndef TCoverSlipFormH
#define TCoverSlipFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
//#include <Vcl.DBLookup.hpp>
#include <Vcl.DBCtrls.hpp>
#include <string>
#include "atBarCodeBuilder.h"
//---------------------------------------------------------------------------

using std::string;

class TCoverSlipForm : public TForm
{
__published:
	TDataSource *CSDataSource;
	TDBLookupComboBox *CoverslipIDCB;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);


    private:
		string					mBarCode;
		void		        	initForm();
		BarCodeBuilder			mBCBuilder;
    public:
        __fastcall TCoverSlipForm(const string& csID, TComponent* Owner);
};

extern PACKAGE TCoverSlipForm *CoverSlipForm;
#endif

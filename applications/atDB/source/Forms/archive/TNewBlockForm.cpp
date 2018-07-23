#include <vcl.h>
#pragma hdrstop
#include "TNewBlockForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewBlockForm *NewBlockForm;

//---------------------------------------------------------------------------
__fastcall TNewBlockForm::TNewBlockForm(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TNewBlockForm::Button3Click(TObject *Sender)
{
	//Extract the document and open with default viewer

//	String id  		= mDocumentsGrid->DataSource->DataSet->FieldByName("id")->AsString;
//	String docName  = mDocumentsGrid->DataSource->DataSet->FieldByName("document_name")->AsString;
//	String type 	= mDocumentsGrid->DataSource->DataSet->FieldByName("type")->AsString;
//    Log(lInfo) << "Opening a :"<<stdstr(type)<<" file";
//
//    TByteDynArray bytes = mDocumentsGrid->DataSource->DataSet->FieldByName("document")->AsBytes;
//
//    String fNames(docName + "." + type);
//    string fName(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA),"Temp", stdstr(fNames)));
//
//	fstream out(fName.c_str(), ios::out|ios::binary);
//    if(out)
//    {
//        for(int i = 0; i < bytes.Length; i++)
//        {
//            out << bytes[i];
//        }
//    }
//
//    out.close();
//    ShellExecuteA(NULL, NULL, fName.c_str(), 0, 0, SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------

void __fastcall TNewBlockForm::Button2Click(TObject *Sender)
{
	//Find out if there are any changes...
    int mrResult = MessageDlg("Sure you want to cancel?", mtWarning, TMsgDlgButtons() << mbYes<<mbNo, 0);
    if (mrResult == mrNo)
    {
    	this->ModalResult = mrNone;
    }

}



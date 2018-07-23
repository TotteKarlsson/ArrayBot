#pragma hdrstop
#include "TMainForm.h"

//---------------------------------------------------------------------------
void __fastcall TMainForm::SlicesGridMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
//	if(Button != TMouseButton::mbRight)
//    {
//    	return;
//    }
//
//    TGridCoord c = SlicesDBGrid->MouseCoord(X,Y);
//    TField* field =  SlicesDBGrid->Columns->operator [](c.X - 1)->Field;
//
//    if(field->FieldKind == fkLookup)
//    {
//        TPoint screen(SlicesDBGrid->ClientToScreen(Point(X,Y)));
//
//        Log(lInfo) << "Field: " << stdstr(field->Value);
//        Log(lInfo) << "Key Fields: " << stdstr(field->KeyFields);
//
//        Log(lInfo) << "Field Lookup: " << stdstr(field->LookupKeyFields);
//        String value = field->DataSet->FieldByName(field->KeyFields)->Value;
//
//        //Query lookup data set for document_id
//        TLocateOptions lo;
//        bool found = field->LookupDataSet->Locate("id", value, lo);
//
//        if(found)
//        {
//            int id = -1;
//            if(!field->LookupDataSet->FieldByName("document_id")->Value.IsNull())
//            {
//                id = field->LookupDataSet->FieldByName("document_id")->Value;
//            }
//
//            Log(lInfo) << "Opening document with id: "<<id;
//
//            TLocateOptions lo;
//            bool found = atdbDM->documentsCDS->Locate("id", id, lo);
//            if(found)
//            {
//            //	SpecimenPopup->Popup(screen.X, screen.Y);
//                openCurrentDocumentFile();
//            }
//        }
//
//        //Get document id
//        Log(lInfo) << "Field Lookup Value" << stdstr(value);
//    }
}

//---------------------------------------------------------------------------
//void TMainForm::openCurrentDocumentFile()
//{
//	TClientDataSet* cds = atdbDM->documentsCDS;
//
//	String id  		= cds->FieldByName("id")->AsString;
//	String docName  = cds->FieldByName("document_name")->AsString;
//	String type 	= cds->FieldByName("type")->AsString;
//
//    Log(lInfo) << "Opening a :"<<stdstr(type)<<" file";
//
//    TByteDynArray bytes = cds->FieldByName("document")->AsBytes;
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
//}
//

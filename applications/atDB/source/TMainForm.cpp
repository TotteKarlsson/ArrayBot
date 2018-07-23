#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "Package/atdbVCLUtils.h"
#include "atVCLUtils.h"
#include "database/atDBUtils.h"
#include "dslLogger.h"
#include "DSLException.h"
#include "database/dslSQLiteException.h"
#include "dslStringUtils.h"
#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Glob.h"
#include "Poco/Timezone.h"
#include "TPGDataModule.h"
#include "TPGCoverSlipDataModule.h"
#include "TPGImagesAndMoviesDataModule.h"
#include "dslTMemoLogger.h"
#include "TShowFileContentForm.h"
#include "TTableUpdateForm.h"
#include "TRegisterFreshCSBatchForm.h"
#include "TPrintLabelForm.h"
#include "database/atQueryBuilder.h"
#include "vcl/forms/TTextInputDialog.h"
#include "forms/TStringInputDialog.h"
#include "TSpecimenForm.h"
#include "TSlicesForm.h"
#include "TBlockForm.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "frames/TMovieItemFrame.h"
#include <JPEG.hpp>
#include "TScanForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIniFileC"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma link "TTableFrame"
#pragma link "dslTIntLabel"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTSTDStringEdit"
#pragma link "TImagesFrame"
#pragma link "TMoviesFrame"
#pragma link "TPGConnectionFrame"
#pragma resource "*.dfm"

TMainForm *MainForm;
using namespace dsl;
using namespace at;

extern string gLogFileName;
extern string gApplicationRegistryRoot;
extern string gDefaultAppTheme;
extern string gFullDateTimeFormat;
extern bool gIsDevelopmentRelease;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),

    mBottomPanelHeight(205),
    mMainTabIndex(0),
	mDustAssayResultImageHeight(100),
    mDustAssayBackGroundImageWidth(100),
	mCoverslipPrintingProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
    mSplashProperties(shared_ptr<TRegistryProperties>(new TRegistryProperties(gApplicationRegistryRoot, "Splash"))),
    mShowSplashOnStartup(true),
    mLogLevel(lAny),
    gCanClose(true),
    logMsgMethod(&logMsg),
    mLogFileReader(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB", gLogFileName), logMsgMethod),
    mDBUserID(0),
	BatchesGBHeight(250),
    mTableUnlockPassword(""),
    mAppProperties("atDB", gApplicationRegistryRoot, "0,5"),
    mGeneralProperties(shared_ptr<IniFileProperties>(new IniFileProperties))
{
    //Close any dataconnection created by stupid TSQLConnection
    mTempFileFolder = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "atDB");
    TMemoLogger::mMemoIsEnabled = false;
    setupIniFile();
    setupAndReadIniParameters();

    //Add grids to db grids container for reading/saving column states
//    mDBGrids.push_back(mProcessForBlocksGrid);
    mDBGrids.push_back(BlocksGrid);
    mDBGrids.push_back(mBlockNotesGrid);
//	mDBGrids.push_back(mBlocksForRibbonsGrid);
    mDBGrids.push_back(mRibbonsGrid);
    mDBGrids.push_back(mRibbonNotesGrid);
    mDBGrids.push_back(mUsersDBGrid);
	mDBGrids.push_back(SlicesGrid);
}

void __fastcall	TMainForm::afterDBServerConnect(System::TObject* Sender)
{
	//Enable datamodules
    TPGConnectionFrame1->afterConnect();
	pgDM->afterConnect();
    csPGDM->afterConnect();
    PGImagesAndMoviesDM->afterConnect();

    UsersCB->KeyValue = mDBUserID.getValue();
    UsersCB->Enabled = true;

    TTableFrame1->assignDBconnection(pgDM->SQLConnection1);
	SpecieRGClick(NULL);

	//Populate table dropdown
    StringList tables = pgDM->getTableNames();
    populateListBox(tables, mTablesLB);
	this->SetFocusedControl(this);
}

//---------------------------------------------------------------------------
void __fastcall	TMainForm::afterDBServerDisconnect(System::TObject* Sender)
{
	pgDM->afterDisConnect();
    TPGConnectionFrame1->afterDisconnect();
    UsersCB->Enabled = false;
}

//This one is called from the reader thread
void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Add(vclstr(mLogFileReader.getData()));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DBGridDblClick(TObject *Sender)
{
    TDBGrid* g = dynamic_cast<TDBGrid*>(Sender);

    if(g == SpecimenGrid)
    {
    	openSpecimenForm();
    }
    else if(g == SlicesGrid)
    {
    	openSlicesForm();
    }
    else if(g == BlocksGrid)
    {
    	openBlocksForm();
    }
    else if(g == SpecimenGrid)
    {
    	openSpecimenForm();
    }
    else if(g == SlicesGrid)
    {
    	openSlicesForm();
    }
    else
    {
    	MessageDlg("This grid don't handle double clicks..", mtInformation, TMsgDlgButtons() << mbOK, 0);
    }
}

void __fastcall TMainForm::openSpecimenForm()
{
	//Open the currently seleceted record in the form
    TSpecimenForm* f = new TSpecimenForm(this);
    int res = f->ShowModal();

    if(res != mrCancel)
    {
        pgDM->specimenCDS->Post();
        pgDM->specimenCDS->First();
    }
    else
    {
		pgDM->specimenCDS->Cancel();
    }
}

void __fastcall TMainForm::openSlicesForm()
{
	//Open the currently seleceted record in the form
    TSlicesForm* f = new TSlicesForm(this);
    int res = f->ShowModal();

    if(res != mrCancel)
    {
        pgDM->slicesCDS->Post();
        pgDM->slicesCDS->First();
    }
    else
    {
		pgDM->slicesCDS->Cancel();
    }
}

//---------------------------------------------------------------------------
String __fastcall TMainForm::createBlockLabel()
{
    String lbl;
    String specie = pgDM->specimenCDS->FieldByName("Lspecie")->AsString;
	if(specie == "Human")
    {
    	lbl = "H";
    }
    else if(specie == "Mouse")
    {
    	lbl = "M";
    }
    else if(specie == "Human Surgical")
    {
    	lbl = "HS";
    }

	lbl = lbl + pgDM->specimenCDS->FieldByName("specimen_id")->AsString + "-" + (pgDM->blocksCDS->RecordCount + 1);

	return lbl;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mATDBServerBtnConnectClick(TObject *Sender)
{
	if(pgDM->SQLConnection1->Connected)
    {
    	//Remove runtime indices
    	TClientDataSet* cds = pgDM->specimenCDS;
	    cds->IndexDefs->Update();
        for(int i = 0; i <cds->IndexDefs->Count; i++)
        {
            String idxName = cds->IndexDefs->operator [](i)->Name;
            Log(lDebug) <<"Removing index: "<< stdstr(idxName);
            if(idxName != "DEFAULT_ORDER" && idxName != "CHANGEINDEX")
            {
                cds->DeleteIndex(idxName);
            }
        }

	    pgDM->SQLConnection1->Connected = false;
	    pgDM->SQLConnection1->Close();
    }
    else
    {
//	    pgDM->connect(mServerIPE->getValue(), mDBUserE->getValue(), mPasswordE->getValue(), mDatabaseE->getValue());
	    pgDM->connect(PGConnectionFrame->getCredentials());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mUpdateNoteBtnClick(TObject *Sender)
{
	pgDM->blockNotesCDS->Post();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::UsersCBCloseUp(TObject *Sender)
{
	if(UsersCB->KeyValue == -1)
    {
    	enableDisableGroupBox(mBlocksGB, false);
    }
    else
    {
    	enableDisableGroupBox(mBlocksGB, true);
		mDBUserID = UsersCB->KeyValue;
    }
}

void __fastcall TMainForm::SlicesGridDrawDataCell(TObject *Sender, const TRect &Rect,
          TField *Field, TGridDrawState State)
{
  	if (Field->DataType == ftMemo)
  	{
     	String S = Field->AsString;
      	SlicesGrid->Canvas->Pen->Color = clWindow;
      	SlicesGrid->Canvas->Brush->Color = clWindow;
      	SlicesGrid->Canvas->Rectangle(Rect);
      	SlicesGrid->Canvas->TextOut(Rect.Left, Rect.Top, S);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SlicesGridDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
//    if (Column->Field->DataType == ftMemo)
//    {
//		SlicesDBGrid->Canvas->FillRect (Rect);
//		SlicesDBGrid->Canvas->TextOut( Rect.Left + 3, Rect.Top + 3,
//              Column->Field->AsString);
//    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mTablesLBClick(TObject *Sender)
{
	if(mTablesLB->ItemIndex != -1)
    {
		String tbl = mTablesLB->Items->Strings[mTablesLB->ItemIndex];
		TTableFrame1->loadTable(stdstr(tbl));
        TTableFrame1->lock();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{

	int mr = MessageDlg("This will print using the default printer on your system (beta).", mtInformation, TMsgDlgButtons() << mbOK<<mbCancel, 0);
    if(mr == mrCancel)
    {
		return;
    }
        //	TPrinter *pr = Printer();
        //	TFont *Font1 = new TFont();
        //	Font1->Name = "Times New Roman";
        //	Font1->Size = 4;
        //    pr->BeginDoc();
        //	TBarcodeTextDefine TextDefine;
        //    TextDefine.DisplayText = dtBarcode;
        //	TextDefine.TextPosition = tpBottomOut;
        //	TextDefine.TextAlignment = taJustify;
        //	TextDefine.TextFont = Font1;
        //	TextDefine.ExtraFontSize = 9;
        //
        ////    TextDefine->
        //	Barcode1D_Code391->Print(10, 10, Barcode1D_Code391->Barcode, true, clBlack, clWhite, TextDefine, 2, 0.3, 20, 10.1, 0);
        //    pr->EndDoc();


	TPrinter *Prntr = Printer();
//	TRect r = Rect(200, 200, Prntr->PageWidth - 200, Prntr->PageHeight - 200);
	Prntr->BeginDoc();
    Prntr->Canvas->Font->Name = "Times New Roman";
    Prntr->Canvas->Font->Size = 4;

	for(int i = 0; i < mLblMakerMemo->Lines->Count; i++)
    {
    	int lineHeight = (i * Prntr->Canvas->TextHeight(mLblMakerMemo->Lines->Strings[i]));
		Prntr->Canvas->TextOut(200, 200 + lineHeight, mLblMakerMemo->Lines->Strings[i]);
    }

//	Prntr->Canvas->Brush->Color = clBlack;
//	Prntr->Canvas->FrameRect(r);
	Prntr->EndDoc();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mProcessForBlocksGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	selectBlocks();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mProcessForBlocksGridCellClick(TColumn *Column)
{
	selectBlocks();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::selectBlocks()
{
//	//Retrieve selected id and apply filter on blocks table
//    pgDM->blocksCDS->Close();
//  	if(mProcessForBlocksGrid->SelectedRows->Count > 0)
//    {
//       	vector<int> p_ids = getSelectedIDS(mProcessForBlocksGrid, "specimen_id");
//    	stringstream s;
//        s << "SELECT * FROM blocks WHERE specimen_id IN (";
//
//        for(int i = 0; i < p_ids.size(); i++)
//        {
//			s << p_ids[i];
//            if(i < p_ids.size() - 1)
//            {
//            	s << ", ";
//            }
//        }
//        s << ")";
//		pgDM->blocksCDS->CommandText = s.str().c_str();
//        Log(lDebug) << "Selected: "<<s.str();
//    }
//    else
//    {
//        pgDM->blocksCDS->CommandText = "SELECT * FROM blocks WHERE specimen_id = :specimen_id ORDER BY id DESC";
//    }
//    pgDM->blocksCDS->Open();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PageControl2Change(TObject *Sender)
{
	//If we are opening the Ribbons page, sett blocks query to select all blocks
   	if(PageControl2->TabIndex == 2)
    {
//        pgDM->blocksCDS->Close();
//        pgDM->blocksCDS->CommandText = "SELECT * FROM blocks ORDER BY id DESC";
//        pgDM->blocksCDS->Open();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mAddDocBtnClick(TObject *Sender)
{
//	//Browse for file
//	string filename = browseForFile();
//
//    if(filename.size())
//    {
//    	Log(lInfo) << "Adding document: "<<filename<<" to documents table";
//
//        string fName(getFileNameNoPath(filename));
//        string fExt(getFileExtension(filename));
//
//        if(!fName.size())
//        {
//        	MessageDlg("Something is wrong with this documents filename and or extension!", mtWarning, TMsgDlgButtons() << mbOK, 0);
//        	return;
//        }
//
//        ifstream ifs(filename.c_str(), ios::binary|ios::ate);
//    	ifstream::pos_type pos = ifs.tellg();
//
//	    std::vector<char> result(pos);
//    	ifs.seekg(0, ios::beg);
//	    ifs.read(&result[0], pos);
//
//		TSQLQuery* q = new TSQLQuery(NULL);
//        q->SQLConnection = pgDM->SQLConnection1;
//    	stringstream s;
//
//        q->SQL->Add("INSERT INTO documents ");
//        q->SQL->Add("(document_name, document, type) VALUES  ");
//		q->SQL->Add("( :dname, :doc, :type )");
//        q->ParamByName("dname")->Value = getFileNameNoExtension(fName).c_str();
//
//        TByteDynArray bytes;
//        bytes.Length = result.size();
//        for(int i = 0; i < result.size(); i++)
//        {
//        	bytes[i] = result[i];
//        }
//
//        q->ParamByName("doc")->AsBlob = bytes;
//		q->ParamByName("type")->Value = fExt.c_str();
//        q->ExecSQL();
//        delete q;
//       	pgDM->documentsCDS->ApplyUpdates(0);
//    }
//	pgDM->documentsCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SlicesDBGridDblClick(TObject *Sender)
{
//	//Show current record on a form
//    TNewSpecimenForm* nsf = new TNewSpecimenForm(this);
//    pgDM->specimenCDS->Open();
//    pgDM->specimenCDS->Edit();
//    pgDM->substitutionProtocol->Open();
//	pgDM->substitutionProtocol->Edit();
//    int res = nsf->ShowModal();
//    if(res == mrCancel)
//    {
//        //revert
//        pgDM->specimenCDS->Cancel();
//    }
//    else
//    {
//        pgDM->specimenCDS->Post();
//        pgDM->specimenCDS->First();
//    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SlicesGridMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(Button == TMouseButton::mbRight)
    {
    	TGridCoord c = SlicesGrid->MouseCoord(X,Y);
        if(c.X > -1 && c.Y > -1)
        {
			TField* field =  SlicesGrid->Columns->operator [](c.X)->Field;
			SpecimenPopup->Popup(X,Y);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BlocksGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//When selecting multiple blocks, prepare Memo for block text output
	createBlockLabels();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::createBlockLabels()
{
	mLblMakerMemo->Clear();
  	stringstream s;
  	if(BlocksGrid->SelectedRows->Count > 0)
    {
      	for(int i = 0; i < BlocksGrid->SelectedRows->Count; i++)
    	{
    		TBookmarkList* bookMarkList = BlocksGrid->SelectedRows;
            if(bookMarkList->Count == BlocksGrid->SelectedRows->Count)
            {
        		pgDM->blocksCDS->GotoBookmark((*bookMarkList)[i]);
                String str = pgDM->blocksCDS->FieldByName("Cblock_label")->AsString;
		        s << stdstr(str);
                if(i < BlocksGrid->SelectedRows->Count -1)
                {
					s<<"\n";
                }
            }
        }

        StringList l(s.str(), '\n');
		mLblMakerMemo->Clear();
        for(int i = 0; i < l.count(); i++)
        {
			mLblMakerMemo->Lines->Add(vclstr(l[i]));
        }
    }
    else
    {
        String str = pgDM->blocksCDS->FieldByName("Cblock_label")->AsString;
		s << stdstr(str);

        StringList l(s.str(), '\n');
		mLblMakerMemo->Clear();
        for(int i = 0; i < l.count(); i++)
        {
			mLblMakerMemo->Lines->Add(vclstr(l[i]));
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BlocksGridCellClick(TColumn *Column)
{
	createBlockLabels();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SlicesGridMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	TGridCoord pt = SlicesGrid->MouseCoord(X,Y);
	SlicesGrid->Cursor = (pt.Y == 0) ? crHandPoint : crDefault;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SlicesGridTitleClick(TColumn *Column)
{
	TField* field =  Column->Field;
	static int PreviousColumnIndex = -1;
	if(SlicesGrid->DataSource->DataSet == pgDM->specimenCDS && PreviousColumnIndex != -1)
    {
    	TColumn* prevCol = SlicesGrid->Columns->Items[PreviousColumnIndex];
        if(prevCol)
        {
	 		prevCol->Title->Font->Style = TFontStyles();
        }
    }

	Column->Title->Font->Style =  TFontStyles() <<  fsBold;
	PreviousColumnIndex = Column->Index;

    String fieldName;
	TField* Field = pgDM->specimenCDS->Fields->FindField(Column->FieldName);
    if(Field)
    {
    	if(Field->FieldKind == fkLookup)
        {
        	fieldName = Field->KeyFields;
        }
        else
        {
        	fieldName = Column->FieldName;
        }
    }
	SortClientDataSet(pgDM->specimenCDS, fieldName);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mPrintTestLabelBtnClick(TObject *Sender)
{
   	TSCLIB lblPrinter;

    if(!lblPrinter.load("TSCLIB.dll"))
    {
    	Log(lError) << "Failed to load mTSC library..";
        return;
    }

    stringstream lbl;
    lbl <<mTestLabel->getValue();
    Log(lInfo) << "Printing label: "<<lbl.str();


    BarcodePrintParameters p;
    p.command = stdlines(mBarCodeCommandMemo->Lines);
    lblPrinter.printCoverSlipLabel(p, lbl.str(), 1);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mRegisterFreshBatchBtnClick(TObject *Sender)
{
	//Open Register batch form
    TRegisterFreshCSBatchForm* f = new TRegisterFreshCSBatchForm(this);
    f->ShowModal();
    delete f;

	selectCoverSlips(FreshBatchesGrid, CoverSlipsGrid);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mPrintBatchLblBtnClick(TObject *Sender)
{
	//Open print label form
	TPrintLabelForm* f = new TPrintLabelForm(this);

    //Get current Batch Label
    String code_1 = csPGDM->csFreshBatchesCDS->FieldByName("lot_number")->AsString;
    String code_2 = csPGDM->csFreshBatchesCDS->FieldByName("box_number")->AsString;

    if(code_1.Length())
    {
    	f->setup(stdstr(code_1 + '_' + code_2));
	    f->ShowModal();
    	delete f;
    }
    else
    {
    	MessageDlg("No label to print was selected..", mtError, TMsgDlgButtons() << mbOK, 0);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FreshBatchesGridCellClick(TColumn *Column)
{
	selectCoverSlips(FreshBatchesGrid, CoverSlipsGrid);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FreshBatchesGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(FreshBatchesGrid->DataSource->DataSet->Eof != true)
    {
        selectCoverSlips(FreshBatchesGrid, CoverSlipsGrid);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::selectCoverSlips(TDBGrid* masterGrid, TDBGrid* detailGrid)
{
	//Retrieve selected ids from masterGrid
    // and apply filter on details table
    TClientDataSet* detailDataSet = dynamic_cast<TClientDataSet*>(detailGrid->DataSource->DataSet);
    detailDataSet->Close();
	TDataSet* masterDataSet = masterGrid->DataSource->DataSet;

  	if(masterGrid->SelectedRows->Count > 0)
    {
    	vector<int> p_ids = getSelectedIDS(masterGrid, "id");

    	QueryBuilder qb;
        qb << "SELECT * FROM coverslips WHERE freshcsbatch IN (";

        for(int i = 0; i < p_ids.size(); i++)
        {
			qb << p_ids[i];
            if(i < p_ids.size() - 1)
            {
            	qb << ", ";
            }
        }
        qb << ")";
		detailDataSet->CommandText = qb.asCString();
        Log(lDebug) << "Selected: "<<qb.asString();
    }
    else
    {
    	//Get master ID
        int id = masterDataSet->FieldByName("id")->AsInteger;
        detailDataSet->CommandText =
        	"SELECT * FROM coverslips WHERE freshcsbatch = " + IntToStr(id) +" ORDER BY freshcsbatch DESC";
    }

    detailDataSet->Open();
}

//---------------------------------------------------------------------------
//Rename to RegisterSilanized

void __fastcall TMainForm::mRegisterCleanRoundBtnClick(TObject *Sender)
{
	//Get selected cs records in the coverslip grid
    vector<int> coverslipIDS = getSelectedIDS(CoverSlipsGrid, "id");

    if(coverslipIDS.size() == 0)
    {
	 	MessageDlg("Please select some coverslips!", mtInformation, TMsgDlgButtons() << mbOK, 0);
		return;
    }

    StringList fromInts(coverslipIDS);
	Log(lInfo) << "Selected ids: (" << fromInts.asString(',')<<")";
    int mr = MessageDlg("Register a SILANIZED batch for selected coverslips?", mtInformation, TMsgDlgButtons() << mbYes << mbCancel, 0);
    if(mr != mrYes)
    {
    	return;
    }

    //Create a new cleanround batch record, and associate selected coverslips with it
    TSQLQuery* q = new TSQLQuery(NULL);
    q->SQLConnection = pgDM->SQLConnection1;
    QueryBuilder qb;

    int current_user = getCurrentUserID();
    qb <<"INSERT into cleancsbatches (user_id, count) VALUES ('"<<current_user<<"','"<<coverslipIDS.size()<<"') RETURNING id";

    Log(lDebug) << "Query: " << qb.asString();
    q->SQL->Add(qb.asCString());
    q->Open();


    //Get last insert ID for cleanCS batch and update coverslips
    int cleanCSBatchID = q->FieldByName("id")->AsInteger;

    for(int i = 0; i < coverslipIDS.size(); i++)
    {
        qb.clear();
        qb 	<< "UPDATE coverslips SET status='"<<cssPostSilanization<<"',cleanCSBatch='"<<cleanCSBatchID<<"' "
            << "WHERE id='"<<coverslipIDS[i]<<"'";

        Log(lDebug) << "Query: " << qb.asString();
        q->SQL->Text = qb.asCString();
        int res = q->ExecSQL();
        Log(lDebug) << "Query result: " << res;

        //Update status and associate each coverslip
        Log(lInfo) << "Updating record:" <<coverslipIDS[i];
    }

    delete q;
	csPGDM->csCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mRegisterCarbonCoatBatchBtnClick(TObject *Sender)
{
	//Get selected cs records in the coverslip grid
    vector<int> coverslipIDS = getSelectedIDS(CoverSlipsGrid, "id");

    if(coverslipIDS.size() == 0)
    {
	 	MessageDlg("Please select some coverslips!", mtInformation, TMsgDlgButtons() << mbOK, 0);
		return;
    }

    StringList fromInts(coverslipIDS);
	Log(lInfo) << "Selected ids: (" << fromInts.asString(',')<<")";
    int mr = MessageDlg("Create a carboncoated batch for selected coverslips? This will also print coverslip labels.", mtInformation, TMsgDlgButtons() << mbYes << mbCancel, 0);
    if(mr != mrYes)
    {
    	return;
    }

    //Create a new cleanround record, and associate slected coverslips with it
    TSQLQuery* q = new TSQLQuery(NULL);
    q->SQLConnection = pgDM->SQLConnection1;

    QueryBuilder qb;
    int current_user = getCurrentUserID();
    qb <<"INSERT into carboncoatedcsbatches (user_id, count) VALUES ('"<<current_user<<"','"<<coverslipIDS.size()<<"') RETURNING id";

    Log(lDebug) << "Query: " << qb.asString();
    q->SQL->Add(qb.asCString());
   	q->Open();

    //Get last insert ID for cleanCS batch and update coverslips
//    int carboncoatbatchID = getLastInsertID(pgDM->SQLConnection1);
    int carboncoatbatchID = q->FieldByName("id")->AsInteger;;

    for(int i = 0; i < coverslipIDS.size(); i++)
    {
        qb.clear();
        qb 	<< "UPDATE coverslips SET status='"<<cssPostCarbonCoat<<"', carboncoatbatch='"<<carboncoatbatchID<<"' "
            << "WHERE id='"<<coverslipIDS[i]<<"'";

        Log(lDebug) << "Query: " << qb.asString();
        q->SQL->Text = qb.asCString();
        int res = q->ExecSQL();
        Log(lDebug) << "Query result: " << res;

        //Update status and associate each coverslip
        Log(lInfo) << "Updating record:" <<coverslipIDS[i];
    }

    BarcodePrintParameters p;
    p.command = stdlines(mBarCodeCommandMemo->Lines);

    //Create and print labels
    if(!createAndPrintCoverSlipLabels(p, coverslipIDS, pgDM->SQLConnection1))
    {
		Log(lError) << "There was a problem creating and/or printing coverslip labels";
    }

    delete q;
	csPGDM->csCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

    //Get selected cs records in the coverslip grid
    vector<int> coverslipIDS = getSelectedIDS(CoverSlipsGrid, "id");

	//These are actions requiring a selection of coverslips
	if(b == mPrintCSLabelsBtn || b == mAddCSNote)
    {
        if(coverslipIDS.size() == 0)
        {
            MessageDlg("Please select some coverslips!", mtInformation, TMsgDlgButtons() << mbOK, 0);
            return;
        }

        if(b == mPrintCSLabelsBtn)
        {
            BarcodePrintParameters p;
            p.command 			= stdlines(mBarCodeCommandMemo->Lines);

            //Create and print labels
            if(!createAndPrintCoverSlipLabels(p, coverslipIDS, pgDM->SQLConnection1))
            {
                Log(lError) << "There was a problem creating and/or printing coverslip labels";
            }
        }
        else if(b == mAddCSNote)
        {
            TTextInputDialog* f = new TTextInputDialog(this);

            //Setup form
            f->Caption = "Add note to multiple coverslips";

            //Todo: use another function for getDateTimeString
            stringstream msg;
            msg <<"---------------------------------------------------------------------";
            msg <<"\nNew note added on "<<getDateTimeString() << " by " <<stdstr(UsersCB->Text)<<endl;
            msg <<"---------------------------------------------------------------------";
            f->setText(msg.str().c_str());

            f->mInfoMemo->SelStart = f->mInfoMemo->GetTextLen();
            f->mInfoMemo->Perform(EM_SCROLLCARET, 0, 0);
            int mr = f->ShowModal();

            if(mr == mrOk)
            {
                string note = f->getText();
                Log(lError) << "Adding note to multiple coverslips";
                addNoteToMultipleCoverSlips(coverslipIDS, pgDM->SQLConnection1, note);
                CSNavigator->BtnClick(::Data::Bind::Controls::nbRefresh);
            }
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CoverSlipsGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	CoverSlipsGrid->SelectedRows->Count;
	mNrOfSelectedCS->setValue(CoverSlipsGrid->SelectedRows->Count);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CoverSlipsGridCellClick(TColumn *Column)
{
	CoverSlipsGrid->SelectedRows->Count;
	mNrOfSelectedCS->setValue(CoverSlipsGrid->SelectedRows->Count);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DiscardedMenuItemClick(TObject *Sender)
{

	//Get selected cs records in the coverslip grid
    vector<int> coverslipIDS = getSelectedIDS(CoverSlipsGrid, "id");
    if(coverslipIDS.size() == 0)
    {
	 	MessageDlg("Please select some coverslips!", mtInformation, TMsgDlgButtons() << mbOK, 0);
		return;
    }

    StringList fromInts(coverslipIDS);
	Log(lInfo) << "Selected ids: (" << fromInts.asString(',')<<")";


	TMenuItem* mi = dynamic_cast<TMenuItem*>(Sender);
    CoversSlipStatusE status;
    int mr;
    if(mi == DiscardedMenuItem)
    {
	    mr = MessageDlg("Change status to 'Discarded' for selected coverslips?", mtInformation, TMsgDlgButtons() << mbYes << mbCancel, 0);
		status = cssDiscarded;
    }
    else if(mi == FreshoutoftheBoxMenuItem)
    {
	    mr = MessageDlg("Change status to 'Fresh Out of the Box for selected Coverslips?", mtInformation, TMsgDlgButtons() << mbYes << mbCancel, 0);
    	status = cssFreshOutOfTheBox;
    }
    else
    {
	    MessageDlg("Invalid selection......!", mtInformation, TMsgDlgButtons() << mbOK, 0);
    }

    if(mr != mrYes)
    {
    	return;
    }

    //Create a new cleanround record, and associate slected coverslips with it
    TSQLQuery* q = new TSQLQuery(NULL);
    q->SQLConnection = pgDM->SQLConnection1;
    QueryBuilder qb;

    int current_user = getCurrentUserID();
    for(int i = 0; i < coverslipIDS.size(); i++)
    {
        qb.clear();
        qb 	<< "UPDATE coverslips SET status='"<<status<<"'"
            << "WHERE id='"<<coverslipIDS[i]<<"'";

        Log(lDebug) << "Query: " << qb.asString();
        q->SQL->Text = qb.asCString();
        int res = q->ExecSQL();
        Log(lDebug) << "Query result: " << res;

        //Update status and associate each coverslip
        Log(lInfo) << "Updating status for coverslip with ID:" <<coverslipIDS[i];
    }

    delete q;
	csPGDM->csCDS->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::UnlocktablesBtnClick(TObject *Sender)
{
	static int nrOfTrys = 1;
	//Enable editing of current table
	auto_ptr<TStringInputDialog> f(new TStringInputDialog(this));
    f->Caption = "Input password";
    f->STDStringLabeledEdit1->EditLabel->Visible = false;
    f->BottomPanel->Visible = false;
    f->Width = 473;
    f->Height = 110;
    f->STDStringLabeledEdit1->PasswordChar = '*';

    if(f->ShowModal() == mrCancel)
    {
    	return;
    }

    if(f->getText() == mTableUnlockPassword.getValue())
    {
    	TTableFrame1->unlock();
	    nrOfTrys = 0;
    }
    else
    {
    	switch(nrOfTrys)
        {
    		case 1:
            	MessageDlg("That password is not the right one!\n\nYou get one more try, but after that, all files on this computer will be erased!", mtWarning, TMsgDlgButtons() << mbOK, 0);
			    nrOfTrys++;
			break;
    		case 2:
            	MessageDlg("We are sorry. That password is not the right one!\n\nAll files on this computer will now be erased!", mtWarning, TMsgDlgButtons() << mbOK, 0);
            	MessageDlg("Ok, one more try!", mtWarning, TMsgDlgButtons() << mbOK, 0);
			    nrOfTrys++;
			break;
			default:
            	MessageDlg("Ok, one more try!", mtWarning, TMsgDlgButtons() << mbOK, 0);
			    nrOfTrys = 1;
            break;
        }
    }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::SpecieRGClick(TObject *Sender)
{
	if(!pgDM)
    {
    	return;
    }
    //Apply filter to specimen table
   	string specie = stdstr(SpecieRG->Items->Strings[SpecieRG->ItemIndex]);
    int specieID = pgDM->getIDForSpecie(specie);

	pgDM->specimenCDS->Filter = "specie = '" + IntToStr(specieID) + "'";
    pgDM->specimenCDS->Filtered = true;
}

void __fastcall TMainForm::openBlocksForm()
{
	//Open the currently seleceted record in the form
    TBlockForm* f = new TBlockForm(this);
    int res = f->ShowModal();

    if(res != mrCancel)
    {
    	// Create block label
        String str = pgDM->createBlockLabel();
        pgDM->blocksCDS->FieldValues["label"] = str;
        pgDM->blocksCDS->Post();
        pgDM->blocksCDS->First();
    }
    else
    {
		pgDM->blocksCDS->Cancel();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ApplicationEvents1Exception(TObject *Sender, Exception *E)
{
	Log(lError) << "There was an exception";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BlockIDSLLBKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkUp || Key == vkDown || Key == vkLeft|| Key == vkRight)
    {

    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BlockIDSLLBMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	populateMedia();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BlockIDSLLBKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == vkUp || Key == vkDown|| Key == vkLeft|| Key == vkRight)
    {
        populateMedia();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BrowseForFolder1Accept(TObject *Sender)
{
	MediaFolderE->setValue(stdstr(BrowseForFolder1->Folder));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::MediaPageControlChange(TObject *Sender)
{
	populateMedia();
}

void TMainForm::populateMedia()
{
    if(BlockIDSLLB->KeyValue.IsNull())
    {
        return;
    }

    //Check what page is open, movies or images
    Poco::Path p(MediaFolderE->getValue());
    if(MediaPageControl->TabIndex == 0)
    {
		TMoviesFrame1->populate(BlockIDSLLB->KeyValue, p);
    }
    else
	{
		TImagesFrame1->populate(BlockIDSLLB->KeyValue, p);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mRibbonsGridCellClick(TColumn *Column)
{
    if(BlockIDCB->KeyValue.IsNull())
    {
        return;
    }

    Poco::Path p(MediaFolderE->getValue());
	MoviesFrame1->populate(BlockIDCB->KeyValue, stdstr(RibbonIDLbl->Caption), p);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BlockIDCBCloseUp(TObject *Sender)
{
	TDBLookupComboBox* b = dynamic_cast<TDBLookupComboBox*>(Sender);
	if(b == BlockIDCB )
    {
    	if(!b->KeyValue.IsNull())
		{
//        	mBlockID.setValue(b->KeyValue);
        	pgDM->blockNotesCDS->Active = true;
        }
    }
}


void __fastcall TMainForm::CoverslipIDEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key != vkReturn)
    {
    	return;
    }

    //Set coverslip ID to edit box text
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ArrayBotButton1Click(TObject *Sender)
{
    Poco::Path p(MediaFolderE->getValue());
	TScanForm* f = new TScanForm(p, this);
    f->ShowModal();
    delete f;
}



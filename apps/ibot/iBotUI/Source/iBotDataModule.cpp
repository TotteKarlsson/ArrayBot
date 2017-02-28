#pragma hdrstop
#include "iBotDataModule.h"
#include "mtkVCLUtils.h"

using namespace mtk;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma link "DbxDevartSQLite"
#pragma resource "*.dfm"
TiBotDataModule *iBotDataModule;
//---------------------------------------------------------------------------
__fastcall TiBotDataModule::TiBotDataModule(TComponent* Owner)
	: TDataModule(Owner)
{
}

void __fastcall TiBotDataModule::mImageStainSessionCDSetAfterPost(TDataSet *DataSet)
{
	Log(lInfo) <<"Hello";
}
//---------------------------------------------------------------------------

void __fastcall TiBotDataModule::SQLConnection1AfterConnect(TObject *Sender)

{
	Log(lInfo) << "After Connect";
}
//---------------------------------------------------------------------------


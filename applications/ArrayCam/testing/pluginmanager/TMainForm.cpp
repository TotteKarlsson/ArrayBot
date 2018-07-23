#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslException.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslPluginWithEvents.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTAboutFrame"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TMainForm *MainForm;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}

__fastcall TMainForm::~TMainForm()
{
	mPythonPM.getPythonInterpreter()->finalize();
	mPythonPM.unloadAll();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadPluginsBtnClick(TObject *Sender)
{
    TButton* b = dynamic_cast<TButton*>(Sender);

    if(b == LoadPluginsBtn)
    {
//		loadPlugins();
        loadPythonPlugins();
    }
    else if(b == GetPluginsInfoBtn)
    {
        //Get information about the plugin manager
        Log(lInfo) << PluginManager1->mPM.getInfo();
    }
}

void TMainForm::loadPlugins()
{
//	try
//	{
//        int j = PluginManager1->loadPlugins();
//        if(j == 0)
//        {
//            Log(lInfo) << "No plugins were loaded.";
//        }
//        else
//        {
//            Log(lInfo) << "Loaded " << j << " plugins.";
//            Log(lInfo) << PluginManager1->mPM.getInfo();
//            PluginsLB->Clear();
//
//            StringList pl = PluginManager1->getLoadedPluginsNames();
//            for(int i = 0; i < pl.count(); i++)
//            {
//                Plugin* p = PluginManager1->Plugins[i];
//                PluginsLB->AddItem(pl[i].c_str(), (TObject*) p);
//            }
//        }
//    }
//	catch(const DSLException& e)
//	{
//		Log(lError) << "Exception: "<<e.what();
//	}
}
void TMainForm::loadPythonPlugins()
{
	try
	{
        int j = mPythonPM.loadPlugins();
        if(j == 0)
        {
            Log(lInfo) << "No plugins were loaded.";
        }
        else
        {
            Log(lInfo) << "Loaded " << j << " plugins.";
            Log(lInfo) << mPythonPM.getInfo();
            PluginsLB->Clear();

            StringList pl = mPythonPM.getPluginNames();
            for(int i = 0; i < pl.count(); i++)
            {
                Plugin* p = mPythonPM.getPlugin(i);
                PluginsLB->AddItem(pl[i].c_str(), (TObject*) p);
            }
        }
    }
	catch(const DSLException& e)
	{
		Log(lError) << "Exception: "<<e.what();
	}
}

void __fastcall TMainForm::FormShow(TObject *Sender)
{
    PluginInfoFrame = new TPluginInfoFrame(NULL, this);
	LogFileReader1->start();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
	{
		Close();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(LogFileReader1->isRunning() ||
       PluginManager1->getNumberOfPlugins()
    )
    {
        CanClose = false;
    }
    else
    {
        CanClose = true;
    }

    if(!CanClose)
    {
	    ShutDownTimer->Enabled = true;
    }
}

void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;

	if(LogFileReader1->isRunning())
    {
		LogFileReader1->stop();
    }

    if(PluginManager1->getNumberOfPlugins())
    {
		PluginManager1->unLoadAllPlugins();
    }

    Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PluginsLBClick(TObject *Sender)
{
    //Retrieve plugin
//    int indx = PluginsLB->ItemIndex;
//    if(indx > -1)
//    {
//        Plugin* p = (Plugin*) PluginsLB->Items->Objects[indx];
//        if(p)
//        {
//            Log(lInfo) << "Checking out plugin: "<<p->getName();
//            Log(lInfo) <<p->getExtendedInfo();
//            ExecuteBtn->Enabled = true;
//            if(!PluginInfoFrame)
//            {
//                MessageDlg("Hoops", mtError, TMsgDlgButtons() << mbOK, 0);
//            }
//
//            if(PluginInfoFrame->populate(p))
//            {
//                PluginInfoFrame->Parent = TopGB;
//                PluginInfoFrame->Left = PluginsLB->Left + 100;
//                PluginInfoFrame->Align = alLeft;
//            }
//        }
//    }
//    else
//    {
//    	ExecuteBtn->Enabled = false;
//    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PythonPluginsLBClick(TObject *Sender)
{
    //Retrieve plugin
    int indx = PluginsLB->ItemIndex;
    if(indx > -1)
    {
        Plugin* p = (Plugin*) PluginsLB->Items->Objects[indx];
        if(p)
        {
            Log(lInfo) << "Examining the plugin: "<<p->getName();
            Log(lInfo) << "\n" << p->getExtendedInfo();
            ExecuteBtn->Enabled = true;
            if(!PluginInfoFrame)
            {
                MessageDlg("Hoops", mtError, TMsgDlgButtons() << mbOK, 0);
            }

            if(PluginInfoFrame->populate(p))
            {
                PluginInfoFrame->Parent = PythonGB;
                PluginInfoFrame->Left = PluginsLB->Left + 100;
                PluginInfoFrame->Align = alLeft;
            }
        }
    }
    else
    {
    	ExecuteBtn->Enabled = false;
    }
}

void __fastcall TMainForm::ExecuteBtnClick(TObject *Sender)
{
    //
    Plugin* p = getSelectedPlugin();
    if(p)
    {
         if(dynamic_cast<PluginWithEvents*>(p))
         {
            PluginWithEvents* pwe = dynamic_cast<PluginWithEvents*>(p);
            //pwe->assignOnStartedEvent(onPluginStarted, nullptr, nullptr);
//            pwe->assignOnProgressEvent(onPluginRunning, nullptr, nullptr);
//            pwe->assignOnFinishedEvent(onPluginExit, nullptr, nullptr);
         }

        p->execute(NULL, true);
    }
}

Plugin* TMainForm::getSelectedPlugin()
{
    int indx = PluginsLB->ItemIndex;
    if(indx > -1)
    {
        Plugin* p = (Plugin*) PluginsLB->Items->Objects[indx];
        return p;
    }
    return nullptr;
}

void onPluginStarted(void* a, void* b)
{
    Log(lInfo) << "Plugin called its started method";
}

void onPluginRunning(void* a, void* b)
{
    Log(lInfo) << "Plugin called its running method";
}

void onPluginExit(void* a, void* b)
{
    Log(lInfo) << "Plugin worker exited";

    if(b)
    {
	    Property<int>* p = (Property<int>*) b;
	    Log(lInfo) << "The plugins property: " << p->getLabel() << " value is " << p->getValue();
    }
}




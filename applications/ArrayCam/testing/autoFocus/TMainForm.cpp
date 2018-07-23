#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "atCore.h"
#include "ArrayCamMessages.h"
#include "dslVCLUtils.h"
#include "TSelectIntegerForm.h"
#include "ArrayCamUtilities.h"
#include <bitset>
#include "arraybot/apt/atAPTMotor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabel"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma link "TNavitarMotorFrame"
#pragma link "dslTLogFileReader"
#pragma link "dslTLogMemoFrame"
#pragma link "TMotorFrame"
#pragma resource "*.dfm"

TMainForm *MainForm;

extern ArrayCamUtilities acu;
using namespace dsl;
using namespace std;
using namespace at;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	:
    	TRegistryForm(acu.AppRegistryRoot, "MainForm", Owner),
        mSettingsForm(NULL),
        mAVIID(0),
    	mIniFile(joinPath(acu.AppDataFolder, "ArrayCam.ini"), true, true),
    	mLogLevel(lAny),
        mAutoGain(false),
        mAutoExposure(false),
        mAutoBlackLevel(false),
        mAutoWhiteBalance(false),
        mSoftwareGamma(0.0),
        mVerticalMirror(false),
        mHorizontalMirror(false),
        mReticle(mPB->Canvas),
        mReticle2(mPB->Canvas, TReticle::rtCrossHair, clBlue),
        mServiceCamera1(mCamera1, 1, this->Handle),
        mMovingReticle(false),
        mMainContentPanelWidth(700),
        mReticleVisible(false),
	    mRenderMode(IS_RENDER_FIT_TO_WINDOW),
        LoggerForm(NULL)//,
//        mFocusScoreWatcher("d:\\AC\\live")
{
    //Init the DLL -> give intra messages their ID's
	initABCoreLib();

    std::bitset<23> s;

    //Properties are retrieved and saved to an ini file
    setupProperties();
    mGeneralProperties.read();

    //The loglevel is read from ini file
	gLogger.setLogLevel(mLogLevel);
	TLogMemoFrame1->init();

    mServiceCamera1.onCameraOpen 			= onCameraOpen;
    mServiceCamera1.onCameraClose 			= onCameraClose;


    /******** Update UI controls *************/
    //Todo, put these in a container and call update in a loop

    MainContentPanel->Width = mMainContentPanelWidth;

	ArrayCamServerPortE->update();
    MediaFolderE->update();

	THeaderSection* Section = CameraHC->Sections->Items[2];
    Section->Text = mReticleVisible ? "Hide Reticle" : "Show Reticle";

	mReticle2.visible(false);

    //Setup the focusController
//	mFocusScoreWatcher.assignCallback(onFocusScore);
}

double getScore(const string& fName)
{
    ifstream in(fName.c_str());
	double val(-1);
    if(in)
    {
        in >> val;
    }
    return val;
}

void TMainForm::onFocusScore(int* notifier)
{
//    enum direction {fwd, rev};
//    static double lastScore = 0;
//    static direction directionWas  = fwd;
//    string sharpnessFile("sharpness.txt");
//	DirectoryNotifier* n = (DirectoryNotifier*) notifier;
//    if (n->checkOverflow() || !n)
//    {
//        Log(lInfo) << "Queue overflowed, or notifier is NULL."<<endl;
//    }
//    else
//    {
//        DirectoryChangeNotification notification;
//        n->pop(notification);
//		//        Log(lInfo) << actionToStr(notification.first) << " " << notification.second << endl;
//        if(notification.second == sharpnessFile)
//        {
//
//            double newScore = getScore(joinPath("d:\\AC\\live", sharpnessFile));
//			Log(lInfo) << "Got new sharpness value"<<newScore;
//            APTMotor* m = dynamic_cast<APTMotor*>(this->mDeviceManager.getFirst());
//            double scoreDifference = fabs(newScore) - fabs(lastScore);
//            double moveStep(0.1);
//            if(newScore != -1 && m != NULL && (fabs(scoreDifference) > 0.001))
//            {
//                if(!m->isActive())
//                {
//                    if(newScore > lastScore)
//                    {
//                        if(directionWas == fwd)
//                        {
//                        	m->moveRelative(moveStep);
//                        	Log(lInfo) << "Moving forward";
//	                    }
//                        else
//                        {
//                            m->moveRelative(-1.*moveStep);
//                            directionWas = rev;
//                            Log(lInfo) << "Moving reverse";
//                        }
//                    }
//                    else//Move oppposite direction
//                    {
//                        if(directionWas == fwd)
//                        {
//                            m->moveRelative(-1.*moveStep);
//                            directionWas = rev;
//                        	Log(lInfo) << "Moving reverse";
//	                    }
//                        else
//                        {
//                        	m->moveRelative(moveStep);
//                            Log(lInfo) << "Moving forward";
//                        }
//                    }
//					lastScore = newScore;
//            	}
//            }
//        }
//    }
}

__fastcall TMainForm::~TMainForm()
{}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mStartupTimerTimer(TObject *Sender)
{
	mStartupTimer->Enabled = false;

    try
    {
        //Connect navitar motors
//        NavitarControllerConnectBtn->Click();

    }
    catch(const TDBXError& e)
    {
        Log(lError) << "There was an exception: "<<stdstr(e.Message);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{;}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AppInBox(ATWindowStructMessage& msg)
{
    if(msg.lparam == NULL)
    {
        return;
    }

    try
    {
        ApplicationMessageEnum aMsg = (ApplicationMessageEnum) msg.wparam;

        switch(aMsg)
        {

            case atMiscMessage:
            {
            	int* m = (int*) msg.lparam;
                Log(lDebug) << "Handling Misc message: \"" << *m;
            }
            break;
            default:
            break ;
        }
	}
	catch(...)
	{
		Log(lError) << "An exception was thrown in AppInBox.";
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::StatusBar1Hint(TObject *Sender)
{
	;
}

void __fastcall TMainForm::ToggleMainContentPanelAExecute(TObject *Sender)
{
	MainContentPanel->Visible 		= !MainContentPanel->Visible;
	ToggleMainContentBtn->Visible 	= !MainContentPanel->Visible;
    Splitter2->Visible 				= MainContentPanel->Visible;

    if(MainContentPanel->Visible)
    {
		Splitter2->Left = MainContentPanel->Left - 1;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TakeSnapShotBtnClick(TObject *Sender)
{
	takeSnapShot();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ControlBar1StartDrag(TObject *Sender, TDragObject *&DragObject)
{
	this->Align = alNone;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BrowseForFolderClick(TObject *Sender)
{
	//Open Browse for folder dialog
	TButton* b = dynamic_cast<TButton*>(Sender);
    if(b == BrowseForMediaFolderBtn)
    {
        string f = browseForFolder(MediaFolderE->getValue());
        if(!f.size())
        {
            return;
        }

    	MediaFolderE->setValue(f);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PageControlChange(TObject *Sender)
{
	//Check if we need any processing as a tab changes
	TPageControl* pc = dynamic_cast<TPageControl*>(Sender);

    if(pc == MiscPageControl)
    {

    }

    else if(pc == MainPC)
    {
    	if(pc->TabIndex == 2)//Media tab
        {

        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PageControlExit(TObject *Sender)
{
	//Check if we need any processing as a tab changes
	TPageControl* pc = dynamic_cast<TPageControl*>(Sender);

    if(pc == MiscPageControl)
    {
    }
}



void __fastcall TMainForm::MediaFolderEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
    {

    }
}

void __fastcall TMainForm::ThemesMenuClick(TObject *Sender)
{
    TMenuItem* menuItem = dynamic_cast<TMenuItem*>(Sender);
    if(!menuItem)
    {
        return;
    }

	//Uncheck any checked items
	for(int i = 0; i < ThemesMenu->Count; i++)
	{
		TMenuItem* menuItem = ThemesMenu->Items[i];
		if(menuItem && menuItem->Checked)
		{
			menuItem->Checked = false;
		}
	}

	TRegistryForm::writeToRegistry();

	TReplaceFlags rFlags(rfIgnoreCase|rfReplaceAll);
	String styleName = StringReplace(menuItem->Caption, "&", "", rFlags);
	TStyleManager::SetStyle(styleName);

	//Check the menu item
	menuItem->Checked = (TStyleManager::ActiveStyle->Name == styleName) ? true : false;

	//Write to registry
	acu.Style = stdstr(styleName);
	writeStringToRegistry(acu.AppRegistryRoot, "", "Theme", acu.Style);
}

void __fastcall TMainForm::AutoFocusTimerTimer(TObject *Sender)
{
    //Take a snapshot
	if(mCamera1.SaveImage(mFocusController.getSnapShotFileName().c_str()))
    {
    	Log(lError) << "Failed saving focus shot.";
    }
    else
    {
    	Log(lDebug5) << "Saved focus shot.";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::startAFClick(TObject *Sender)
{
    AutoFocusTimer->Enabled = !AutoFocusTimer->Enabled;
	startAF->Caption = AutoFocusTimer->Enabled ? "Stop AF" : "Start AF";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mPBClick(TObject *Sender)
{
    //Getting ROI
    Log(lInfo) << "Setting ROI" ;


}



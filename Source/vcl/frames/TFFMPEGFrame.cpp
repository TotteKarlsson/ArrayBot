#include <vcl.h>
#pragma hdrstop
#include "TFFMPEGFrame.h"
#include <sstream>
#include "dslVCLUtils.h"

#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTPropertyCheckBox"
#pragma resource "*.dfm"
TFFMPEGFrame *FFMPEGFrame;

using namespace std;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TFFMPEGFrame::TFFMPEGFrame(TComponent* Owner)
	: TFrame(Owner),
    mH264Preset("medium")
{}

//---------------------------------------------------------------------------
string TFFMPEGFrame::getOutFileArguments()
{
	stringstream s;
    s << "-vcodec libx264";
    s << " -crf " <<CRFValue->getValue();
	s << " -threads " << FFMPEGThreads->getValue();
    s << " -preset " <<stdstr(PresetCB->Text);
	return  s.str();
}
void TFFMPEGFrame::setupProperties(dsl::IniFile& ini)
{
    mFrameProperties.setSection("FFMPEG_COMPRESSION");
	mFrameProperties.setIniFile(&ini);

   	mFrameProperties.add((BaseProperty*)  &FFMPEGThreads->getProperty()->setup( 	    	    "NUMBER_OF_THREADS",    					1));
	mFrameProperties.add((BaseProperty*)  &mH264Preset.setup( 	    	    					"H264_PRESET",    							"medium"));
	mFrameProperties.add((BaseProperty*)  &CRFValue->getProperty()->setup( 	    	    		"CONSTANT_RATE_FACTOR(CRF)",    		  	20));
	mFrameProperties.add((BaseProperty*)  &DeleteSourceFileCB->getProperty()->setup( 	    	"DELETE_SOURCE_FILE",    					false));
    mFrameProperties.add((BaseProperty*)  &RenameSourceFileCB->getProperty()->setup( 	    	"RENAME_SOURCE_FILE",    					true));

	readFromINI();

}
void TFFMPEGFrame::readFromINI()
{
	mFrameProperties.read();

    //Update UI controls
	FFMPEGThreads->update();
	CRFValue->update();
	DeleteSourceFileCB->update();
	RenameSourceFileCB->update();
    PresetCB->ItemIndex = PresetCB->Items->IndexOf(vclstr(mH264Preset));
}

void TFFMPEGFrame::writeToINI()
{
	mH264Preset = stdstr(PresetCB->Text);

    mFrameProperties.write();
}


void __fastcall TFFMPEGFrame::CBClick(TObject *Sender)
{
	TPropertyCheckBox *cb = dynamic_cast<TPropertyCheckBox *>(Sender);
    if(cb)
    {
    	cb->OnClick(Sender);
    }
}



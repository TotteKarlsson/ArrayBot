#pragma hdrstop
#include "abArrayBot.h"
//---------------------------------------------------------------------------

ArrayBot::ArrayBot(IniFile& ini)
:
mIniFile(ini),
mCoverSlip("CoverSlip Unit", mIniFile),
mWhisker("Whisker Unit", mIniFile)
{

}

ArrayBot::~ArrayBot()
{
}

XYZUnit& ArrayBot::getCoverSlipUnit()
{
	return mCoverSlip;
}

XYZUnit& ArrayBot::getWhiskerUnit()
{
	return mWhisker;
}

void ArrayBot::initialize()
{
	mCoverSlip.initialize();
	mWhisker.initialize();
}




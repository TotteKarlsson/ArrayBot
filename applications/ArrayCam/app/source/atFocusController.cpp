#pragma hdrstop
#include "atFocusController.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;

FocusController::FocusController()
:
mFocusRange(2,24),
mStepFocus(1),
mLiveImagePath("d:\\AC\\live"),
mLiveImageFileName("live.jpg"),
mSharpnessFileName(joinPath(mLiveImagePath, "sharpness.txt")),
mScores()
{
}

FocusController::~FocusController()
{}

string FocusController::getSnapShotFileName()
{
    return joinPath(mLiveImagePath, mLiveImageFileName);
}

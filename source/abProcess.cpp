#pragma hdrstop
#include "abProcess.h"
//---------------------------------------------------------------------------

Process::Process(const string& lbl, ABObject* o)
:
mUnit(o),
mProcessName(lbl),
mDwellTime(0)
{}

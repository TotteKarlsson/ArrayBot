#pragma hdrstop
#include "abProcess.h"
//---------------------------------------------------------------------------

Process::Process(const string& lbl, ABObject* o)
:
mUnit(o),
mLabel(lbl)
{}

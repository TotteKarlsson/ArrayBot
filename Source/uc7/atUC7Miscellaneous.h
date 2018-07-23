#ifndef atUC7MiscellaneousH
#define atUC7MiscellaneousH
#include "atUC7Exporter.h"
#include "Poco/TimeStamp.h"
#include <string>
//---------------------------------------------------------------------------

using std::string;
enum UC7StrokeState {ssBeforeCutting = 0, ssCutting, ssAfterCutting, ssRetracting, ssUndefined};

struct UC7StatusPoint
{
	UC7StatusPoint(const UC7StrokeState& s, Poco::Timestamp t = Poco::Timestamp()) : status(s), time(t){}
	UC7StrokeState		status;
    Poco::Timestamp     time;
};

AT_UC7 string toText(UC7StrokeState state);
#endif

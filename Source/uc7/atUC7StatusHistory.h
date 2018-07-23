#ifndef atUC7StatusHistoryH
#define atUC7StatusHistoryH
#include <deque>
#include "Poco/TimeStamp.h"
#include "atUC7Exporter.h"
#include "atUC7Miscellaneous.h"
//---------------------------------------------------------------------------

using std::deque;


class AT_UC7 UC7StatusHistory
{
	public:
										        UC7StatusHistory();
					        			        ~UC7StatusHistory();

		void							        insert(const UC7StatusPoint& sp);
        void							        clearAll();
        void							        clearCycleData();
        void							        clearHistoryData();
        deque<UC7StatusPoint>			        getCurrentCycle();
        deque< deque<UC7StatusPoint> >	        getHistory();

    protected:
		UC7StatusPoint					        mLastStatus;
    	deque<UC7StatusPoint>			        mPresentCycle;
        deque< deque<UC7StatusPoint> > 	        mHistory;
};

#endif

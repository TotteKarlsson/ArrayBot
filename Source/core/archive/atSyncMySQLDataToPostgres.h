#ifndef atSyncMySQLDataToPostgresH
#define atSyncMySQLDataToPostgresH
#include "atATObject.h"
#include "dslThread.h"
#include <functional>
#include "Poco/Process.h"
#include "Poco/Timespan.h"
//---------------------------------------------------------------------------


class AT_CORE SyncMySQLDataToPostgres : public dsl::Thread
{
	typedef boost::function<void(int*, int*)> Callback;
    public:
								SyncMySQLDataToPostgres();
								~SyncMySQLDataToPostgres();
        void					setAppArguments(const string& args);
		void					assignCallBacks(Callback one, Callback two, Callback three);
        virtual void            run();

    protected:
    	string					mConverterApp;
        string				    mAppArguments;

	    Callback 				onEnter;
	    Callback 				onProgress;
	    Callback 				onExit;
        int						parseOutput(const string& str);
};

#endif

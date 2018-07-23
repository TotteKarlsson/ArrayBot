#ifndef TestPluginWorkerH
#define TestPluginWorkerH
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
//---------------------------------------------------------------------------

class TestPlugin;

class TestPluginWorker : public Poco::Runnable
{
    protected:
        Poco::Thread            mThread;
        TestPlugin&   			mTheHost;

    public:
                                TestPluginWorker(TestPlugin& mTheHost);
        bool                    start(bool useThread = true);
        void                    run();
        bool                    isRunning() const;
};

#endif

#pragma hdrstop
#include "TestPlugin.h"
#include "dslLogger.h"
#include "dslException.h"
//---------------------------------------------------------------------------
//#undef _DEBUG

using Poco::DateTimeFormatter;
using namespace dsl;

//---------------------------------------------------------------------------
TestPlugin::TestPlugin(PluginManager* manager)
:
PluginWithEvents( "TestPlugin",   "Test Plugin With Events", manager),
mAnInteger(1, "An Integer"),
mWorker(*this)
{
    mMetaData.setVersion("1.0.0");

    //Setup the plugins properties
    mProperties.add(&mAnInteger);
    mMetaData.setHint("Testing Plugin");
    mMetaData.setDescription("Multiply an integer with 2");
}

TestPlugin::~TestPlugin()
{}

bool TestPlugin::execute(DSLObject* subject, bool inThread)
{
    Log(lInfo)<<"Testing Plugin";

    //go away and carry out the work in a thread, or not if inThread is false
    return mWorker.start(inThread);
}

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

static int gPluginCount = 0;


namespace dsl
{
    // Plugin factory function
    Plugin* createPlugin(void* manager)
    {
        //allocate a new plugin object and return it
        Plugin* p = new TestPlugin((PluginManager*) manager);
        if(p)
        {
            gPluginCount++;
        }
        return p;
    }

    // Plugin factory function
    bool destroyPlugin(Plugin* p)
    {
        delete p;
        gPluginCount--;
        return true;
	}
}

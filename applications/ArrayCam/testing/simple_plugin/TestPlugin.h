#ifndef TestPluginH
#define TestPluginH
#include "dslPluginWithEvents.h"
#include "dslProperty.h"
#include "TestPluginWorker.h"
#include "TestPluginExporter.h"
//---------------------------------------------------------------------------

using dsl::PluginWithEvents;
using dsl::PluginManager;
using dsl::DSLObject;
using dsl::Property;
using dsl::Plugin;

//This simple plugin has one simple property, "mAnInteger".
//The plugin worker simply multiply this value (initially '1'), with two;
class TestPlugin : public PluginWithEvents
{
    friend class TestPluginWorker;
    public:
                                        TestPlugin(PluginManager* manager);
                                        ~TestPlugin();

                                        //!The first argument allow the client to set
                                        //the initial value of the property, anInt
        bool                            execute(DSLObject* obj, bool inThread);

    private:
        Property<int>                   mAnInteger;

                                        //!The worker is doing the work..
        TestPluginWorker      			mWorker;
};

namespace dsl
{
extern "C"
{
    EXPORTED dsl::Plugin*  	createPlugin(void* manager);
    EXPORTED bool      		destroyPlugin(dsl::Plugin* p);
}

}

#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "dslPlugins.lib")
#pragma comment(lib, "poco_foundation-static.lib")

#endif

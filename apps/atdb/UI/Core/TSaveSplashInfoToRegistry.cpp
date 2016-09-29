#pragma hdrstop
#include "TSaveSplashInfoToRegistry.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TSaveSplashInfoToRegistry::TSaveSplashInfoToRegistry(TForm* f, const string& registryRoot)
:
TSaveFormToRegistry(registryRoot, f)
{

}

TSaveSplashInfoToRegistry::~TSaveSplashInfoToRegistry()
{
}

void TSaveSplashInfoToRegistry::read(const string& sec)
{
    TSaveFormToRegistry::read();

    if(sec.size())
    {
        mRegistryRoot = sec;
    }

    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));

    mShowOnStartup = Registry->ReadBool(mRegistryRoot.c_str(),"ShowOnStartup", true);
}

void  TSaveSplashInfoToRegistry::write()
{
    TSaveFormToRegistry::write();
    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));
    Registry->WriteBool(mRegistryRoot.c_str(), "ShowOnStartup", mShowOnStartup);
}

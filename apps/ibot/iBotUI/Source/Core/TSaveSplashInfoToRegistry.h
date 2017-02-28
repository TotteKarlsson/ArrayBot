#ifndef TSaveSplashInfoToRegistryH
#define TSaveSplashInfoToRegistryH
#include "TSaveFormToRegistry.h"
//---------------------------------------------------------------------------

class PACKAGE TSaveSplashInfoToRegistry : public TSaveFormToRegistry
{
    public:
                                        TSaveSplashInfoToRegistry(TForm* f, const string& registryRoot);
        virtual                         ~TSaveSplashInfoToRegistry();
        virtual void                    read(const string& sec = "");
        virtual void                    write();
        __property bool                 ShowOnStartup = {read=mShowOnStartup, write=mShowOnStartup};

    protected:
        bool                            mShowOnStartup;

};
#endif

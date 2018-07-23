#ifndef TRibbonsDataModuleH
#define TRibbonsDataModuleH
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
//---------------------------------------------------------------------------

class PACKAGE TRibbonsDataModule : public TDataModule
{
    __published:	// IDE-managed Components

    private:

    public:
    		 __fastcall 					TRibbonsDataModule(TComponent* Owner);
		void __fastcall 					afterConnect();
		void __fastcall 					afterDisconnect();
};

extern PACKAGE TRibbonsDataModule *RibbonsDataModule;
#endif

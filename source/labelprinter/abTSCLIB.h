#ifndef abTSCLIBH
#define abTSCLIBH
#include <string>
#include <windows.h>
#include "abExporter.h"
//---------------------------------------------------------------------------

using std::string;
typedef int (__stdcall *f_void)();

class AB_CORE TSCLIB
{
	public:
							TSCLIB();
							~TSCLIB();
        bool                load(const string& dllPath);
		bool                unload();

							//Exposed functions
        void				about();


    private:
        HINSTANCE			mDLLHandle;

        //Function pointers
        f_void				mAboutFunc;
};

#endif

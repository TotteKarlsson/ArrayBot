#ifndef atTSCLIBH
#define atTSCLIBH
#include <string>
#include <windows.h>
#include "atCoreExporter.h"
#include "atATObject.h"
#include "dslStringList.h"


//---------------------------------------------------------------------------
using std::string;
using dsl::StringList;
//Function pointers
typedef int (__stdcall *f_int_void)();
typedef int (__stdcall *f_int_cchar)(const char*);
typedef int (__stdcall *f_int_cchar_cchar)(const char*, const char*);
typedef int (__stdcall *f_BarCode)(		 const char*, const char*, const char*, const char*, const char*,
								   		 const char*, const char*, const char*, const char*);

typedef int (__stdcall *f_PrinterFont)(	 const char*, const char*, const char*, const char*, const char*,
										 const char*, const char*);

typedef int (__stdcall *f_Setup)(		 const char*, const char*, const char*, const char*, const char*,
										 const char*, const char*);

typedef int (__stdcall *f_WinFont)(		 int, int, int, int, int, int, const char*, const char*);

struct BarcodePrintParameters
{
	StringList command;
};

namespace at
{
    //!The TSCLIB class wraps functions that are present in the tsclib.dll module. These functions
    //!allow printing custom labels on a TSC printer
    class AT_CORE TSCLIB : public ATObject
    {
    	public:
    							                TSCLIB();
    							                ~TSCLIB();
            bool                                load(const string& dllPath);

            bool								printCoverSlipLabel(BarcodePrintParameters& p, const string& content, int copies = 1);
            bool								printFreshBatchLabel(const string& content, int copies = 1);

            bool						        isLoaded();
    		bool                                unload();

    							                //Exposed functions
            int					                about();

        	int 				                openport(const char* printername);

    		int 				                barcode(const char *x,		const char *y,		const char *type,
        			    		                		const char *height,	const char *readable,	const char *rotation,
        			    		                		const char *narrow,	const char *wide,		const char *code);

        	int 				                clearbuffer();
    	  	int 				                closeport();
        	int 				                downloadpcx(const char *filename,const char *image_name);
    	  	int 				                formfeed();
        	int 				                nobackfeed();
        	int 				                printerfont(const char *x, 	const char *y, 	const char *fonttype, const char *rotation, const char *xmul,	const char *ymul,	const char *text);

        	int 				                printlabel(const char *set, const char *copy);
        	int 				                sendcommand(const char* printercommand);

        	int 				                setup(const char *width,	const char *height,  const char *speed,	const char *density,
        			                                  const char *sensor,	const char *vertical,const char *offset);

        	int 				                windowsfont(int x, 				int y, 			int fontheight,
        						                			int rotation,		int fontstyle,	int fontunderline,
        						                			const char *szFaceName,	const char *content);


        private:
            HINSTANCE			                mDLLHandle;
            f_int_void	   		                mAboutFunc;
            f_int_cchar			                mOpenPort;
            f_BarCode			                mBarCode;
            f_int_void			                mClearBuffer;
            f_int_void			                mClosePort;
            f_int_cchar_cchar		            mDownLoadPCX;
            f_int_void			                mFormFeed;
            f_int_void			                mNoBackFeed;
    		f_PrinterFont		                mPrinterFont;
            f_int_cchar_cchar		            mPrintLabel;
           	f_int_cchar			                mSendCommand;
    		f_Setup            	                mSetup;
        	f_WinFont			                mWindowsFont;

            bool						        assignFunctions();

    };

}
#endif

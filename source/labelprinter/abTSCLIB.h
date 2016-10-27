#ifndef abTSCLIBH
#define abTSCLIBH
#include <string>
#include <windows.h>
#include "abExporter.h"
//---------------------------------------------------------------------------

using std::string;
//Function pointers
typedef int (__stdcall *f_int_void)();
typedef int (__stdcall *f_int_char)(char*);
typedef int (__stdcall *f_int_char_char)(char*, char*);
typedef int (__stdcall *f_BarCode)(		 char*, char*, char*, char*, char*,
								   		 char*, char*, char*, char*);

typedef int (__stdcall *f_PrinterFont)(	 char*, char*, char*, char*, char*,
										 char*, char*);

typedef int (__stdcall *f_Setup)(		 char*, char*, char*, char*, char*,
										 char*, char*);

typedef int (__stdcall *f_WinFont)(		 int, int, int, int, int, int, char*, char*);

//!The TSCLIB class wraps functions that are present in the tsclib.dll module. These functions
//allow printing custom labels on a TSC printer
class AB_CORE TSCLIB
{
	public:
							        TSCLIB();
							        ~TSCLIB();
        bool                        load(const string& dllPath);
        bool						isLoaded();
		bool                        unload();

							        //Exposed functions
        int					        about();

    	int 				        openport(char* printername);

		int 				        barcode(char *x,		char *y,		char *type,
    			    		        		char *height,	char *readable,	char *rotation,
    			    		        		char *narrow,	char *wide,		char *code);

    	int 				        clearbuffer();

	  	int 				        closeport();

    	int 				        downloadpcx(char *filename,char *image_name);

	  	int 				        formfeed();

    	int 				        nobackfeed();

    	int 				        printerfont(char *x, 	char *y, 	char *fonttype, char *rotation,
        					        			char *xmul,	char *ymul,	char *text);

    	int 				        printlabel(char *set, char *copy);

    	int 				        sendcommand(char *printercommand);

    	int 				        setup(char *width,	char *height,  char *speed,	char *density,
    			                          char *sensor,	char *vertical,char *offset);

    	int 				        windowsfont(int x, 				int y, 			int fontheight,
    						        			int rotation,		int fontstyle,	int fontunderline,
    						        			char *szFaceName,	char *content);


    private:
        HINSTANCE			        mDLLHandle;
        f_int_void	   		        mAboutFunc;
        f_int_char			        mOpenPort;
        f_BarCode			        mBarCode;
        f_int_void			        mClearBuffer;
        f_int_void			        mClosePort;
        f_int_char_char		        mDownLoadPCX;
        f_int_void			        mFormFeed;
        f_int_void			        mNoBackFeed;
		f_PrinterFont		        mPrinterFont;
        f_int_char_char		        mPrintLabel;
       	f_int_char			        mSendCommand;
		f_Setup            	        mSetup;
    	f_WinFont			        mWindowsFont;

        bool						assignFunctions();

};

#endif

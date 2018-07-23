#ifndef ArrayCamUtilitiesH
#define ArrayCamUtilitiesH
#include <windows.h>
#include <string>
//---------------------------------------------------------------------------

using std::string;

class ApplicationUtilities
{
	public:
    			                            ApplicationUtilities(const string& appName, const string& regRoot, const string& appVersion);
    virtual 	                            ~ApplicationUtilities();
    HANDLE 		                            AppMutex;
	string	   	                            AppName;
	string	   	                            AppRegistryRoot;
    string		                            AppVersion;
    string		                            AppDataFolder;
    string 		                            LogFileName;
  	string		                            LogFileLocation;
  	string		                            Style;

    string                                  RestartMutexName;
    HWND                                    OtherAppWindow;
    bool       	                            AppIsStartingUp;
    bool       	                            AppIsClosing;

    void		                            init();
	bool		                            setupLogging();
	bool		                            closeLogFile();
	bool	                                otherInstanceIsRunning();
};

class ArrayCamUtilities : public ApplicationUtilities
{
    public:
											ArrayCamUtilities();
											~ArrayCamUtilities();
    protected:

    private:

};
#endif

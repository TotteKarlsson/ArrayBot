#include <vcl.h>
#pragma hdrstop
#include "UIUtilities.h"
#include "dslLogger.h"
//#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "dslRestartApplicationUtils.h"
#include "abApplicationMessages.h"
//#include "dslMoleculixException.h"
//#include "Poco/DateTimeFormatter.h"
#pragma package(smart_init)

using namespace dsl;

//---------------------------------------------------------------------------
bool sendAppMessage(ApplicationMessageEnum msgID, void* s)
{
	if(!Application || !Application->MainForm || !Application->MainForm->HandleAllocated())
    {
    	Log(lError) << "Failed to get a valid handle when trying to send application message";
        return false;
    }
    HWND h = Application->MainForm->Handle;

	AppMessageStruct data;
	data.mMessageEnum = msgID;
	data.mData = s;

	LRESULT res =  SendStructMessage(h, UWM_MESSAGE, 0, &data);
	if(res)
	{
		Log(lError) << "Sending message: "<<msgID<<" was unsuccesful";
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------
void setupApplicationTheme(const string& appRegRoot, string& theme)
{
	if(dsl::checkForCommandLineFlag("-Theme="))
	{
		string cmdLine = stdstr(GetCommandLineA());
		//User is changing the theme.
		//Parse the command line
		StringList paras(cmdLine,'-');

		//Create iniKeys for easy parsing
		for(uint i = 0; i < paras.size(); i++)
		{
			string record = paras[i];
			IniKey aKey(record);
			if(aKey.mKey == "Theme")
			{
				 theme = aKey.mValue;
			}
		}
	}
	else
	{
		//Read from registry
		theme = readStringFromRegistry(appRegRoot, "", "Theme", theme);
	}

	if(theme.size())
	{
		try
		{
			if(theme == "Windows")
			{
				//Do nothing..
			}
			else
			{
				TStyleManager::TrySetStyle(theme.c_str());
			}
		}
		catch(...)
		{
			//Do nothing
		}
	}
}

void loadStyles()
{
	string themeFolder("styles");
	themeFolder = joinPath(getCWD(), themeFolder);
	if(DirectoryExists(themeFolder.c_str()))
	{
		StringList list = getFilesInDir(themeFolder, "vsf");
		for(uint i = 0; i < list.size(); i++)
		{
			string styleFile(list[i]);
			try
			{
				if(TStyleManager::IsValidStyle(vclstr(styleFile)))
				{
					TStyleManager::LoadFromFile(vclstr(styleFile));
				}
			}
			catch(...)
			{
				MessageDlg("Bad theme file", mtWarning, TMsgDlgButtons() << mbOK, 0);
			}
		}
	}
}

void setupLogging(const string& logFileLocation, const string& logFileName)
{
	//Get Application folder
	if(!folderExists(logFileLocation))
	{
		createFolder(logFileLocation);
	}

	string fullLogFileName(joinPath(logFileLocation, logFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
    dsl::gLogger.setLogLevel(lInfo);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;
	Log(lInfo) << "The Logger was setup";
}


#pragma hdrstop
#include <Winapi.Messages.hpp> //Have to put this one first :(
#include "UIUtilities.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "mtkRestartApplicationUtils.h"
#include "abApplicationMessages.h"
#include "mtkMoleculixException.h"
#include "Poco/DateTimeFormatter.h"

using namespace mtk;
extern string 	gLogFileLocation;
extern string 	gLogFileName;
extern string 	gDefaultAppTheme;
extern string 	gApplicationRegistryRoot;
extern string 	gAppDataFolder;

bool sendAppMessage(ApplicationMessageEnum msgID, void* s)
{
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
void setupApplicationTheme()
{
	if(mtk::checkForCommandLineFlag("-Theme="))
	{
		string cmdLine = stdstr(GetCommandLineA());
		//User is changing the theme.
		//Parse the command line
		StringList paras(cmdLine,'-');

		//Create iniKeys for easy parsing
		for(int i = 0; i < paras.size(); i++)
		{
			string record = paras[i];
			IniKey aKey(record);
			if(aKey.mKey == "Theme")
			{
				 gDefaultAppTheme = aKey.mValue;
			}
		}
	}
	else
	{
		//Read from registry
		gDefaultAppTheme = readStringFromRegistry(gApplicationRegistryRoot, "", "Theme", gDefaultAppTheme);
	}

	if(gDefaultAppTheme.size())
	{
		try
		{
			if(gDefaultAppTheme == "Windows")
			{
				//Do nothing..
			}
			else
			{
				TStyleManager::TrySetStyle(gDefaultAppTheme.c_str());
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
		for(int i = 0; i < list.size(); i++)
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

void setupLogging()
{
	//Get Application folder
	if(!folderExists(gAppDataFolder))
	{
		createFolder(gAppDataFolder);
	}

	gLogFileLocation = gAppDataFolder;

	string fullLogFileName(joinPath(gLogFileLocation, gLogFileName));
	clearFile(fullLogFileName);
	mtk::gLogger.logToFile(fullLogFileName);
    mtk::gLogger.setLogLevel(lInfo);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;
	Log(lInfo) << "Logger was setup";
}


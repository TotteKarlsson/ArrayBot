#pragma hdrstop
#include <Winapi.Messages.hpp> //Have to put this one first :(
#include "UIUtilities.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "dslRestartApplicationUtils.h"
#include "abApplicationMessages.h"
#include "Poco/DateTimeFormatter.h"

using namespace dsl;
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
	dsl::gLogger.logToFile(fullLogFileName);
    dsl::gLogger.setLogLevel(lInfo);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;
	Log(lInfo) << "Logger was setup";
}


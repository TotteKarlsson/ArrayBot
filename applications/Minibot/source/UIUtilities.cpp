#pragma hdrstop
#include <Winapi.Messages.hpp> //Have to put this one first :(
#include "UIUtilities.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "dslRestartApplicationUtils.h"
#include "abApplicationMessages.h"
#include "dslException.h"
#include "Poco/DateTimeFormatter.h"
#pragma package(smart_init)

using namespace dsl;

//---------------------------------------------------------------------------
bool sendAppMessage(ApplicationMessageEnum msgID, void* s)
{
	if(!Application || !Application->MainForm || !Application->MainForm->Handle)
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

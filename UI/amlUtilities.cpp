#pragma hdrstop
#include <Winapi.Messages.hpp> //Have to put this one first :(
#include "amlUtilities.h"
#include "mtkLogger.h"
#include "mtkUtils.h"
#include "mtkVCLUtils.h"
#include "mtkRestartApplicationUtils.h"
#include "amlApplicationMessages.h"
#include "mtkMoleculixException.h"
#include "Poco/DateTimeFormatter.h"

using namespace mtk;
extern string 	gLogFileLocation;
extern string 	gLogFileName;
extern string 	gDefaultAppTheme;
extern string 	gApplicationRegistryRoot;

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
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "Amalytico");
	if(!folderExists(fldr))
	{
		createFolder(fldr);
	}

	gLogFileLocation = fldr;

	string fullLogFileName(joinPath(gLogFileLocation, gLogFileName));
	clearFile(fullLogFileName);
	mtk::gLogger.logToFile(fullLogFileName);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = false;
	LogOutput::mUseLogTabs = false;
	Log(lInfo) << "Logger was setup";
}

StringList fixStatesOrRegionsData(const StringList& orders)
{
	//This functions convert every state or region to its proper abbreviation
	//e.g. Washington -> WA
	StringList result;

	for(int i = 0; i < orders.count(); i++)
	{
		StringList order(orders[i], '|');

		//State is element 5 (This will need to change in order to allow
		//Amazon data records to change in the future)
		order[5] = updateStateOrRegionData(order[5]);

		result.append(order.asString('|'));
	}

	return result;
}

string updateStateOrRegionData(const string& sor)
{

    if(compareNoCase("Alabama", sor) || compareNoCase("AL", sor))
    {
        return "AL";
    }
    else if(compareNoCase("Alaska", sor) || compareNoCase("AK", sor))
    {
        return "AK";
    }
    else if(compareNoCase("Arizona", sor) || compareNoCase("AZ", sor))
    {
        return "AZ";
    }
    else if(compareNoCase("Arkansas", sor) || compareNoCase("AR", sor))
    {
        return "AR";
    }
    else if(compareNoCase("California", sor) || compareNoCase("CA", sor))
    {
        return "CA";
    }
    else if(compareNoCase("Colorado", sor) || compareNoCase("CO", sor))
    {
        return "CO";
    }
    else if(compareNoCase("Connecticut", sor) || compareNoCase("CT", sor))
    {
        return "CT";
    }
    else if(compareNoCase("Delaware", sor) || compareNoCase("DE", sor))
    {
        return "DE";
    }
    else if(compareNoCase("Florida", sor) || compareNoCase("FL", sor))
    {
        return "FL";
    }
    else if(compareNoCase("Georgia", sor) || compareNoCase("GA", sor))
    {
        return "GA";
    }
    else if(compareNoCase("Hawaii", sor) || compareNoCase("HI", sor))
    {
        return "HI";
    }
    else if(compareNoCase("Idaho", sor) || compareNoCase("ID", sor))
    {
        return "ID";
    }
    else if(compareNoCase("Illinois", sor) || compareNoCase("IL", sor))
    {
        return "IL";
    }
    else if(compareNoCase("Indiana", sor) || compareNoCase("IN", sor))
    {
        return "IN";
    }
    else if(compareNoCase("Iowa", sor) || compareNoCase("IA", sor))
    {
        return "IA";
    }
    else if(compareNoCase("Kansas", sor) || compareNoCase("KS", sor))
    {
        return "KS";
    }
    else if(compareNoCase("Kentucky", sor) || compareNoCase("KY", sor))
    {
        return "KY";
    }
    else if(compareNoCase("Louisiana", sor) || compareNoCase("LA", sor))
    {
        return "LA";
    }
    else if(compareNoCase("Maine", sor) || compareNoCase("ME", sor))
    {
        return "ME";
    }
    else if(compareNoCase("Maryland", sor) || compareNoCase("MD", sor))
    {
        return "MD";
    }
    else if(compareNoCase("Massachusetts", sor) || compareNoCase("MA", sor))
    {
        return "MA";
    }
    else if(compareNoCase("Michigan", sor) || compareNoCase("MI", sor))
    {
        return "MI";
    }
    else if(compareNoCase("Minnesota", sor) || compareNoCase("MN", sor))
    {
        return "MN";
    }
    else if(compareNoCase("Mississippi", sor) || compareNoCase("MS", sor))
    {
        return "MS";
    }
    else if(compareNoCase("Missouri", sor) || compareNoCase("MO", sor))
    {
        return "MO";
    }
    else if(compareNoCase("Montana", sor) || compareNoCase("MT", sor))
    {
        return "MI";
    }
    else if(compareNoCase("Nebraska", sor) || compareNoCase("NE", sor))
    {
        return "NE";
    }
    else if(compareNoCase("Nevada", sor) || compareNoCase("NV", sor))
    {
        return "NV";
    }
    else if(compareNoCase("New Hampshire", sor) || compareNoCase("NH", sor))
    {
        return "NH";
    }
    else if(compareNoCase("New Jersey", sor) || compareNoCase("NJ", sor))
    {
        return "NJ";
    }
    else if(compareNoCase("New Mexico", sor) || compareNoCase("NM", sor))
    {
        return "NM";
    }
    else if(compareNoCase("New York", sor) || compareNoCase("NY", sor))
    {
        return "NY";
    }
    else if(compareNoCase("North Carolina", sor) || compareNoCase("NC", sor))
    {
        return "NC";
    }
    else if(compareNoCase("North Dakota", sor) || compareNoCase("ND", sor))
    {
        return "ND";
    }
    else if(compareNoCase("Ohio", sor) || compareNoCase("OH", sor))
    {
        return "OH";
    }
    else if(compareNoCase("Oklahoma", sor) || compareNoCase("OK", sor))
    {
        return "OK";
    }
    else if(compareNoCase("Oregon", sor) || compareNoCase("OR", sor))
    {
        return "OR";
    }
    else if(compareNoCase("Pennsylvania", sor) || compareNoCase("PA", sor))
    {
        return "PA";
    }
    else if(compareNoCase("Rhode Island", sor) || compareNoCase("RI", sor))
    {
        return "RI";
    }
    else if(compareNoCase("South Carolina", sor) || compareNoCase("SC", sor))
    {
        return "SC";
    }
    else if(compareNoCase("South Dakota", sor) || compareNoCase("SD", sor))
    {
        return "SD";
    }
    else if(compareNoCase("Tennessee", sor) || compareNoCase("TN", sor))
    {
        return "TN";
    }
    else if(compareNoCase("Texas", sor) || compareNoCase("TX", sor))
    {
        return "TX";
    }
    else if(compareNoCase("Utah", sor) || compareNoCase("UT", sor))
    {
        return "UT";
    }
    else if(compareNoCase("Vermont", sor) || compareNoCase("VT", sor))
    {
        return "VT";
    }
    else if(compareNoCase("Virginia", sor) || compareNoCase("VA", sor))
    {
        return "VA";
    }
    else if(compareNoCase("Washington", sor) || compareNoCase("WA", sor))
    {
        return "WA";
    }
    else if(compareNoCase("West Virginia", sor) || compareNoCase("WV", sor))
    {
        return "WV";
    }
    else if(compareNoCase("Wisconsin", sor) || compareNoCase("WI", sor))
    {
        return "WI";
    }
    else if(compareNoCase("Wyoming", sor) || compareNoCase("WY", sor))
    {
        return "WY";
    }
	else
	{
		Log(lWarning) <<"The state or region "<<sor<<" do not have a filter";
		return sor;
	}
}

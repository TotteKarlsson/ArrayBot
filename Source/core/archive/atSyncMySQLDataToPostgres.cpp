#pragma hdrstop
#include "atSyncMySQLDataToPostgres.h"
#include "dslLogger.h"
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include <fstream>
#include "dslFileUtils.h"
#include "dslMathUtils.h"
#include "Poco/Path.h"
#include "Poco/File.h"
//---------------------------------------------------------------------------
using namespace Poco;
using namespace dsl;
using Poco::Path;

SyncMySQLDataToPostgres::SyncMySQLDataToPostgres()
:
mConverterApp("s2pagent.exe"),
mAppArguments("")
{}

SyncMySQLDataToPostgres::~SyncMySQLDataToPostgres()
{}

void SyncMySQLDataToPostgres::assignCallBacks(Callback one, Callback two, Callback three)
{
	onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}

void SyncMySQLDataToPostgres::setAppArguments(const string& args)
{
	mAppArguments = args;
}

void SyncMySQLDataToPostgres::run()
{
	mIsStarted = true;
    if(onEnter)
    {
    	onEnter(0,0);
    }

	mIsRunning = true;

	try
    {
        //Setup arguments
        StringList args;
        args.append(mAppArguments);
        Log(lInfo) << "Running syncMySQL to Postgres with arguments: " << mAppArguments;

        //Capture output
        Pipe outPipe;

		//Capture stdout and stderr to outPipe
        ProcessHandle ph = Process::launch(mConverterApp, args, NULL, &outPipe, &outPipe);

        //Use stream objects to read and write to the pipes
        PipeInputStream istr(outPipe);

        string s;
		int progress(0);
        int c = istr.get();
       	bool isBeingKilled(false);
        while (c != -1 && isBeingKilled == false)
        {
            s += (char) c;
            if(c == '\n' || c == '\r')
            {
            	progress = parseOutput(s);
                Log(lDebug5) << s;

                if(onProgress && s.size() > 1)
                {
	                onProgress((int*) &s, 0);
                }
                s.clear();
            }

            c = istr.get();
            if(mIsTimeToDie)
            {
            	Log(lInfo) << "Killing Sync process..";
            	Process::kill(ph.id());
				isBeingKilled = true;
            }
        }

		if(!mIsTimeToDie)
        {
	        int rc = ph.wait();
	        Log(lInfo) <<"Process Exit Code: "<<rc;
        }
        else
        {
	        Log(lInfo) <<"Process was forcibly killed.";
        }
    }
    catch(...)
    {
		Log(lError) << "Unhandled exception..";
    }

	Log(lInfo) << "Exiting thread..";

    if(onExit)
    {
    	onExit(0,0);
    }

	mIsRunning = false;
	mIsFinished = true;
}

int SyncMySQLDataToPostgres::parseOutput(const string& s)
{
	//    Log(lDebug5) << "Parsing string: "<<s;
    //Check and parse string
   	return (s.size()) ? 0 : 1;
}


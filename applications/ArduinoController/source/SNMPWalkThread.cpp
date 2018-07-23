#pragma hdrstop
#include "SNMPWalkThread.h"
#include "dslLogger.h"
#include "core/atExceptions.h"
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "dslException.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

//using Poco::Path;
using namespace Poco;
using namespace dsl;

SNMPWalkThread::SNMPWalkThread(const string& exe)
:
mExecutable(exe),
mIP("192.168.123.123"),
mOIDRoot("1.3.6.1.4")
{}

void SNMPWalkThread::assignCallBacks(Callback one, Callback two, Callback three)
{
	onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}

void SNMPWalkThread::setWalkParameters(const string& ip, const string& oidRoot)
{
	mIP = ip;
    mOIDRoot = oidRoot;
}

void SNMPWalkThread::run()
{
	mIsStarted = true;
    if(onEnter)
    {
    	onEnter(0,0);
    }

	mIsRunning = true;

	try
    {
    	if(!fileExists(mExecutable))
        {
	        Log(lError) << "The executable: " << mExecutable << " don't exists";
            const ATException ae(string("The executable: ") +  string(" don't exists"));
            throw(ae);
        }

        //Setup arguments
        StringList args;
        args.append("-v 2c -c public " + mIP);
        args.append(mOIDRoot);
        Log(lDebug5) << "SNMP WALK arguments: " << args.asString();

        //Capture output
        Pipe outPipe;

		//Capture stdout and stderr to outPipe
        ProcessHandle ph = Process::launch(mExecutable, args, NULL, &outPipe, &outPipe);

        //Use stream objects to read and write to the pipes
        PipeInputStream istr(outPipe);


		int progress(0);
        int c = istr.get();
        bool exitRequested(false);

        //Read all three values before reporting progress
        string s;
        StringList walk;
        while (!istr.eof())
        {

            s += (char) c;
            if((c == '\n' || c == '\r') && s.size() > 1)
            {
            	walk.append(s);
                s.clear();
            }

            c = istr.get();
            if(mIsTimeToDie && !exitRequested)
            {
                exitRequested = true;
            }
        }

        walk.reverse();
        Log(lInfo) << walk.asString();
        int rc = ph.wait();
        Log(lDebug5) <<"RC: "<<rc;
    }
    catch(...)
    {
		Log(lError) << "Unhandled exception..";
    }

	Log(lInfo) << "Exiting WALK SNMP Thread..";

    if(onExit)
    {
    	onExit(0,0);
    }

	mIsRunning = false;
	mIsFinished = true;
}

//Parsing text can be ugly..
int SNMPWalkThread::parseOutput(const string& s)
{
	//Check string for MIB content
    try
    {

        return 0;
	}
	catch(const DSLException& e)
   	{
        Log(lError) << " There was a problem: "<<e.what();
   	}

}


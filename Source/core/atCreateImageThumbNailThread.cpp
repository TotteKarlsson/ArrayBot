#pragma hdrstop
#include "atCreateImageThumbNailThread.h"
#include <fstream>
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
//#include "dslMathUtils.h"

//---------------------------------------------------------------------------
using namespace Poco;
using namespace dsl;
using Poco::Path;

CreateImageThumbNailThread::CreateImageThumbNailThread()
:
mFFMPEGLocation("ffmpeg.exe")
{}

CreateImageThumbNailThread::~CreateImageThumbNailThread()
{}

void CreateImageThumbNailThread::setFFMPEGLocation(const string& loc)
{
	mFFMPEGLocation = loc;
}

void CreateImageThumbNailThread::setInputFile(const string& f)
{
	mInputFileName = f;
}

string CreateImageThumbNailThread::getInputFileName()
{
	return mInputFileName;
}

void CreateImageThumbNailThread::assignCallBacks(Callback one, Callback two, Callback three)
{
	onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}

void CreateImageThumbNailThread::run()
{
	mIsStarted = true;
    if(onEnter)
    {
    	onEnter(0,0);
    }

	mIsRunning = true;

	try
    {
        string outputFolder(getFilePath(mInputFileName));
        string outFile(joinPath(outputFolder, getFileNameNoExtension(mInputFileName)));
        outFile += "_tn.jpg";

        if(fileExists(outFile))
        {
            removeFile(outFile);
            Log(lWarning) << "Removed file: "<<outFile;
        }

        //Setup arguments
        StringList args;
        args.append("-i " + mInputFileName);
        args.append("-filter scale=-1:100 -y");
        args.append(outFile);

        //Capture output
        Pipe outPipe;

		//Capture stdout and stderr to outPipe
        ProcessHandle ph = Process::launch(mFFMPEGLocation, args, NULL, &outPipe, &outPipe);

        //Use stream objects to read and write to the pipes
        PipeInputStream istr(outPipe);

        string s;
		int progress(0);
        int c = istr.get();
        while (c != -1)
        {
            s += (char) c;
            if(c == '\n' || c == '\r')
            {
            	progress = parseFFMPEGOutput(s);
                Log(lDebug5) << s;
                s.clear();
                if(onProgress && progress > 0)
                {
	                onProgress(progress, 0);
                }
            }

            c = istr.get();
        }

        int rc = ph.wait();
        Log(lInfo) <<"RC: "<<rc;
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

int CreateImageThumbNailThread::parseFFMPEGOutput(const string& s)
{
	//    Log(lDebug5) << "Parsing string: "<<s;
    //Check and parse string
   	return (s.size()) ? 0 : 1;
}



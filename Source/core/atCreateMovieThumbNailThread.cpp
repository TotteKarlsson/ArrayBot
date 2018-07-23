#pragma hdrstop
#include "atCreateMovieThumbNailThread.h"
#include <fstream>
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "dslLogger.h"
#include "dslFileUtils.h"

//---------------------------------------------------------------------------
using namespace Poco;
using namespace dsl;
using Poco::Path;

CreateMovieThumbNailThread::CreateMovieThumbNailThread()
:
mFFMPEGLocation("ffmpeg.exe"),
mFFMPEGOutFileArguments("-qscale:v 31 -vframes 1")
{}

CreateMovieThumbNailThread::~CreateMovieThumbNailThread()
{}


void CreateMovieThumbNailThread::setFFMPEGLocation(const string& loc)
{
	mFFMPEGLocation = loc;
}

void CreateMovieThumbNailThread::setInputFile(const string& f)
{
	mInputFileName = f;
}

string CreateMovieThumbNailThread::getInputFileName()
{
	return mInputFileName;
}

void CreateMovieThumbNailThread::assignCallBacks(Callback one, Callback two, Callback three)
{
	onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}

void CreateMovieThumbNailThread::setFFMPEGOutFileArguments(const string& args)
{
	mFFMPEGOutFileArguments = args;
}

void CreateMovieThumbNailThread::run()
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
        outFile += ".jpg";

        if(fileExists(outFile))
        {
            removeFile(outFile);
            Log(lWarning) << "Removed file: "<<outFile;
        }

        //Setup arguments
        StringList args;
        args.append("-i " + mInputFileName);
        args.append(mFFMPEGOutFileArguments);
        args.append(outFile);
        Log(lDebug5) << "OutputFile arguments: " << mFFMPEGOutFileArguments;

        //Capture output
        Pipe outPipe;

        //Tell process to start/stop stuff
        Pipe inPipe;

		//Capture stdout and stderr to outPipe
        ProcessHandle ph = Process::launch(mFFMPEGLocation, args, &inPipe, &outPipe, &outPipe);

        //Use stream objects to read and write to the pipes
        PipeInputStream istr(outPipe);
		PipeOutputStream ostr(inPipe);

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

int CreateMovieThumbNailThread::parseFFMPEGOutput(const string& s)
{
	//    Log(lDebug5) << "Parsing string: "<<s;
    //Check and parse string
   	return (s.size()) ? 0 : 1;
}



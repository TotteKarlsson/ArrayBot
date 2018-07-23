#pragma hdrstop
#include "atHDMIStreamerProcess.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "Poco/File.h"
using namespace dsl;
using namespace Poco;

//---------------------------------------------------------------------------
HDMIStreamerProcess::HDMIStreamerProcess(const string& bmExecutable, const string& pipeName)
:
mBMStreamerExecutable(bmExecutable),
mStartStreamingRequest(false),
mStopStreamingRequest(false),
mIsStreaming(false),
mOutStream(NULL),
mBitRate(20000)
{}


HDMIStreamerProcess::~HDMIStreamerProcess()
{
	delete mOutStream;
}

void HDMIStreamerProcess::assignCallBacks(Callback one, Callback two, Callback three)
{
	onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}

void HDMIStreamerProcess::assignCallBacks2(Callback one, Callback two, Callback three)
{
	onEnter2 		= one;
    onProgress2 	= two;
    onExit2 		= three;
}

void HDMIStreamerProcess::exit()
{
	this->stopStreaming();
    dsl::Thread::stop();
}

bool HDMIStreamerProcess::startStreaming()
{
	if(!this->isRunning())
    {
    	dsl::Thread::run();
    }

	return false;
}

bool HDMIStreamerProcess::stopStreaming()
{
	if(mOutStream && mIsTimeToDie == false)
    {
    	(*mOutStream) << std::string(1, 'q');
    	(*mOutStream) << endl;
    }

    //Quit thread
    mIsTimeToDie = true;
	return false;
}

bool HDMIStreamerProcess::startRecording(const string& fName, int bitRate)
{
	Log(lInfo) << "Starting recording HDMI using outputFileName = "<<fName<<" and bitrate = "<<bitRate;
	//Change file name
    mOutputFileName = fName;
    mBitRate = bitRate;

	//Make sure output folder exists, if not create it
    if(!folderExists(getFilePath(fName)))
    {
		string folder(getFilePath(fName));
        Log(lInfo) << "Creating folder: " <<folder;
		if(!createFolder(folder))
        {
	        Log(lError) << "Failed creating folder: " <<folder;
	        Log(lError) << "Failed starting HDMI streamer";
        	return false;
        }
    }

	return startStreaming();
}

bool HDMIStreamerProcess::stopRecording()
{
	stopStreaming();
	return false;
}

void HDMIStreamerProcess::run()
{
	mIsStarted = true;
    if(onEnter)
    {
    	onEnter(0,0);
    }

    if(onEnter2)
    {
    	onEnter2(0,0);
    }

	mIsRunning = true;

	try
    {
        //Setup arguments
        StringList args;
        args.append("-a");		//Start recording immediately
        args.append("-b" + dsl::toString(mBitRate));
        args.append("-f" + mOutputFileName);


        Log(lInfo) <<"Entered streamerthread";
        Log(lInfo) <<"Calling "<<mBMStreamerExecutable<<" using args "<<args.asString();
        //Capture output
        Pipe outPipe;

        //Tell process to start/stop stuff
        Pipe inPipe;

		//Capture stdout and stderr to outPipe
        ProcessHandle ph = Process::launch(mBMStreamerExecutable, args, &inPipe, &outPipe, &outPipe);

        //Use stream objects to read and write to the pipes
        PipeInputStream istr(outPipe);
		mOutStream = new PipeOutputStream(inPipe);

        string s;
		int progress(0);
        int c = istr.get();
        bool exitRequested(false);

        while(!exitRequested)
        {
            s += (char) c;
            if(c == '\n' || c == '\r')
            {
            	progress = parseOutput(s);
                Log(lDebug5) << s;
                s.clear();

                Poco::File aFile(mOutputFileName);
                long sz(0);
                if(aFile.exists())
                {
                    sz = aFile.getSize();
                }

                if(onProgress)
                {
	                onProgress(sz, 0);
                }

                if(onProgress2)
                {
	                onProgress2(sz, 0);
                }
            }

           	c = istr.get();

			if(mIsTimeToDie)
            {
				exitRequested = true;
            }
        }

        //Thread is exiting
        //Waith for managed process to exit
        int ec = ph.wait();
        Log(lInfo) <<"Streamer thread exited with code: "<<ec;
    }
    catch(...)
    {
		Log(lError) << "Unhandled exception..";
    }

    if(onExit)
    {
    	onExit(0,0);
    }

    if(onExit2)
    {
    	onExit2(0,0);
    }

	mIsRunning = false;
	mIsFinished = true;
}

int HDMIStreamerProcess::parseOutput(const string& s)
{
    Log(lDebug5) << "Parsing string: "<<s;
    //Check and parse string
   	return (s.size()) ? 0 : 1;
}

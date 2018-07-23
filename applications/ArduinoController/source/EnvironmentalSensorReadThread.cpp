#pragma hdrstop
#include "EnvironmentalSensorReadThread.h"
#include "dslLogger.h"
#include "core/atExceptions.h"
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "dslException.h"
//using Poco::Path;
using namespace Poco;

//---------------------------------------------------------------------------

using namespace dsl;

EnvironmentalSensorReadThread::EnvironmentalSensorReadThread(const string& exe)
:
mExecutable(exe),
mAlias(""),
mIsPresent(false),
mTemperature(0),
mHumidity(0),
mDewPoint(0),
mServer(NULL)
{}

void EnvironmentalSensorReadThread::assignCallBacks(Callback one, Callback two, Callback three)
{
	onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
}

void EnvironmentalSensorReadThread::assignServer(WatchDogServer* aServer)
{
	//Retrieve MIBS from the sensor
    mServer = aServer;
}

string EnvironmentalSensorReadThread::getAliasOID(WatchDogSensor* sensor)
{
	return mServer->getOIDRoot() + "." + dsl::toString(sensor->getSubRootOID()) + "." + mServer->AliasOID + "." + dsl::toString(sensor->getInstanceNr());
}

string EnvironmentalSensorReadThread::getPresentOID(WatchDogSensor* sensor)
{
	return mServer->getOIDRoot() + "." + dsl::toString(sensor->getSubRootOID()) + "." + mServer->AvailableOID + "." + dsl::toString(sensor->getInstanceNr());
}

string EnvironmentalSensorReadThread::getTempOID(WatchDogSensor* sensor)
{
	return mServer->getOIDRoot() + "." + dsl::toString(sensor->getSubRootOID()) + "." + mServer->TemperatureOID + "." + dsl::toString(sensor->getInstanceNr());
}

string EnvironmentalSensorReadThread::getHumidityOID(WatchDogSensor* sensor)
{
	return mServer->getOIDRoot() + "." + dsl::toString(sensor->getSubRootOID()) + "." + mServer->HumidityOID + "." + dsl::toString(sensor->getInstanceNr());
}

string EnvironmentalSensorReadThread::getDewPointOID(WatchDogSensor* sensor)
{
	return mServer->getOIDRoot() + "." + dsl::toString(sensor->getSubRootOID()) + "." + mServer->DewPointOID + "." + dsl::toString(sensor->getInstanceNr());
}

void EnvironmentalSensorReadThread::run()
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

        for(int i = 0; i < mServer->getNumberOfSensors(); i++)
        {
            if(mIsTimeToDie)
            {
            	break;
            }
	        //Query one sensor at a time
    	    WatchDogSensor* sensor = mServer->getSensor(i);

            if(sensor != 0 && !querySensor(sensor))
            {
            	Log(lError) << "There was a problem reading sensor with ID: "<<sensor->getDeviceID();
            }
        }
    }
    catch(...)
    {
		Log(lError) << "Unhandled exception..";
    }

	Log(lInfo) << "Exiting ENV Sensor Thread..";

    if(onExit)
    {
    	onExit(0,0);
    }

	mIsRunning = false;
	mIsFinished = true;
}


bool EnvironmentalSensorReadThread::querySensor(WatchDogSensor* sensor)
{
        //Setup arguments
        StringList args;
        args.append("-O n -v 2c -c public 192.168.123.123");

        args.append(getAliasOID(sensor));
        args.append(getPresentOID(sensor));
        args.append(getTempOID(sensor));
        args.append(getHumidityOID(sensor));
        args.append(getDewPointOID(sensor));

        Log(lDebug5) << "SNMP arguments: " << args.asString();

        //Capture output
        Pipe outPipe;

		//Capture stdout and stderr to outPipe
        ProcessHandle ph = Process::launch(mExecutable, args, NULL, &outPipe, &outPipe);

        //Use stream objects to read and write to the pipes
        PipeInputStream istr(outPipe);

		int progress(0);
        int c = istr.get();

        //Read all values before reporting progress
        string s;
        while (!istr.eof())
        {

            s += (char) c;
            if((c == '\n' || c == '\r') && s.size() > 1)
            {
            	Log(lDebug5) << "Parsing string: "<< s;
            	progress = parseOutput(s, sensor);

                if(onProgress && progress == 5)
                {
                	string msg;
                    //Let the calling application do whatever with the data
                    //in the onProgress callback
                    stringstream m;
                    m <<"DeviceID = "<<sensor->getDeviceID();
                    msg = m.str();
                    onProgress(progress, (int) &msg);
                }
                else if(progress == -1)
                {
                	Log(lError) << s;
                    mIsTimeToDie = true;
                }

                //Data should be consumed by now
                s.clear();
            }

            c = istr.get();
            if(mIsTimeToDie)
            {
            	break;
            }
        }

	int rc = ph.wait();
    Log(lDebug5) <<"RC: "<<rc;
	return true;
}

//Parsing text can be ugly..
int EnvironmentalSensorReadThread::parseOutput(const string& s, WatchDogSensor* sensor)
{
	//Update the sensor
	//Check string for content
    try
    {
		StringList tokens(s, ':');

        string valueToken = (tokens.count() == 2) ? trimChars(tokens[1], " \r") : string("");
        if(contains(getAliasOID(sensor), s))
        {
           	mAlias = valueToken;
            mAlias = trim(mAlias, 34);
            sensor->setAlias(mAlias);
            return 1;
        }

        if(contains(getPresentOID(sensor), s))
        {
            mIsPresent = toBool(valueToken);
            sensor->isPresent(mIsPresent);
            return 2;
        }

        if(contains(getTempOID(sensor), s))
        {
            //Got a temperature
            mTemperature = toInt(s, false) / 10.0;
            sensor->setTemperature(mTemperature);
            return 3;
        }
        if(contains(getHumidityOID(sensor), s))
        {
            mHumidity = toInt(s, false);
            sensor->setHumidity(mHumidity);
            return 4;
        }

        if(contains(getDewPointOID(sensor), s))
        {
            mDewPoint = toInt(s, false) / 10.0;
            sensor->setDewPoint(mDewPoint);
            return 5;
        }

        if(contains("Timeout", s))
        {
        	return -1;
        }
	}
	catch(const DSLException& e)
   	{
        Log(lError) << " There was a problem: "<<e.what();
   	}
    return 0;
}


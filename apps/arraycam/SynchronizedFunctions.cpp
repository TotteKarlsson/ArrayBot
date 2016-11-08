#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "vcl/abVCLUtils.h"
#include "mtkStringList.h"
#include "TSettingsForm.h"
using namespace mtk;
using namespace ab;


class TLocalArgs
{
    public:
    	string msg;

//    void __fastcall onSensorsArduinoMessage()
//    {
//        if(startsWith("DHT22_DATA", msg))
//        {
//            //Parse the message
//            StringList l(msg,',');
//            if(l.size() == 4)
//            {
//                //Fourth parameter is sensor number
//                int sensorNum = toInt(l[3]);
//
//                MainForm->mEnvReader.addReading(toDouble(l[1]), toDouble(l[2]), toInt(l[3]));
//
//                //Get average when it makes sense
//                if(MainForm->mEnvReader.getNumberOfReadings() == MainForm->mEnvReader.getNumberOfSensors())
//                {
//                    MainForm->mTemperatureLbl->SetValue(MainForm->mEnvReader.getAverageTemperature());
//                    MainForm->mHumidityE->SetValue(MainForm->mEnvReader.getAverageHumidity());
//
//                    //Put the numbers into the DB (change this to be outside the main thread(!)
//                    vector<SensorReading> readings = MainForm->mEnvReader.getReadings();
//                    for(int i = 0; i < readings.size(); i++)
//                    {
//                        SensorReading r = readings[i];
//                        try
//                        {
//                            MainForm->mClientDBSession.insertSensorData(r.mSensorID, r.mTemperature, r.mHumidity);
//                        }
//                        catch(...)
//                        {
//                            handleSQLiteException();
//                        }
//                    }
//
//                    //Purge reader
//                    MainForm->mEnvReader.purge();
//                }
//            }
//        }
//    }

    void __fastcall onLightsArduinoMessage()
    {
        //If mouse is down.. do not update certain UI objects
        bool isMouseBtnDown = (bool) GetAsyncKeyState(VK_LBUTTON);

        if(startsWith("GET_READY_FOR_ZERO_CUT_2", msg))
        {
            Log(lInfo) <<"Steady for zero cut";
            MainForm->stopSounds();
            MainForm->mGetReadyForZeroCutSound.play();
        }

        else if(startsWith("SET_ZERO_CUT", msg))
        {
            Log(lInfo) <<"Go for zero cut ";
            MainForm->stopSounds();
            MainForm->mSetZeroCutSound.play();
        }

        else if(startsWith("RESTORE_FROM_ZERO_CUT", msg))
        {
            Log(lInfo) <<"Restore from zero Cut ";
            MainForm->stopSounds();
            //MainForm->mRestoreFromZeroCutSound.play();
        }
        else if(startsWith("COAX_DRIVE", msg) && isMouseBtnDown == false )
        {
            StringList l(msg,'=');
            if(l.size() == 2 && MainForm->mSettingsForm)
            {
                MainForm->mSettingsForm->mCoaxTB->Tag = 1;
                MainForm->mSettingsForm->mCoaxTB->Position = toInt(l[1]);
                MainForm->mSettingsForm->mCoaxTB->Tag = 0;
            }
        }
        else if(startsWith("FRONT_LED_DRIVE", msg) && isMouseBtnDown == false)
        {
            StringList l(msg,'=');
            if(l.size() == 2 && MainForm->mSettingsForm)
            {
                MainForm->mSettingsForm->mFrontLEDTB->Tag = 1;
                MainForm->mSettingsForm->mFrontLEDTB->Position = toInt(l[1]);
                MainForm->mSettingsForm->mFrontLEDTB->Tag = 0;
            }
        }

        else if(startsWith("BACK_LED_DRIVE", msg) && isMouseBtnDown == false)
        {
            StringList l(msg,'=');
            if(l.size() == 2 && MainForm->mSettingsForm)
            {
                MainForm->mSettingsForm->mBackLEDTB->Tag = 1;
                MainForm->mSettingsForm->mBackLEDTB->Position = toInt(l[1]);
                MainForm->mSettingsForm->mBackLEDTB->Tag = 0;
            }
        }
    }
};

void TMainForm::onLightsArduinoMessageReceived(const string& msg)
{
    TLocalArgs args;
    args.msg = msg;

    //This causes this fucntion to be called in the UI thread
	TThread::Synchronize(NULL, &args.onLightsArduinoMessage);
}


void TMainForm::onSensorsArduinoMessageReceived(const string& msg)
{
//    TLocalArgs args;
//    args.msg = msg;
//
//    //This causes this fucntion to be called in the UI thread
//	TThread::Synchronize(NULL, &args.onSensorsArduinoMessage);

	//Populate DB

    if(startsWith("DHT22_DATA", msg))
    {
        //Parse the message
        StringList l(msg,',');
        if(l.size() == 4)
        {
            //Fourth parameter is sensor number
            int sensorNum = toInt(l[3]);

            mEnvReader.addReading(toDouble(l[1]), toDouble(l[2]), toInt(l[3]));

            //Get average when it makes sense
            if(mEnvReader.getNumberOfReadings() == mEnvReader.getNumberOfSensors())
            {
                //MainForm->mTemperatureLbl->SetValue(MainForm->mEnvReader.getAverageTemperature());
                //MainForm->mHumidityE->SetValue(MainForm->mEnvReader.getAverageHumidity());

                //Put the numbers into the DB (change this to be outside the main thread(!)
                vector<SensorReading> readings = mEnvReader.getReadings();
                for(int i = 0; i < readings.size(); i++)
                {
                    SensorReading r = readings[i];
                    try
                    {
                        Poco::ScopedLock<Poco::Mutex> lock(mClientDBMutex);
                        mClientDBSession.insertSensorData(r.mSensorID, r.mTemperature, r.mHumidity);
                    }
                    catch(...)
                    {
                        handleMySQLException();
                    }
                }

                //Purge reader
                mEnvReader.purge();
            }
        }
    }
}




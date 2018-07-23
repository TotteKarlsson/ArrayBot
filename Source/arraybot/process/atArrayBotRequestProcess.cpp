#pragma hdrstop
#include "atArrayBotRequestProcess.h"
//#include "atXYZUnit.h"
#include "dslLogger.h"
#include "dslXMLUtils.h"
#include "core/atArrayBotClient.h"
#include "atProcessSequence.h"

using namespace dsl;
using namespace tinyxml2;

namespace at
{

    static ArrayBotProtocol ap;
    //---------------------------------------------------------------------------
    ArrayBotRequestProcess::ArrayBotRequestProcess(ArrayBotClient& acc, const string& lbl, const string& request)
    :
    Process(lbl, NULL),
    mRequest(ap.idFromString(request)),
    mArrayBotClient(acc),
    mParameter1(0),
    mParameter2(0)
    {
    	mProcessType = ptArrayBotRequest;
        mArrayBotClient.assignOnMessageReceivedCallBack(onReceivedResponse);
    }

    void ArrayBotRequestProcess::clear()
    {}

    bool ArrayBotRequestProcess::write()
    {
    	if(mProcessSequence)
        {
        	return mProcessSequence->write();
        }
    	return false;
    }

    const string ArrayBotRequestProcess::getTypeName() const
    {
    	return "ArrayBotRequestProcess";
    }

    bool ArrayBotRequestProcess::setRequest(const string& request)
    {
    	ArrayBotProtocol ap;
    	mRequest = ap.idFromString(request);
        return true;
    }

    bool ArrayBotRequestProcess::setRequest(ABMessageID r)
    {
    	mRequest = r;
        return true;
    }

    XMLElement* ArrayBotRequestProcess::addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot)
    {
        //Create XML for saving to file
    	ArrayBotProtocol ap; //To get string value
        XMLElement* request	  		= doc.NewElement("request");

    	request->SetText(ap[mRequest].c_str() );
        docRoot->InsertEndChild(request);

    //	if(mRequest == acrSetZoomAndFocus) //Need parameters for this one
    //    {
    //        XMLElement* f = doc.NewElement("focus");
    //        f->SetText(mParameter1.getValueAsString().c_str());
    //        docRoot->InsertEndChild(f);
    //
    //        XMLElement* zoom = doc.NewElement("zoom");
    //        zoom->SetText(mParameter2.getValueAsString().c_str());
    //        docRoot->InsertEndChild(zoom);
    //    }
    //	else if(mRequest == acrSetLEDIntensity) //Need parameters for this one
    //    {
    //        XMLElement* f = doc.NewElement("intensity");
    //        f->SetText(mParameter1.getValueAsString().c_str());
    //        docRoot->InsertEndChild(f);
    //    }

        return request;
    }

    bool ArrayBotRequestProcess::isBeingProcessed()
    {
    	if(isDone())
        {
    		mIsBeingProcessed = false;
            mIsProcessed = true;
           	Timestamp now;
            mEndTime = now;
        }

        return mIsBeingProcessed;
    }

    bool ArrayBotRequestProcess::start()
    {
    	switch(mRequest)
        {

    		default:
            	Log(lError) << "Bad ArrayBotRequest in process";
    			return false;
        }

    	return Process::start();
    }

    bool ArrayBotRequestProcess::stop()
    {
    	return Process::stop();
    }

    bool ArrayBotRequestProcess::isProcessed()
    {
        if(isDone())
        {
            //Consider this process to be "processed"
            mIsProcessed 		= true;
            mIsBeingProcessed 	= false;
            return true;
        }

    	return false;
    }

    void ArrayBotRequestProcess::onReceivedResponse(const string& msg)
    {
    	if(!mIsBeingProcessed)
        {
        	return;
        }
        ArrayBotProtocol p;

        Log(lInfo) << "Got ArrayBot Response: "<<msg;

    //    switch(mRequest)
    //    {
    //    	case acrEnableBarcodeScanner:
    //        	if(msg == p[acrBarcodeScanSucceded])
    //    		{
    //                mIsProcessed = true;
    //            }
    //		break;
    //
    //    	case acrDisableBarcodeScanner:
    //        	if(msg == p[acrBarcodeScannerDisabled])
    //    		{
    //                mIsProcessed = true;
    //            }
    //		break;
    //
    //    	case acrStartVideoRecorder:
    //        	if(msg == p[acrVideoRecorderStarted])
    //    		{
    //                mIsProcessed = true;
    //            }
    //		break;
    //
    //    	case acrStopVideoRecorder:
    //        	if(msg == p[acrVideoRecorderStopped])
    //    		{
    //                mIsProcessed = true;
    //            }
    //		break;
    //
    //    	case acrTakeSnapShot:
    //        	if(msg == p[acrSnapShotTaken])
    //    		{
    //                mIsProcessed = true;
    //            }
    //		break;
    //
    //    	case acrSetZoomAndFocus:
    //        	if(msg == p[acrFocusAndZoomSet])
    //    		{
    //                mIsProcessed = true;
    //            }
    //		break;
    //
    //        case acrSetLEDIntensity:
    //        	if(msg == p[acrLEDIntensitySet])
    //    		{
    //                mIsProcessed = true;
    //            }
    //        break;
    //        case acrStartUC7:
    //        	if(msg == p[acrUC7Started] || msg == p[acrUC7IsRunning])
    //    		{
    //                mIsProcessed = true;
    //            }
    //        break;
    //
    //        case acrStopUC7:
    //        	if(msg == p[acrUC7Stopped] || msg == p[acrUC7IsStopped])
    //    		{
    //                mIsProcessed = true;
    //            }
    //        break;
    //
    //        case acrSetMoveWhiskerForwardOn:
    //        	if(msg == p[acrMoveWhiskerForwardOnSet])
    //    		{
    //                mIsProcessed = true;
    //            }
    //        break;
    //
    //        case acrSetMoveWhiskerForwardOff:
    //        	if(msg == p[acrMoveWhiskerForwardOffSet])
    //    		{
    //                mIsProcessed = true;
    //            }
    //        break;
    //    }
    }

    bool ArrayBotRequestProcess::isDone()
    {
    	if(!mIsStarted)
        {
        	return false;
        }

        return mIsProcessed;
    }


}


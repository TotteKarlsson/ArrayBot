#ifndef abProcessH
#define abProcessH
#include <string>
#include "abExporter.h"
#include "abABObject.h"
#include "Poco/TimeStamp.h"
#include "Poco/Timespan.h"
#include "mtkXMLUtils.h"
#include "abUtilities.h"
//---------------------------------------------------------------------------

using std::string;
using Poco::Timestamp;
using Poco::Timestamp::TimeDiff;

namespace mtk
{
	class IniSection;
}

class Trigger;
class ArrayBot;

class AB_CORE Process : public ABObject
{
    public:
        							            Process(const string& name, ABObject* ao = NULL);
							                    ~Process(){}
		virtual void		   		            init(ArrayBot& ab);
		string 						            getProcessType();
		virtual void	                        assignUnit(ABObject* o){mSubject = o;}
        void									setSubjectName(const string& n){mSubjectName = n;}
		ABObject*					            getUnit(){return mSubject;}
        string						            getProcessName(){return mProcessName;}
        void						            setProcessName(const string& l) {mProcessName = l;}
        bool						            isTimedOut();

        double			                        getPreDwellTime(){return mPreDwellTime;}
        bool			                        setPreDwellTime(double dt){mPreDwellTime = dt; return true;}

        double			                        getPostDwellTime(){return mPostDwellTime;}
        bool			                        setPostDwellTime(double dt){mPostDwellTime = dt; return true;}

                            		            //!isBeingProcess refer to if process is currently being processed
        virtual bool	                        isBeingProcessed() 	{return mIsBeingProcessed;}
        virtual	bool 			 	            isProcessed() 		{return mIsProcessed;}
        virtual	bool 			 	            isStarted() 		{return mIsStarted;}

        virtual bool	                        start() 			= 0;
        virtual bool	                        stop() 				= 0;
        virtual	bool	                        undo() 				= 0;

        virtual mtk::XMLElement*           		addToXMLDocument(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);
		virtual mtk::XMLElement*                addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);

    protected:
        							            //!The Process Name identifies the process in a sequence
                                                //and in a ini file
        string						            mProcessName;

        					                    //!The subject object can be casted in derived classes
    	ABObject* 		                        mSubject;

        										//!When reconstructing a process from XML use strings
                                                //!to identify objects
        string									mSubjectName;

        							            //!The process type help us construct
                                                //a new process object from a file
        ProcessType					            mProcessType;


		bool						            mIsStarted;
		bool						            mIsBeingProcessed;
		bool						            mIsProcessed;

        double			                        mPreDwellTime;
        double			                        mPostDwellTime;
        Timestamp					            mStartTime;
        Timestamp					            mEndTime;
        Poco::Timespan 				            mTimeOut;

        										//!Each process can have one trigger
                                                //!Todo: Make this a container and enable multiple trigger
                                                //!functionality. Also triggers of various subtypes
//        Trigger*								mTrigger;
};

#endif

#ifndef atProcessH
#define atProcessH
#include <string>
#include "atATObject.h"
#include "Poco/TimeStamp.h"
#include "Poco/Timespan.h"
#include "dslXMLUtils.h"
#include "atUtils.h"
//---------------------------------------------------------------------------

using std::string;
using Poco::Timestamp;
using Poco::Timestamp::TimeDiff;
using tinyxml2::XMLElement;
//using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;

namespace dsl
{
	class IniSection;
}

namespace at
{

class Trigger;
class ArrayBot;
class ProcessSequence;

class AT_CORE Process : public ATObject
{
    public:
        							            Process(const string& name, ATObject* ao = NULL);
							                    ~Process(){}
		virtual void		   		            init(ArrayBot& ab);

        virtual bool	                        start() 			= 0;
        virtual bool	                        stop() 				= 0;
        virtual bool	                        resume()			= 0;
        virtual	bool	                        undo() 				= 0;
        virtual bool 	  						isDone()			= 0;

        										//If the process is part of a sequence, write will
                                                //update the xml and save to file
        virtual bool							write() = 0;

        string									getInfoText(){return mInfoText;}
        void									setInfoText(const string& txt){mInfoText = txt;}

		virtual ProcessType 	   	            getProcessType();
		string 						            getProcessTypeAsString();

		virtual void	                        assignSubject(ATObject* o){mSubject = o;}
		virtual void	                        assignProcessSequence(ProcessSequence* ps){mProcessSequence = ps;}
		ProcessSequence*						getProcessSequence(){return mProcessSequence;}

        void									setSubjectName(const string& n){mSubjectName = n;}
		ATObject*					            getUnit(){return mSubject;}
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


        virtual  XMLElement*          			addToXMLDocument(tinyxml2::XMLDocument& doc, XMLNode* docRoot);
		virtual  XMLElement*                	addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot);
        Poco::Timespan							getElapsedTimeSinceStart();

    protected:
        							            //!The Process Name identifies the process in a sequence
        string						            mProcessName;

        					                    //!The subject object can be casted in derived classes
                                                //!The subject is typically a motor or relay for example
    	ATObject* 		                        mSubject;

        										//!When reconstructing a process from XML we use strings
                                                //!to identify objects
        string									mSubjectName;

        							            //!The process type help us construct
                                                //a new process object from a file
        ProcessType					            mProcessType;

        										//!A process may be part of a process sequence
		ProcessSequence*						mProcessSequence;

        										//!Info text is used if the user want to document the purpose of
                                                //a particular process
        string									mInfoText;

		bool						            mIsStarted;
		bool						            mIsBeingProcessed;
		bool						            mIsProcessed;

        double			                        mPreDwellTime;
        double			                        mPostDwellTime;
        Timestamp					            mStartTime;
        Timestamp					            mEndTime;
        Poco::Timespan 				            mTimeOut;
};

}
#endif

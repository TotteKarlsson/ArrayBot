#ifndef abProcessH
#define abProcessH
#include "abExporter.h"
#include "abABObject.h"
#include <string>
#include "Poco/TimeStamp.h"
#include "Poco/Timespan.h"


//---------------------------------------------------------------------------

using std::string;
namespace mtk
{
	class IniSection;
}

using Poco::Timestamp;

using Poco::Timestamp::TimeDiff;
enum ProcessType {ptLinearMove = 0};

class AB_CORE Process : public ABObject
{
    public:
        							Process(const string& lbl, ABObject* o);
							        ~Process(){}
		void						init();

		virtual void	            assignUnit(ABObject* o){mUnit = o;}
		ABObject*					getUnit(){return mUnit;}
        string						getProcessName(){return mProcessName;}
        void						setProcessName(const string& l) {mProcessName = l;}
        bool						isTimedOut();

        double			            getPostDwellTime(){return mPostDwellTime;}
        bool			            setPostDwellTime(double dt){mPostDwellTime = dt; return true;}

        double			            getPreDwellTime(){return mPreDwellTime;}
        bool			            setPreDwellTime(double dt){mPreDwellTime = dt; return true;}

                            		//!isBeingProcess refer to if process is currently being processed
        virtual bool	            isBeingProcessed() 	{return mIsBeingProcessed;}
        virtual	bool 			 	isProcessed() 		{return mIsProcessed;}
        virtual	bool 			 	isStarted() 		{return mIsStarted;}

        virtual bool	            start() 			= 0;
        virtual bool	            stop() 				= 0;
        virtual	bool	            undo() 				= 0;

        virtual bool				read(mtk::IniSection* sec) = 0;
        virtual bool				write(mtk::IniSection* sec) = 0;

    protected:
        							//!The Process Name identifies the process in a sequence
                                    //and in a ini file
        string						mProcessName;

        					        //!Making object for moving abstract allow us
                                    //to process 'any' object. Just specialize in the
                                    //execute function..
    	ABObject* 		            mUnit;

        							//!The process type help us construct
                                    //a new process object from a file
        ProcessType					mProcessType;

        							//!A process parameters are saved
                                    //to its own INI section in a INI file
        mtk::IniSection*	   		mIniSection;

		bool						mIsStarted;
		bool						mIsBeingProcessed;
		bool						mIsProcessed;


        double			            mPreDwellTime;
        double			            mPostDwellTime;
        Timestamp					mStartTime;
        Timestamp					mEndTime;
        Poco::Timespan 				mTimeOut;
};


#endif

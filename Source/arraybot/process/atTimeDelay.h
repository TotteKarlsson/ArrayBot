#ifndef atTimeDelayH
#define atTimeDelayH
#include "atProcess.h"
#include <vector>
#include "dslXMLUtils.h"
#include "arraybot/atABExporter.h"
//---------------------------------------------------------------------------
using namespace std;


namespace at
{

    class AT_AB TimeDelay : public Process
    {
        public:
            	   			                    TimeDelay(const string& lbl, Poco::Timespan ts = Poco::Timespan(1000*Poco::Timespan::MILLISECONDS));
        	virtual			                    ~TimeDelay(){}
            bool						        setTimeDelay(long delay){mTimeDelay = delay; return true;}
    		const string 				        getTypeName() const;
    		virtual bool 			            write();
    	    void						        clear();

            virtual dsl::XMLElement*            addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);

            virtual bool	                    start();
            virtual bool	                    resume(){return false;}
            virtual bool	                    stop();
            virtual bool	                    isBeingProcessed();
            bool 						        isProcessed();
    		Poco::Timespan				        getTimeDelay(){return mTimeDelay;}

    									        //Check if we are at proper position(s)
            bool 						        isDone();
           	bool	            		        undo(){return true;}

        protected:                              //!The TimeDelay is represented with a Poco Timespan
    		Poco::Timespan				        mTimeDelay;
    };


}
#endif

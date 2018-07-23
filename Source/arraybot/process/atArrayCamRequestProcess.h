#ifndef atArrayCamRequestH
#define atArrayCamRequestH
#include "atABExporter.h"
#include "atProcess.h"
#include "dslXMLUtils.h"
#include "atArrayCamProtocol.h"
#include "atProcessSequenceProject.h"

//---------------------------------------------------------------------------
using namespace std;

namespace at
{

    class ArrayCamClient;
    class AT_AB ArrayCamRequestProcess : public Process
    {
    	friend ProcessSequenceProject;
        public:
            	   			                            ArrayCamRequestProcess(ArrayCamClient& acc, const string& lbl, const string& request = "");
        	virtual			                            ~ArrayCamRequestProcess(){}
    		virtual bool 	   	                        write();
            bool						                setRequest(ACMessageID r);
            bool						                setRequest(const string& request);
    		const string 				                getTypeName() const;
    	    void						                clear();
            virtual dsl::XMLElement*                    addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
            void						                onReceivedResponse(const string& msg);

            virtual bool	                            start();
            virtual bool	                            resume(){return false;}
            virtual bool	                            stop();
            virtual bool	                            isBeingProcessed();
            bool 						                isProcessed();
    		ACMessageID					                getRequest(){return mRequest;}

            bool 						                isDone();
           	bool	            		                undo(){return false;}

            											//This is pretty ugly
    		Property<double>&							getParameter1(){return mParameter1;}
    		Property<double>&							getParameter2(){return mParameter2;}

        protected:                                      //!The ArrayCamRequestProcess is a simple text command
    		ACMessageID					                mRequest;

            							                //!The client allows us to send a request to the server
            ArrayCamClient&				                mArrayCamClient;
            Property<double>							mParameter1;
            Property<double>							mParameter2;


    };


}
#endif

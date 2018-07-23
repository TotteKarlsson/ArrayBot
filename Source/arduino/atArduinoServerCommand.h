#ifndef atArduinoServerCommandH
#define atArduinoServerCommandH
#include "atCoreExporter.h"
#include "atProcess.h"
#include "atArduinoExporter.h"
//---------------------------------------------------------------------------

namespace at
{
class ArduinoClient;


//!Arraybot can execute a Arduino command, like Activate Vacuum using an
//!Arduino server command.
class AT_ARDUINO ArduinoServerCommand : public Process
{
    public:
        	   			                    ArduinoServerCommand(const string& lbl);
    	virtual			                    ~ArduinoServerCommand();
		const string 						getTypeName() const;
		virtual void		   		        init(ArrayBot& ab);
		virtual bool 			  	        write(){return false;}
		virtual XMLElement*            		addToXMLDocumentAsChild(tinyxml2::XMLDocument& doc, XMLNode* docRoot);

        virtual bool	                    isBeingProcessed();
        bool 						        isProcessed();
        virtual	bool	                    undo();

        void								setArduinoClient(ArduinoClient* c){mArduinoClient = c;}
        void								setCommand(const string& c){mCommand = c;}

        virtual bool	                    start();
        virtual bool	                    resume(){return 0;}
        virtual bool	                    stop(){return Process::stop();}
        virtual bool 				        isDone();

    protected:
        Trigger*							mTrigger;
        string								mCommand;
        ArduinoClient*                      mArduinoClient;
};

}
#endif

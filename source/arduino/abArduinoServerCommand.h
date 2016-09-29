#ifndef abArduinoServerCommandH
#define abArduinoServerCommandH
#include "abExporter.h"
#include "abProcess.h"
//---------------------------------------------------------------------------

class ArduinoClient;

//!The switch class allow a 'switched' process to be executed
class AB_CORE ArduinoServerCommand : public Process
{
    public:
        	   			                    ArduinoServerCommand(const string& lbl);
    	virtual			                    ~ArduinoServerCommand(){}
		const string 						getTypeName() const;
		virtual void		   		        init(ArrayBot& ab);

		virtual mtk::XMLElement*            addToXMLDocumentAsChild(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);

        virtual bool	                    isBeingProcessed();
        bool 						        isProcessed();
        virtual	bool	                    undo();

        void								setArduinoClient(ArduinoClient* c){mArduinoClient = c;}
        void								setCommand(const string& c){mCommand = c;}

        virtual bool	                    start();
        virtual bool	                    stop(){return Process::stop();}
        virtual bool 				        isDone();

    protected:
        Trigger*							mTrigger;
        string								mCommand;
        ArduinoClient*                      mArduinoClient;
};


#endif

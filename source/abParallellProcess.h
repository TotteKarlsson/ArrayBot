#ifndef abParallellProcessH
#define abParallellProcessH
#include "abProcess.h"
#include <vector>
#include "mtkXMLUtils.h"
//---------------------------------------------------------------------------
using namespace std;

//!A parallell process is a process combining one or more processes that are
//!executed in parallell.
//!When starting a parallell process, all parallell processes are started virtually simultaneously (occurs in a loop).
//!A parallell process is not finished until all processes, including their triggered processes
//!are processed, finished
class AB_CORE ParallellProcess : public Process
{
    public:
        	   			            ParallellProcess(const string& lbl);
    	virtual			            ~ParallellProcess(){}
		virtual void		   		init(ArrayBot& ab);
		const string 				getTypeName() const;
        void						clear();

        virtual mtk::XMLElement*    addToXMLDocumentAsChildProcess(mtk::XMLDocument& doc, mtk::XMLNode* docRoot);
        int							getNumberOfProcesses(){return mProcesses.size();}

		virtual void	            addProcess(Process* lm);
        Process*			  		getProcess(const string& lbl);
        Process*					getProcess(int i);

        bool 						removeProcess(Process* m);
        bool 						removeProcess(const string& name);

        							//!All moves starts at the same time
        virtual bool	            start();
        virtual bool	            stop();
        virtual bool	            isBeingProcessed();
        bool 						isProcessed();
		bool						isCommandPending();
        virtual	bool	            undo();

									//Check if we are at proper position(s)
        virtual bool 	  			isDone();
        virtual bool	            areMotorsActive();

    protected:                      //!The Processes container contain all moves
		vector<Process*>	  		mProcesses;
};

#endif

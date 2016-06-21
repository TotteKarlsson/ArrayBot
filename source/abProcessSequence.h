#ifndef abProcessSequenceH
#define abProcessSequenceH
#include "abExporter.h"
#include "abABObject.h"
#include <list>
#include <string>

//---------------------------------------------------------------------------
using std::list;
using std::string;
class Process;

class AB_CORE ProcessSequence : public ABObject
{
    public:
										    ProcessSequence(const string& name = "MyProcess", const string& fileExt = "proc");
				        		            ~ProcessSequence();

		void					            clear();
        string								getName(){return mName;}
        virtual bool	 		            read(const string& fName);
        virtual bool			            write(const string& folder);

		virtual bool	   		            assignUnit(ABObject* o);
		virtual bool 			            add(Process* p);
		bool 					            remove(Process* p);
		bool 					            remove(const string& lbl);

        Process*                 	        getFirst() const;
        Process*                          	getNext() const;
        Process*                          	getPrevious() const;
        Process*                          	getCurrent() const;
        void								setName(const string& name) {mName = name;}
        void								setFileExtension(const string& e) {mFileExtension = e;}
        void								setFileFolder(const string& f) {mFileFolder = f;}
        string 								getFileFolder() {return mFileFolder;}

    protected:
  		string					        	mName;
        string								mFileExtension;
        string								mFileFolder;

        									//!List of abstract Processes
		mutable list<Process*>  			mProcesses;
        mutable list<Process*>::iterator 	mProcessIter;
};
#endif

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
										    ProcessSequence();
				        		            ~ProcessSequence();

		void					            clear();
        virtual bool	 		            read(const string& fName);
        virtual bool			            write();

		virtual bool	   		            assignUnit(ABObject* o);
		virtual bool 			            add(Process* p);
		bool 					            remove(const string& lbl);

        Process*                 	        getFirst() const;
        Process*                          	getNext() const;
        Process*                          	getPrevious() const;
        Process*                          	getCurrent() const;

    protected:
  		string					        	mName;
        string								mFileExtension;

        									//!List of abstract Processes
		mutable list<Process*>  			mProcesses;
        mutable list<Process*>::iterator 	mProcessIter;
};
#endif

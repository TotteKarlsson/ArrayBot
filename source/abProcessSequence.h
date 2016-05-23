#ifndef abProcessSequenceH
#define abProcessSequenceH
#include "abExporter.h"
#include "abABObject.h"
#include <list>
#include <vector>
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
		bool					            assignUnit(ABObject* o);
		void					            clear();
        bool					            read(const string& fName);
        bool					            write();
		bool 					            add(Process* p);
		bool 					            remove(const string& lbl);

        Process*                 	        getFirst() const;
        Process*                          	getNext() const;
        Process*                          	getPrevious() const;
        Process*                          	getCurrent() const;

    protected:
  		string					        	mName;
		mutable list<Process*>  			mProcesses;
        mutable list<Process*>::iterator 	mProcessIter;
};
#endif

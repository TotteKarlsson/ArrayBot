#ifndef abProcessSequenceH
#define abProcessSequenceH
#include "abExporter.h"
#include "abABObject.h"
#include <list>
#include <string>
#include "mtkINISection.h"
#include "mtkProperty.h"
#include "abProcessSequenceProject.h"
//---------------------------------------------------------------------------

using std::list;
using std::string;
using mtk::IniSection;
using mtk::Property;
class Process;

class AB_CORE ProcessSequence : public ABObject
{
    public:
										    ProcessSequence(const string& name = "", const string& fileExt = "proc");
				        		            ~ProcessSequence();
					        		        ProcessSequence(const ProcessSequence& s);

                                            //!Init the sequence brings all processes into their
                                            //!initial state. Required if a sequence is to be rerun
		void								init();
		void					            clear();
        string								getName(){return mProject.getProjectName();}


        virtual bool	 		            read(const string& fName);
        virtual bool			            write(const string& folder);

		virtual bool	   		            assignUnit(ABObject* o);
		virtual bool 			            add(Process* p);
		bool 					            remove(Process* p);
		bool 					            remove(const string& lbl);

		bool								isFirst(Process* p);
        Process*                 	        getFirst() const;
        Process*                          	getNext() const;
        Process*                          	getPrevious() const;
        Process*                          	getCurrent() const;
        void								setProjectName(const string& name);


        void								setFileFolder(const string& f);
		void								setFileName(const string& f);
        void								setFileExtension(const string& e);
        string 								getFileFolder();

        int									getNumberOfProcesses(){return mProcesses.size();}


    protected:
	    ProcessSequenceProject	 			mProject;
//        IniSection							mIniSection;
//        string								mFileExtension;
//        string								mFileFolder;

        									//!List of abstract Processes
		mutable list<Process*>  			mProcesses;
        mutable list<Process*>::iterator 	mProcessIter;
};
#endif

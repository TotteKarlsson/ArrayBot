#ifndef atProcessSequenceH
#define atProcessSequenceH
#include "arraybot/atABExporter.h"
#include "atATObject.h"
#include <list>
#include <deque>
#include <string>
#include "dslINISection.h"
#include "dslProperty.h"
#include "atProcessSequenceProject.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------

using std::list;
using std::deque;
using std::string;
using dsl::IniSection;
using dsl::Property;
using dsl::gEmptyString;

namespace at
{

    class Process;
    class ArrayBot;

    //!A ProcessSequence maintains a list of processes.
    //!The processsequencer takes a ProcessSequence as input and executes inidividual processes
    //!from the sequence
    class AT_AB ProcessSequence : public ATObject
    {
        public:
    										    ProcessSequence(ArrayBot& ab, ArrayCamClient& ac, const string& sequenceName = gEmptyString, const string& fileExt = "ab");
    				        		            ~ProcessSequence();
    					        		        ProcessSequence(const ProcessSequence& s);

                                                //!Init the sequence brings all processes into their
                                                //!initial state. Required if a sequence is to be rerun.
                                                //!init and reset are synonomous
    		void								init();

    		void					            clear();
            string								getName();

            virtual bool	 		            read(const string& fName);
            virtual bool			            write(const string& folder = dsl::gEmptyString);

    		virtual bool	   		            assignSubject(ATObject* o);

    		virtual bool 			            add(Process* p);

            Process*							peekNext();
    		bool 					            remove(Process* p);
    		bool 					            remove(const string& lbl);

    		bool								isFirst(Process* p);
            Process*                 	        getFirst() const;
            Process*                          	getNext() const;
            Process*                          	getPrevious() const;
            Process*                          	getCurrent() const;
            bool								selectProcess(Process* p);
            Process*							getProcessWithName(const string& name);

            void								setCategory(const string& c);
            string								getCategory();

    		int 								getOrder();
    		void 								setOrder(int o);

    		bool 								getUseProcessController();
    		void 								setUseProcessController(bool o);


            void								setProjectName(const string& name);
            void								setFileFolder(const string& f);
    		void								setFileName(const string& f);
            void								setFileExtension(const string& e);
    		string								getFileName();
            string 								getFileFolder();
            int									getNumberOfProcesses(){return mProcesses.size();}
            ArrayBot*							getArrayBot(){return &mAB;}
            bool								moveForward(Process* ps);
            bool								moveBack(Process* ps);
            string								getXML();

        protected:
        	ArrayBot&							mAB;
    	    ProcessSequenceProject	 			mProject;

            									//!Allow categorization of ProcessSequences
                                                //!For example, "Preset" sequences and "General"
                                                //!Categories are used in order to organize the UI
    		string								mCategory;

            									//!The order is used by any component that need to order
                                                //!sequences.
            int									mOrder;

            									//!Allow sequence to be executed without using
                                                //!the process controller.
    		bool								mUseProcessController;

            									//!List of abstract Processes
    		mutable list<Process*>  			mProcesses;
            mutable list<Process*>::iterator 	mProcessIter;
    };
}
#endif

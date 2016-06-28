#ifndef abProcessSequencesH
#define abProcessSequencesH
#include "abExporter.h"
#include "abABObject.h"
#include <deque>
#include "abProcessSequence.h"
//---------------------------------------------------------------------------
using std::deque;


class AB_CORE ProcessSequences : public ABObject
{
	public:
								                    ProcessSequences(const string& fileFolder);
								                    ~ProcessSequences();
		bool										setFileFolder(const string& fileFolder);
        string										getFileFolder();
		bool					                    add(ProcessSequence* s);
        bool					                    remove(const string& lbl);
        ProcessSequence*                            getFirst() const;
        ProcessSequence*                            getNext() const;
        ProcessSequence*                            getPrevious() const;
        ProcessSequence*                            getCurrent() const;
		string										getCurrentSequenceName();

        											//!Loads a process sequence from file.
                                                    //Files have the same name as the
                                                    //sequence itself
        bool										load(const string& sName);
        int											count(){return mProcessSequences.size();}
		bool										saveCurrent();
        bool										clear();

	protected:
    	mutable deque<ProcessSequence*> 			mProcessSequences;
    	mutable deque<ProcessSequence*>::iterator 	mProcessSequencesIter;
        string										mFileFolder;
};
#endif

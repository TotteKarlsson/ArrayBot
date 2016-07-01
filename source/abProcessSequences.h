#ifndef abProcessSequencesH
#define abProcessSequencesH
#include "abExporter.h"
#include "abABObject.h"
#include <deque>
#include "abProcessSequence.h"
#include "mtkConstants.h"


//---------------------------------------------------------------------------
using std::deque;
using namespace mtk;

class AB_CORE ProcessSequences : public ABObject
{
	public:
								                    ProcessSequences(const string& fileFolder, const string& fileExtension);
								                    ~ProcessSequences();
		bool										setFileFolder(const string& fileFolder);
        string										getFileFolder();
        int											loadAll(const string& fileFolder = gEmptyString);
		bool					                    add(ProcessSequence* s);
        bool					                    remove(const string& lbl);
	   	ProcessSequence*							select(const string& sName);

        ProcessSequence*                            getFirst() const;
        ProcessSequence*                            getNext() const;
        ProcessSequence*                            getPrevious() const;
        ProcessSequence*                            getCurrent() const;
		string										getCurrentSequenceName();

        											//!Loads a process sequence from file.
                                                    //Files have the same name as the
                                                    //sequence itself
        bool										load(const string& fName);
        int											count(){return mProcessSequences.size();}
		bool										saveCurrent();
        bool										clear();

	protected:
    	mutable deque<ProcessSequence*> 			mProcessSequences;
    	mutable deque<ProcessSequence*>::iterator 	mProcessSequencesIter;
        string										mFileFolder;
        string										mFileExtension;
};
#endif

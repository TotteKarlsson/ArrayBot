#ifndef abProcessSequenceProjectH
#define abProcessSequenceProjectH
#include "abExporter.h"
#include "mtkProject.h"
#include "mtkConstants.h"
#include "abProcess.h"

//---------------------------------------------------------------------------
AB_CORE extern const string gProcessSequenceProjectFileVersion;

class ProcessSequence;
class AB_CORE ProcessSequenceProject : public mtk::Project
{
    public:
                                                ProcessSequenceProject(ProcessSequence& ps, const string& fName = "Sequence 1.abp");
                                                ~ProcessSequenceProject();

        bool                                    save(const string& fName = mtk::gEmptyString);
        bool                                    open();
        string                                  getPresentModelVersion();

    protected:
        ProcessSequence&                        mProcessSequence;
        bool                                    resetXML();
        int                                     loadProcesses();

        Process*				                createProcess(tinyxml2::XMLElement* element);
		Process*								createParallellProcess(tinyxml2::XMLElement* element);
		Process*								createTimeDelayProcess(tinyxml2::XMLElement* element);
};

#endif

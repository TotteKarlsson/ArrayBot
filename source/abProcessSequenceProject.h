#ifndef abProcessSequenceProjectH
#define abProcessSequenceProjectH
#include "abExporter.h"
#include "mtkProject.h"
#include "mtkSharedPointer.h"
#include "mtkConstants.h"
#include "abProcess.h"

//---------------------------------------------------------------------------
AB_CORE extern const string gProcessSequenceProjectFileVersion;

class ProcessSequence;
class AB_CORE ProcessSequenceProject : public mtk::Project
{
    public:
                                                ProcessSequenceProject(ProcessSequence& mlx, const string& fName = mtk::gEmptyString);
                                                ~ProcessSequenceProject();

        bool                                    save(const string& fName = mtk::gEmptyString);
        bool                                    open();
        string                                  getPresentModelVersion();

    protected:
        ProcessSequence&                        mProcessSequence;
        string                                  mVersion;
        bool                                    resetXML();
        int                                     loadProcesses();
        Process*				                createProcess(tinyxml2::XMLElement* element);
};

#endif

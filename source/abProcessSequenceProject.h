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
        ProcessSequence&                        mParent;
        string                                  mVersion;
        bool                                    resetXML();
        bool                                    saveExplorerSettings();
        bool                                    loadExplorerSettings();
        int                                     loadObjects();
        mtk::shared_ptr<Process>                createObject(tinyxml2::XMLElement* element);
};

#endif

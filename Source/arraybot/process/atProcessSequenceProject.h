#ifndef atProcessSequenceProjectH
#define atProcessSequenceProjectH
#include "arraybot/atABExporter.h"
#include "dslProject.h"
#include "dslConstants.h"
#include "atProcess.h"
#include "atATObject.h"

//---------------------------------------------------------------------------
AT_AB extern const string gProcessSequenceProjectFileVersion;

namespace tinyxml2
{
	class XMLElement;
}

namespace at
{
    class ArrayCamClient;
    class ProcessSequence;
    class AbsoluteMove;
    class StopAndResumeProcess;
    class ArrayCamRequestProcess;
    class TimeDelay;
    class ParallelProcess;
    class ArduinoServerCommand;
    class MoveCoverSlipAtAngleProcess;
    class HomeMotor;

    //!A ProcessSequenceProject makes it possible to save and load a ProcessSequence to file, using a simple xml format.
    class AT_AB ProcessSequenceProject : public dsl::Project, public ATObject
    {
    	friend ArrayCamRequestProcess;
        public:
                                                    ProcessSequenceProject(ProcessSequence& ps, ArrayCamClient& ac, const string& fName = "Sequence 1.abp");
                                                    ~ProcessSequenceProject();

            bool                                    save(const string& fName = dsl::gEmptyString);
            bool                                    open(const string& fName = dsl::gEmptyString);
            string                                  getPresentXMLModelVersion();

        protected:
            ProcessSequence&                        mProcessSequence;
            ArrayCamClient&							mArrayCamClient;
            bool                                    resetXML();
            int                                     loadProcesses();

            Process*				                createProcess(tinyxml2::XMLElement* element);
    		ParallelProcess*						createParallelProcess(tinyxml2::XMLElement* element);
    		AbsoluteMove* 				  			createAbsoluteMove(tinyxml2::XMLElement* proc);
    		TimeDelay*								createTimeDelayProcess(tinyxml2::XMLElement* element);
    		StopAndResumeProcess*					createStopAndResumeProcess(tinyxml2::XMLElement* element);
    		ArrayCamRequestProcess* 				createArrayCamRequestProcess(tinyxml2::XMLElement* element);
    		ArduinoServerCommand* 					createArduinoServerCommand(tinyxml2::XMLElement* proc);
    		MoveCoverSlipAtAngleProcess* 			createMoveCoverSlipAtAngleProcess(tinyxml2::XMLElement* proc);
    		HomeMotor* 								createHomeMotorProcess(tinyxml2::XMLElement* proc);
    };
}

#endif

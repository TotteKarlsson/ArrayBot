#ifndef abWhiskerUnitH
#define abWhiskerUnitH
#include "abExporter.h"
#include "abXYZUnit.h"
//---------------------------------------------------------------------------

class AB_CORE WhiskerUnit  : public XYZUnit
{
    public:
        						        WhiskerUnit(IniFile& iniFile, const string& appDataFolder);
						                ~WhiskerUnit(){}
		virtual bool	  	            initialize();
        virtual bool	  		        stopAll();
		virtual void 					attachJoyStick(ArrayBotJoyStick* js);

		vector<APTMotor*> 				getAllMotors();

    protected:
		Property<int>		            mZ2MotorSerialNr;
        APTMotor*			            mZ2Motor;

};
#endif

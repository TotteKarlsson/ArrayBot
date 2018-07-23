#ifndef atSensorsArduinoClientH
#define atSensorsArduinoClientH
#include "atCoreExporter.h"
#include "atArduinoClient.h"
//---------------------------------------------------------------------------

class AT_ARDUINO SensorsArduinoClient : public ArduinoClient
{
    public:
			   			        			SensorsArduinoClient();
		virtual			        			~SensorsArduinoClient(){}
		virtual void	 					getBoardStatus();

    protected:

};

#endif

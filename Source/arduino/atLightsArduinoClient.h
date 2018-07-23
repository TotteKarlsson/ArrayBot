#ifndef atLightsArduinoClientH
#define atLightsArduinoClientH
#include "atCoreExporter.h"
#include "atArduinoClient.h"
//---------------------------------------------------------------------------

namespace at
{


class AT_ARDUINO LightsArduinoClient : public ArduinoClient
{
    public:
			   			        			LightsArduinoClient();
		virtual			        			~LightsArduinoClient(){}

		void								toggleLED();
		void								toggleCoax();
		virtual void	 					getBoardStatus();

    protected:

};

}
#endif

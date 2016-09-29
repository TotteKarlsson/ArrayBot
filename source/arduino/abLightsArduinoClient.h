#ifndef abLightsArduinoClientH
#define abLightsArduinoClientH
#include "abExporter.h"
#include "abArduinoClient.h"
//---------------------------------------------------------------------------

class AB_CORE LightsArduinoClient : public ArduinoClient
{
    public:
			   			        			LightsArduinoClient();
		virtual			        			~LightsArduinoClient(){}

		void								toggleLED();
		void								toggleCoax();
		virtual void	 					getBoardStatus();

    protected:

};

#endif

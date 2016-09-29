#ifndef abPufferArduinoClientH
#define abPufferArduinoClientH
#include "abExporter.h"
#include "abArduinoClient.h"
//---------------------------------------------------------------------------

class AB_CORE PufferArduinoClient : public ArduinoClient
{
    public:
			   			        PufferArduinoClient();
		virtual			        ~PufferArduinoClient(){}

		void 					getBoardStatus();

        						//Requests to the server
        void					resetSectionCounter();

								//Puffer stuff
        void					setDesiredRibbonLength(int c);
        void					enablePuffer();

        void					enableAutoPuff();
        void					disableAutoPuff();
		void					puff();

        void					enableAutoZeroCut();
        void					disableAutoZeroCut();

		void					startNewRibbon();

        void					setCutPreset(int preset);
    protected:

};
#endif

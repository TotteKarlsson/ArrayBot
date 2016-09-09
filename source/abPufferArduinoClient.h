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

        						//Requests to the server
        void					resetSectionCounter();
        void					setPuffAfterSectionCount(int c);

        void					enablePuffer();

        void					enableAutoPuff();
        void					disableAutoPuff();
		void					puff();


    protected:

};
#endif

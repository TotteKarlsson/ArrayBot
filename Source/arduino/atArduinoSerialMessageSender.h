#ifndef atArduinoSerialMessageSenderH
#define atArduinoSerialMessageSenderH
#include "atCoreExporter.h"
#include <string>
#include "dslThread.h"
#include "atATObject.h"
#include "atArduinoExporter.h"
//---------------------------------------------------------------------------

using dsl::gEmptyString;

//!The message sender manages the Arduino's serial output queue in a thread.
//!When a message is posted onto the queue, the thread is awakened and
//!the message, or messages are sent one by one over the serial port.
//!A delay, ProcessTimeDelay can be used in order to no overflow the serial
//!devices input buffer
namespace at
{
    class ArduinoDevice;
    class AT_ARDUINO ArduinoSerialMessageSender : public dsl::Thread, public ATObject
    {
        public:
                                                        ArduinoSerialMessageSender(ArduinoDevice& d);
                                                        ~ArduinoSerialMessageSender();

                                                        // overridden from Thread
            void                                        run();

            bool                                        start(bool in_thread = true);
            void                                        stop();

    	protected:
            double										mProcessTimeDelay;
    		ArduinoDevice&             					mTheArduino;
    };
}
#endif

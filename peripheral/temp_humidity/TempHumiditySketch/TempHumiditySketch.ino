#include <stdio.h>
#include <DHT22.h>

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7

// Setup a GLOBAL DHT22 instance
DHT22 gDHT22(DHT22_PIN);

void readEnvironmentalSensors(DHT22& gDHT22);

template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }
long loopNr(0);
void setup(void)
{
    // setup serial port
    Serial.begin(250000);
    Serial.print("[ArrayBot SensorSketch_1]");
    
}

void loop(void)
{ 
    static int aDelay (1000);
    while(Serial.available() > 0)
    { 
        char ch = Serial.read();        
        switch(ch)
        {
            case 's': //Set delay - send format [s:1234]
                //Next byte is delay length
                aDelay = Serial.parseInt(); 
            break;
            
            case ']': Serial <<"[ACK]"; break;
        }
    }              
    
    Serial<<"[LOOP:" << loopNr++ << "]"; 
    delay(aDelay);
  
    // The sensor is read every ~2s.
    readEnvironmentalSensors(gDHT22);
}

void readEnvironmentalSensors(DHT22& s)
{
    switch(s.readData())
    {
        case DHT_ERROR_NONE:
            Serial.print("[DHT22,");
            Serial.print(s.getTemperatureC());      
            Serial.print(",");
            Serial.print(s.getHumidity());
            Serial.print("]");
        break;

        //The following are error conditions. Pulling to quick happens easily, no need to report
        case DHT_ERROR_CHECKSUM:        Serial.print(   "[DHT22_ERROR, Check Sum Error ");        break;
        case DHT_BUS_HUNG:              Serial.println( "[DHT22_ERROR, BUS Hung]");               break;
        case DHT_ERROR_NOT_PRESENT:     Serial.println( "[DHT22_ERROR, Not Present]");            break;
        case DHT_ERROR_ACK_TOO_LONG:    Serial.println( "[DHT22_ERROR, ACK Time out]");           break;
        case DHT_ERROR_SYNC_TIMEOUT:    Serial.println( "[DHT22_ERROR, Sync Timeout]");           break;
        case DHT_ERROR_DATA_TIMEOUT:    Serial.println( "[DHT22_ERROR, Data Timeout]");           break;
        case DHT_ERROR_TOOQUICK:        /*Serial.println("[DHT22_ERROR, Polled to Quick]");*/     break;
        default:                        Serial.println( "[DHT22_ERROR, Error Code not Defined]"); break;      
    }    
}

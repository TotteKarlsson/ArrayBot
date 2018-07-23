/* 
 *  This sketch read temperature and humidity data
 *  from 3 DHT22 sensors
*/

double sketchVersion = 1.0;

//The DHT22 is a combined temp/humidity sensor
#include "DHT.h"
#define DHTTYPE DHT22

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_1_PIN 7
#define DHT22_2_PIN 8
#define DHT22_3_PIN 9

// Setup global DHT22 instances
DHT gDHT22_1(DHT22_1_PIN, DHTTYPE);
DHT gDHT22_2(DHT22_2_PIN, DHTTYPE);
DHT gDHT22_3(DHT22_3_PIN, DHTTYPE);

void readEnvironmentalSensors(DHT& gDHT22, int sensorNum);

unsigned long lastReadTime = millis();
   
void checkPINStates();
void processByte(char ch); 

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &o, T arg) { o.print(arg); return o; }
  
void setup() 
{
    // setup serial port
    Serial.begin(19200);
    sendInfo();    
}

void loop() 
{ 
    while(Serial.available() > 0)
    {         
        processByte(Serial.read());
    }    
   
    //Read digital lines and send status over serial port so the host
    //can update its UI
    unsigned long currentReadTime = millis();
    if(currentReadTime - lastReadTime > (1000 * 30))
    {
        lastReadTime = currentReadTime;
        readEnvironmentalSensors(gDHT22_1, 1);    
        readEnvironmentalSensors(gDHT22_2, 2);    
        readEnvironmentalSensors(gDHT22_3, 3);            
    }   
}
  
void processByte(char ch)
{
    switch(ch)
    {        
        case 'i': //Return info about current HW state
            sendInfo();
        break;
        
        default: //Do nothing
            Serial << "[UNHANDLED_CHAR_RECEIVED:'"<<ch<<"']";
        break;                        
    }    
}

void sendInfo()
{
    Serial << "[ARRAYBOT SENSOR ARDUINO VERSION="<<sketchVersion<<"]";    
}

void readEnvironmentalSensors(DHT& s, int sensorNum)
{
    s.read();
    float h = s.readHumidity();
    float t = s.readTemperature();    
    if(isnan(h) || isnan(t))
    {
        Serial << "[DHT22_ERROR, READ_ERROR FOR SENSOR NR: " << sensorNum << "]";
    } 
    else
    {
        Serial << "[DHT22_DATA," << t << "," << h << "," << sensorNum << "]";
    }      
}
  

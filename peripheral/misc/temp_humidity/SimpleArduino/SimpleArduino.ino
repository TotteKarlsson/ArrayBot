#include <DHT22.h>
// Only used for sprintf
#include <stdio.h>

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("[DHT22 Library Demo]");
}

void loop(void)
{ 
  DHT22_ERROR_t errorCode;
  
  // The sensor can only be read from every 1-2s, and requires a minimum
  // 2s warm-up after power-on.
   
  //static int loopNr = 0;
 
  
  if(Serial.available() > 0)
  { 
    char ch = Serial.read();
    Serial.print("Thanks: "); 
    Serial.print(ch); 
    Serial.print('\n'); 
    //loopNr = 0;
  }
  
  errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      Serial.print("[DHT22_DATA,");
      Serial.print(myDHT22.getTemperatureC());      
      Serial.print(",");
      Serial.print(myDHT22.getHumidity());
      Serial.print("]");
    break;
      
    case DHT_ERROR_CHECKSUM:
      Serial.print("[check sum error ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%]");
      break;
      
    case DHT_BUS_HUNG:
      Serial.println("[BUS Hung]");
      break;
      
    case DHT_ERROR_NOT_PRESENT:
      Serial.println("[Not Present]");
      break;
      
    case DHT_ERROR_ACK_TOO_LONG:
      Serial.println("[ACK time out]");
      break;
      
    case DHT_ERROR_SYNC_TIMEOUT:
      Serial.println("[Sync Timeout]");
      break;
      
    case DHT_ERROR_DATA_TIMEOUT:
      Serial.println("[Data Timeout]");
      break;
      
    case DHT_ERROR_TOOQUICK:
      Serial.println("[Polled to quick]");
      break;
    default:
      Serial.println("[DHT22 Code not defined]");
      break;      
  }
}

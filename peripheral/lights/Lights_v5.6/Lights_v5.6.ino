/* 
This sketch expects an Adafruit Motor Shield for Arduino v2
---->	http://www.adafruit.com/products/1438
- Adjust LEDs by PWM on motor lines 1 (coax), 3 (front), 4 (back) - 
- Ver 5.5 TK added support for serial commands to control the lights
- and also read temperature and humidity.
*/

#include <Wire.h>
#include "Adafruit_MotorShield.h"
//#include "./utility/Adafruit_MS_PWMServoDriver.h"

//The DHT22 is a combined temp/humidity sensor
#include "DHT22.h"
// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7

// Setup a GLOBAL DHT22 instance
DHT22 gDHT22(DHT22_PIN);
void readEnvironmentalSensors(DHT22& gDHT22);

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

// Create the "motor" shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Name the "motor" ports by solenoid function:
Adafruit_DCMotor *coaxLEDs  = AFMS.getMotor(1);
Adafruit_DCMotor *frontLEDs = AFMS.getMotor(3);
Adafruit_DCMotor *backLEDs  = AFMS.getMotor(4);

  // Name the input lines by pushbutton order:
  int pushButton_1 = 2;
  int pushButton_2 = 3;
  int pushButton_3 = 4;
  int pushButton_4 = 5;
  int pushButton_5 = 6;

  //When controlling over Serial, the following
  //booleans are enabled
  bool btn1(false);
  bool btn2(false);  
  bool btn3(false);
  bool btn4(false);  
  bool btn5(false);    

  // create variables
  int flashFlag = false;
  int flashToggle = true;
  int flashInterval = 500;
  unsigned long flashMillis = millis();
  unsigned long lastReadTime = millis();
    
  void checkPINStates();
  void processByte(char ch); 
  
void setup() 
{
    AFMS.begin();  // create with the default frequency 1.6KHz
  
    // depower devices:
    coaxLEDs->run(RELEASE);
    frontLEDs->run(RELEASE);
    backLEDs->run(RELEASE);
       
    // set solenoid "on" duty cycles:
    coaxLEDs->setSpeed(32);
    frontLEDs->setSpeed(128);
    backLEDs->setSpeed(128);
     
    // set the pushbutton pins as inputs:
    pinMode(pushButton_1, INPUT); // Coax LEDs OFF
    pinMode(pushButton_2, INPUT); // Coax LEDs ON
    pinMode(pushButton_3, INPUT); // front&back OFF
    pinMode(pushButton_4, INPUT); // front&back ON
    pinMode(pushButton_5, INPUT); // front-back ALT

    // setup serial port
    Serial.begin(250000);
    Serial << "[ArrayBot Lights]";
}

void loop() 
{ 
    while(Serial.available() > 0)
    {         
        processByte(Serial.read());
    }    
   
    if (digitalRead(pushButton_1) || btn1 == true)
    {
        coaxLEDs->run(RELEASE);
        btn1 = false; 
    }
  
    if (digitalRead(pushButton_2) || btn2 == true)
    {
        coaxLEDs->run(FORWARD);
        btn2 = false; 
    }

    if (digitalRead(pushButton_3) || btn3 == true)
    {
        frontLEDs->run(RELEASE);
        backLEDs->run(RELEASE);
        flashFlag = false;
        btn3 = false; 
    }  

    if (digitalRead(pushButton_4) || btn4 == true)
    {
        frontLEDs->run(FORWARD);
        backLEDs->run(FORWARD);
        flashFlag = false;
        btn4 = false; 
    }

    if (digitalRead(pushButton_5) || btn5 == true)
    {
        flashFlag = true;
        flashToggle = true;
        flashMillis = millis();
        btn5 = false; 
    }

    if (flashFlag && (millis() >= flashMillis))
    {
        if (flashToggle)
        {
            frontLEDs->run(FORWARD);
            backLEDs->run(RELEASE);
            flashToggle = false;
        }
        else
        {
            frontLEDs->run(RELEASE);
            backLEDs->run(FORWARD);
            flashToggle = true;
        }
        flashMillis = millis() + flashInterval;
    }

    //Read digital lines and send status over serial port so the host
    //can update its UI
    unsigned long currentReadTime = millis();
    if(currentReadTime - lastReadTime > 3000)
    {
        checkPINStates();
        lastReadTime = currentReadTime;
    }
    
    //Read temp/humidity sensor, about every 2s.
      readEnvironmentalSensors(gDHT22);    
}
  
void processByte(char ch)
{
    switch(ch)
    {
        case '1':
            btn1 = true ;
            Serial << "[BUTTON_1_MSG]";
        break;
        
        case '2':
            btn2 = true ;
            Serial << "[BUTTON_2_MSG]";
        break;

        case '3':
            btn3 = true ;
            Serial << "[BUTTON_3_MSG]";
        break;

        case '4':
            btn4 = true ;
            Serial << "[BUTTON_4_MSG]";
        break;

        case '5':
            btn5 = true ;
            Serial << "[BUTTON_5_MSG]";
        break;
        
        case 'i': //Return some info about current state
            sendInfo();
        break;
        
        default: //Do nothing
            Serial << "[UNHANDLED_CHAR_RECEIVED:'"<<ch<<"']";
        ;
    }    
}

void checkPINStates()
{
    //Read and report states of "light pins"            
    Serial << ((digitalRead(1)) ? "[PIN_1=HIGH]" : "[PIN_1=LOW]");
    Serial << ((digitalRead(2)) ? "[PIN_2=HIGH]" : "[PIN_2=LOW]");    
    Serial << ((digitalRead(3)) ? "[PIN_3=HIGH]" : "[PIN_3=LOW]");    
    Serial << ((digitalRead(4)) ? "[PIN_4=HIGH]" : "[PIN_4=LOW]");
    Serial << ((digitalRead(5)) ? "[PIN_5=HIGH]" : "[PIN_5=LOW]");    
    Serial << ((digitalRead(6)) ? "[PIN_6=HIGH]" : "[PIN_6=LOW]"); 
    Serial << ((digitalRead(7)) ? "[PIN_7=HIGH]" : "[PIN_7=LOW]");    
    Serial << ((digitalRead(8)) ? "[PIN_8=HIGH]" : "[PIN_8=LOW]");        
}        

void sendInfo()
{
    Serial << "[VERSION=5.6]";    
}

void readEnvironmentalSensors(DHT22& s)
{
    switch(s.readData())
    {
        case DHT_ERROR_NONE:
            Serial << "[DHT22DATA," << s.getTemperatureC() << "," << s.getHumidity() << "]";
        break;

        //The following are error conditions. Pulling to quick happens easily, no need to report
        case DHT_ERROR_CHECKSUM:        Serial << "[DHT22_ERROR, Check Sum Error ";        break;
        case DHT_BUS_HUNG:              Serial << "[DHT22_ERROR, BUS Hung]";               break;
        case DHT_ERROR_NOT_PRESENT:     Serial << "[DHT22_ERROR, Not Present]";            break;
        case DHT_ERROR_ACK_TOO_LONG:    Serial << "[DHT22_ERROR, ACK Time out]";           break;
        case DHT_ERROR_SYNC_TIMEOUT:    Serial << "[DHT22_ERROR, Sync Timeout]";           break;
        case DHT_ERROR_DATA_TIMEOUT:    Serial << "[DHT22_ERROR, Data Timeout]";           break;
        case DHT_ERROR_TOOQUICK:        /*Serial << "[DHT22_ERROR, Polled to Quick]";*/    break;
        default:                        Serial << "[DHT22_ERROR, ERROR CODE NOT DEFINED]"; break;      
    }    
}
  

//Ribbon separator control code.  
//Uses a Hall effect sensor digital out to pin2, pin 13 output ot an LED, 
//and solenoid connected to Motor 1 terminals on Adafruit motor shield

#include <Wire.h>
#include "Adafruit_MotorShield.h"
#include <SoftwareSerial.h>

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Get port M1 address
Adafruit_DCMotor* gPufferValve = AFMS.getMotor(1);

// global variables (g)
bool            gSimulateHallSensor(false);
unsigned int    gSimulationSpeed    = 5000;

//Pins
const int       gHallSensorPin      = 2;    // Hall sensor pin
const int       gPufferPin          = 3;    // Pushbutton 1 pin
const int       gLedPin             = 13;   // LED pin, illuminates when solenoid is triggered 

//Leica mouse control
SoftwareSerial  leicaSerial(10, 11); // RX, TX

int             gPuffDuration       = 50;   // msec puffer on
int             gPufferValveSpeed   = 255;  // msec puffer on

bool            gEnablePuffer(false);
unsigned long   gLastReadTime = millis();
String          gLeicaMessage;

void setup() 
{
    AFMS.begin();  // create with the default frequency 1.6KHz

    // depower and set up puffer solenoid
    gPufferValve->run(RELEASE);
    gPufferValve->setSpeed(gPufferValveSpeed);
  
    // set up i/o pins
    pinMode(gHallSensorPin,     INPUT);     // Set up the Hall sensor pin to be an input
    pinMode(gLedPin,            OUTPUT);    // Set up the LED pin to be an output
    pinMode(gPufferPin,         INPUT);     // Set off the puffer manually by this pin    
    
    // setup HW serial port
    Serial.begin(250000);
    Serial << "[ArrayBot Puffer Arduino]";

    //setup SW serial port to the Leica Arduino.    
    leicaSerial.begin(9600);    
}

void loop() 
{    
    while(Serial.available() > 0)
    {    
        char ch = Serial.read();
        processByte(ch);
    }    

     if(leicaSerial.available())  
     {       
        //We get acknowledgments from the Leica. Just simply forward
        char ch = leicaSerial.read();
        if(ch == '[')
        {
            gLeicaMessage = "";    
        }
        else if(ch == ']')
        {
            Serial << "[LEICA MESSAGE: " << gLeicaMessage <<"]";            
        }
        else
        {
            gLeicaMessage += ch;    
        }        
     }
   
    //Simulate Hall Sensor
    if(gSimulateHallSensor == true)
    {
        simulateHallSensor();                 
    }
    else if(digitalRead(gHallSensorPin) == HIGH)  // if Hall sensor is high    
    {
        Serial << "[HALL_SENSOR=HIGH]";        
        digitalWrite(gLedPin, HIGH);     // turn the LED on        

        //Set off puffer, but only if enabled by the PUSH BUTTON or the HOST PC (enablePuffer)
        if (digitalRead(gPufferPin) || gEnablePuffer)
        {
            puff(gPuffDuration);
            gEnablePuffer = false;
        }
                            
        //Wait for HALL sensor to go LOW
        while(digitalRead(gHallSensorPin) == HIGH) 
        { }
        
        Serial << "[HALL_SENSOR=LOW]";
    }
    
    digitalWrite(gLedPin, LOW);      // turn the LED off       
}

void sendInfo()
{
    Serial << "[VERSION=2.5, PUFFER_DURATION=" << gPuffDuration << ", PUFFER_VALVE_SPEED=" << gPufferValveSpeed << "]\n";    
}

void puff(int duration_in_ms)
{
    gPufferValve->run(FORWARD);     // turn on solenoid
    delay(duration_in_ms);          //duration of LED/solenoid being on        
    gPufferValve->run(RELEASE);     // turn off solenoid    
}

void processByte(char ch)
{
    switch(ch)    
    {
        //Enable simulation
        case 'S':
        {
            //Get flag
            int flag = Serial.parseInt(); 
            gSimulateHallSensor = (flag == 1) ? true : false;        
        }
        break;
        
        //Set simulation speed
        case 's':
        {            
            int ms = Serial.parseInt(); 
            gSimulationSpeed = ms;        
        }
        break;

        //CutPreset (Leica)                  
        case 'P':   
        {
            //Get Preset
            int preset = Serial.parseInt(); //This one will wait for something that can become an int;
            if(preset > 0 && preset <= 5 )
            {               
               Serial << "[REQUEST_CUT_PRESET_"<<preset<<"]";                                                                   
               leicaSerial <<"P"<<preset<<" ";                                  
            }
            else
            {
                Serial << "[CUT_PRESET "<<preset<<" IS INVALID]";   
            }                                                         
        }
        break;            

        //Set delta Y on the Leica
        case 'Y':
        {
            //Get dy
            int preset = Serial.parseInt(); 
            
            Serial << "[REQUEST_DELTA_Y="<<preset<<"]";                                                                   
            leicaSerial <<"Y"<<preset<<" ";                                  
        }
        break;            
        
        //Enable puffing. When puffing is enabled, the logic in the loop will automatically set off the puffer
        //at the calibrated moment by checking the hall sensor state
        case 'e': 
            gEnablePuffer = true;
            Serial << "[PUFFER_ENABLED]";
        break;

        //Disable puffing. 
        case 'a': 
            gEnablePuffer = false;
            Serial << "[PUFFER_DISABLED]";
        break;

        //Set off the puffer
        case 'p': 
            puff(gPuffDuration);
            Serial << "[EXECUTED_PUFF]";
        break;

        //Set puffer duration
        case 'd': 
            //Next byte is the value
            gPuffDuration = Serial.parseInt(); 
            sendInfo();                
        break;                

        //Set puffer valve speed
        case 'v': 
            //Next byte is the value
            gPufferValveSpeed = Serial.parseInt(); 
            gPufferValve->setSpeed(gPufferValveSpeed);            
            sendInfo();                   
        break;                

        //Return some info about current state
        case 'i':    sendInfo();        break;
        case ' ': 
        case '\n': 
        case '\r':                      break;
        //Report unhandled character
        
        default: 
            Serial << "[Unhandled character in puffer arduino instream: "<<ch<<"]";        
        break;            
    }    
}
 
void simulateHallSensor()
{
    unsigned long currentTime = millis();
    if(currentTime - gLastReadTime > gSimulationSpeed)
    {
        gLastReadTime = currentTime;        
        Serial << "[HALL_SENSOR=HIGH]";                
        Serial << "[HALL_SENSOR=LOW]";                        
    }
}

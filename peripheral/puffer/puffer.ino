//Ribbon separator control code.  
//Uses a Hall effect sensor digital out to pin2, pin 13 output ot an LED, 
//and solenoid connected to Motor 1 terminals on Adafruit motor shield

#include <Wire.h>
#include "Adafruit_MotorShield.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Get port M1 address
Adafruit_DCMotor* gPufferValve = AFMS.getMotor(1);

// global variables (g)
bool            gSimulateHallSensor(true);
unsigned int    gTimeOut        = 500;
//Pins
const int       gHallSensorPin   = 2;    // Hall sensor pin
const int       gLedPin          = 13;   // LED pin, illuminates when solenoid is triggered 
const int       gPufferPin       = 3;    // Pushbutton 1 pin

//Leica mouse control
const int       gSetCutPreset0   = 4;
const int       gSetCutPreset1   = 5;
const int       gSetCutPreset2   = 6;
const int       gSetCutPreset3   = 7;
const int       gReadCutPreset0  = 9;
const int       gReadCutPreset1  = 10;
const int       gReadCutPreset2  = 11;
const int       gReadCutPreset3  = 12;

int             gPuffDuration    = 50;   // msec puffer on
int             gPufferValveSpeed= 255;  // msec puffer on

bool            gEnablePuffer(false);
unsigned long   gLastReadTime = millis();
String          gLeicaMessage;

//Use these booleans to avoid sending more than necessary messages to PC
bool            gSendCutPreset0Message(false);
bool            gSendCutPreset1Message(false);

//functions..

void simulateHallSensor();
void puff(int duration_in_ms);
void sendInfo();        
void processByte(char ch);           

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

    pinMode(gSetCutPreset0,     OUTPUT);    //Leica mouse control trough arduinos
    pinMode(gReadCutPreset0,    INPUT);

    pinMode(gSetCutPreset1,     OUTPUT);
    pinMode(gReadCutPreset1,    INPUT);

    // setup HW serial port
    Serial.begin(250000);
    Serial << "[ArrayBot Puffer Arduino]";

    //setup SW serial port to the Leica Arduino.    
    mySerial.begin(9600);    
}

void loop() 
{    
    while(Serial.available() > 0)
    {    
        char ch = Serial.read();
        processByte(ch);
    }    

     if(mySerial.available()) 
     {
        //We get acknowledgments from Leica. Just forward        
        char ch = mySerial.read() ;
        if(ch == '[')
        {
            gLeicaMessage = "";    
        }
        else if(ch == ']')
        {
            Serial << "[Leica Message: \"" << gLeicaMessage <<"\"]";            
        }
        else
        {
            gLeicaMessage += ch;    
        }        
     }

//    //Check, would be nice to use interupts, but uno only have 2 pins for such
//    if(digitalRead(gReadCutPreset0) == HIGH)
//    {
//        //Notify PC over serial that zero cut request was acknowledged
//        if(gSendCutPreset0Message == true)
//        {
//            Serial << "[CUT_PRESET_1=TRUE]";          
//            gSendCutPreset0Message = false;
//        }
//    }
//    
//    if(digitalRead(gReadCutPreset1) == HIGH)
//    {
//        //Notify PC over serial that zero cut request was acknowledged
//        if(gSendCutPreset1Message == true)
//        {
//            Serial << "[CUT_PRESET_2=TRUE]";          
//            gSendCutPreset1Message = false;
//        }
//    }    
    
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
        //CutPreset                   
        case 'P':   
        {
            //Get Preset
            int preset = Serial.parseInt(); //This one will wait for something that can become an int;
            if(preset > 0 && preset <= 5 )
            {               
               Serial << "[REQUEST_CUT_PRESET_"<<preset<<"]";                                                                   
               mySerial <<"P"<<preset<<" ";                                  
            }
            else
            {
                Serial << "[CUT_PRESET "<<preset<<" IS INVALID]";   
            }                                                         
        }
        break;            
        
        //Enable puffing
        case 'e': 
            gEnablePuffer = true;
            Serial << "[PUFFER_ENABLED]";
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
            Serial << "[Unhandled character in puffer instream: "<<ch<<"]";        
        break;            
    }    
}
 
void simulateHallSensor()
{
    unsigned long currentTime = millis();
    if(currentTime - gLastReadTime > 50)
    {
        gLastReadTime = currentTime;        
        Serial << "[HALL_SENSOR=HIGH]";                
        Serial << "[HALL_SENSOR=LOW]";                        
    }
}

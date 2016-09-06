
//Ribbon separator control code.  
//Uses a Hall effect sensor digital out to pin2, pin 13 output ot an LED, 
//and solenoid connected to Motor 1 terminals on Adafruit motor shield

#include <Wire.h>
#include "Adafruit_MotorShield.h"

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Get port M1 address
Adafruit_DCMotor* gPufferValve = AFMS.getMotor(1);

// global variables (g)

//Pins
const int       gSensorPin       = 2;    // Hall sensor pin
const int       gLedPin          = 13;   // LED pin, illuminates when solenoid is triggered 
const int       gPufferPin       = 3;    // Pushbutton 1 pin

//Leica mouse control
const int       gSetZeroCutPin   = 4;
const int       gReadZeroCutPin  = 12;
const int       gSetCutPreset1   = 5;
const int       gReadCutPreset1  = 11;

int             gPuffDuration    = 50;   // msec puffer on
int             gPufferValveSpeed= 255;  // msec puffer on

bool            gEnablePuffer(false);
unsigned long   gLastReadTime = millis();
bool            gSimulateHallSensor(true);

//Use these booleans to avoid sending more than necessary messages to PC
bool            gSendZeroCutMessage(false);
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
    pinMode(gSensorPin,         INPUT);     // Set up the Hall sensor pin to be an input
    pinMode(gLedPin,            OUTPUT);    // Set up the LED pin to be an output
    pinMode(gPufferPin,         INPUT);     // Set off the puffer manually by this pin    

    pinMode(gSetZeroCutPin,     OUTPUT);    //Leica mouse control trough arduinos
    pinMode(gReadZeroCutPin,    INPUT);

    pinMode(gSetCutPreset1,     OUTPUT);
    pinMode(gReadCutPreset1,    INPUT);

    // setup serial port
    Serial.begin(250000);
    Serial << "[ArrayBot Puffer Arduino]";
}

void loop() 
{    
    while(Serial.available() > 0)
    {         
        processByte(Serial.read());
    }    

    //Simulate Hall Sensor
    if(gSimulateHallSensor == true)
    {
        simulateHallSensor();                 
    }
    else if(digitalRead(gSensorPin) == HIGH)  // if Hall sensor is high    
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
        while(digitalRead(gSensorPin) == HIGH) 
        { }
        
        Serial << "[HALL_SENSOR=LOW]";
    }
    
    digitalWrite(gLedPin, LOW);      // turn the LED off       

    if(digitalRead(gReadZeroCutPin) == HIGH)
    {
        //Notify PC over serial that zero cut request was acknowledged
        if(gSendZeroCutMessage == true)
        {
            Serial << "[ZERO_CUT=TRUE]";          
            gSendZeroCutMessage = false;
        }
    }
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
        //Set digital output lines
        case 'Z':            
            if(Serial.parseInt())
            {
                digitalWrite(gSetZeroCutPin, HIGH);                
                Serial << "[PIN_"<<gSetZeroCutPin<<" -> HIGH]";
                gSendZeroCutMessage = true;                                                
            }
            else
            {
                digitalWrite(gSetZeroCutPin, LOW);
                Serial << "[PIN_"<<gSetZeroCutPin<<" -> LOW]";                
            }            
        break;            
                    
        case 'C':            
            if(Serial.parseInt() == 1) 
            { 
                digitalWrite(gSetCutPreset1, HIGH);
                Serial << "[PIN_"<<gSetCutPreset1<<" -> HIGH]";                                                
                gSendCutPreset1Message = true;                                                                                
            }
            else
            {
                digitalWrite(gSetCutPreset1, LOW);
                Serial << "[PIN_"<<gSetCutPreset1<<" -> LOW]";                                
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
        case 'i': 
            sendInfo();
        break;

        //Report unhandled character
        default: 
            Serial << "Unhandled character in puffer instream: "<<ch;        
        break;            
    }    
}

void simulateHallSensor()
{
    unsigned long currentTime = millis();
    if(currentTime - gLastReadTime > 5000)
    {
        gLastReadTime = currentTime;        
        Serial << "[HALL_SENSOR=HIGH]";                
        Serial << "[HALL_SENSOR=LOW]";                        
    }
}

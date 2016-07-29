
//Ribbon Separator control code.  
//Uses a Hall effect sensor digital out to pin2, pin 13 output ot an LED, 
//and solenoid connected to Motor 1 terminals on Adafruit motor shield
#include <Wire.h>
#include "Adafruit_MotorShield.h"

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Get port M1 address
Adafruit_DCMotor *pufferValve = AFMS.getMotor(1);

// global variables
const int       sensorPin       = 2;    // Hall sensor pin
const int       ledPin          = 13;   // LED pin, illuminates when solenoid is triggered
  
const int       pufferPin       = 3;    // Pushbutton 1 pin
int             puffDuration    = 50;   // msec puffer on
int             pufferValveSpeed= 255;   // msec puffer on
bool            enablePuffer;
unsigned long   lastReadTime = millis();

void setup() 
{
    AFMS.begin();  // create with the default frequency 1.6KHz

    // depower and set up puffer solenoid
    pufferValve->run(RELEASE);
    pufferValve->setSpeed(pufferValveSpeed);
  
    // set up i/o pins
    pinMode(sensorPin, INPUT);      // Set up the Hall sensor pin to be an input
    pinMode(ledPin,    OUTPUT);     // Set up the LED pin to be an output
    pinMode(pufferPin, INPUT);      // Set off the puffer manually by this pin    

    // setup serial port
    Serial.begin(250000);
    Serial << "[ArrayBot Puffer Init]";
}

void puff(int duration_in_ms);
void sendInfo();        
void processByte(char ch);           

void loop() 
{    
    while(Serial.available() > 0)
    {         
        processByte(Serial.read());
    }    

    //Simulate Hall Sensor
    unsigned long currentTime = millis();
    if(currentTime - lastReadTime > 50)
    {
        lastReadTime = currentTime;        
        Serial << "[HALL_SENSOR=HIGH]";                
        Serial << "[HALL_SENSOR=LOW]";                        
    }
        
    if(digitalRead(sensorPin) == HIGH)  // if Hall sensor is high    
    {
        Serial << "[HALL_SENSOR=HIGH]";        
        digitalWrite(ledPin, HIGH);     // turn the LED on        

        //Set off puffer, if enabled by push button or host pc
        if (digitalRead(pufferPin) || enablePuffer)
        {
            puff(puffDuration);
            enablePuffer = false;
        }
                            
        //Wait for HALL sensor to go LOW
        while(digitalRead(sensorPin) == HIGH) 
        { }
        
        Serial << "[HALL_SENSOR=LOW]";
        digitalWrite(ledPin, LOW);      // turn the LED off        
    }
    else
    {
        digitalWrite(ledPin, LOW);      // turn the LED off
    }   
}

void sendInfo()
{
    Serial << "[VERSION=2.5, PUFFER_DURATION=" << puffDuration << ", PUFFER_VALVE_SPEED=" << pufferValveSpeed << "]\n";    
}

void puff(int duration_in_ms)
{
    pufferValve->run(FORWARD);      // turn on solenoid
    delay(duration_in_ms);          //duration of LED/solenoid being on        
    pufferValve->run(RELEASE);      // turn off solenoid    
}

void processByte(char ch)
{
    switch(ch)
    {
        case 'p': //Enable puffing
            enablePuffer = true;
            Serial << "[PUFFER_ENABLED]";
        break;

        case 'd': //Set puffer duration
            //Next byte is the value
            puffDuration = Serial.parseInt(); 
            sendInfo();                
        break;                

        case 'v': //Set puffer valve speed
            //Next byte is the value
            pufferValveSpeed = Serial.parseInt(); 
            pufferValve->setSpeed(pufferValveSpeed);            
            sendInfo();                   
        break;                

        case 'i': //Return some info about current state
            sendInfo();
        break;
        
        default: //Do nothing
        ;
    }    
}

// Ribbon Separator control code.  
//Uses a Hall effect sensor digital out to pin2, pin 13 output ot an LED, 
//and solenoid connected to Motor 1 terminals on Adafruit motor shield

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Get port M1 address
Adafruit_DCMotor *pufferValve = AFMS.getMotor(1);

// create global variables
  const int sensorPin       = 2;    // Hall sensor pin
  const int enablePin       = 3;    // Pushbutton 1 pin
  const int ledPin          = 13;   // LED pin, illuminates when solenoid is triggered
  int       puffDelay       = 10;   // msec delay from hall trigger to puff start
  int       puffDuration    = 50;   // msec puffer on

void setup() 
{
    AFMS.begin();  // create with the default frequency 1.6KHz

    // depower and set up puffer solenoid
    pufferValve->run(RELEASE);
    pufferValve->setSpeed(255);
  
    // set up i/o pins
    pinMode(sensorPin, INPUT); // Set up the Hall sensor pin to be an input
    pinMode(enablePin, INPUT); // Set up the Hall sensor pin to be an input
    pinMode(ledPin,    OUTPUT);   // Set up the LED pin to be an output
}

void loop() 
{
    digitalWrite(ledPin, LOW);   // Turn off the LED  sensorState = digitalRead(sensorPin);  // Read Hall effect sensor

    if(digitalRead(sensorPin) == HIGH)  // if Hall sensor is high    
    {
        delay(puffDelay);            //wait before turning on led and solenoid
        digitalWrite(ledPin, HIGH);  // turn the LED on
        if (digitalRead(enablePin))
        {
            pufferValve->run(FORWARD); // turn on solenoid
        }
        
        delay(puffDuration);         //duration of LED/solenoid being on
    
        digitalWrite(ledPin, LOW);   // turn the LED off
    
        pufferValve->run(RELEASE);   // turn off solenoid
    
        while(digitalRead(sensorPin) == HIGH)
        { }
    }
    else
    {
        digitalWrite(ledPin, LOW);  // turn the LED off
    }
}

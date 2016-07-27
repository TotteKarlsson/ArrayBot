/* 
This sketch expects an Adafruit Motor Shield for Arduino v2
---->	http://www.adafruit.com/products/1438
- Adjust LEDs by PWM on motor lines 1 (coax), 3 (front), 4 (back) - 
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the "motor" shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Name the "motor" ports by solenoid function:
Adafruit_DCMotor *coaxLEDs = AFMS.getMotor(1);
Adafruit_DCMotor *frontLEDs = AFMS.getMotor(3);
Adafruit_DCMotor *backLEDs = AFMS.getMotor(4);

// Name the input lines by pushbutton order:
  int pushButton_1 = 2;
  int pushButton_2 = 3;
  int pushButton_3 = 4;
  int pushButton_4 = 5;
  int pushButton_5 = 6;

// create variables
  int flashFlag = false;
  int flashToggle = true;
  int flashInterval = 500;
  unsigned long flashMillis = millis();
  
      
void setup() {
  AFMS.begin();  // create with the default frequency 1.6KHz
  
  // depower devices:
  coaxLEDs->run(RELEASE);
  frontLEDs->run(RELEASE);
  backLEDs->run(RELEASE);
       
  // set solenoid "on" duty cycles:
  coaxLEDs->setSpeed(32);
  frontLEDs->setSpeed(32);
  backLEDs->setSpeed(32);
     
  // set the pushbutton pins as inputs:
  pinMode(pushButton_1, INPUT); // Coax LEDs OFF
  pinMode(pushButton_2, INPUT); // Coax LEDs ON
  pinMode(pushButton_3, INPUT); // front&back OFF
  pinMode(pushButton_4, INPUT); // front&back ON
  pinMode(pushButton_5, INPUT); // front-back ALT
}

void loop() {
  if (digitalRead(pushButton_1))
    coaxLEDs->run(RELEASE);
  
  if (digitalRead(pushButton_2))
    coaxLEDs->run(FORWARD);

  if (digitalRead(pushButton_3))
  {
    frontLEDs->run(RELEASE);
    backLEDs->run(RELEASE);
    flashFlag = false;
  }  

  if (digitalRead(pushButton_4))
  {
    frontLEDs->run(FORWARD);
    backLEDs->run(FORWARD);
    flashFlag = false;
  }

  if (digitalRead(pushButton_5))
  {
    flashFlag = true;
    flashToggle = true;
    flashMillis = millis();
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
}
  
  

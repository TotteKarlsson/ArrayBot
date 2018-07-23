/* 
This sketch expects an Adafruit Motor Shield for Arduino v2
---->	http://www.adafruit.com/products/1438
- Adjust LEDs by PWM on motor line 3 (front)
- Removed sensor reads
*/
/*March 2017 - TK removed all coax logic, preparing to add sensor code
 * 
*/

double sketchVersion = 1.1;
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the "motor" shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Name the "motor" ports by solenoid function:
Adafruit_DCMotor *frontLEDs = AFMS.getMotor(3);

  // Name the input lines by pushbutton order:
  int pushButton_OFF = 4;
  int pushButton_ON = 5;

  int LEDOn = false;

  //When controlling over Serial, the following
  //booleans are enabled 
  bool btn3(false); //Turn off LEDs
  bool btn4(false); //Turn on LEDs  
  
  //To control light intensity
  int frontLEDDrive(128);
  void processByte(char ch); 

  //Allow nice syntax for serial printing
  template<class T> inline Print &operator <<(Print &o, T arg) { o.print(arg); return o; }
  
void setup() 
{
    AFMS.begin();  // create with the default frequency 1.6KHz
  
    // depower devices:
    frontLEDs->run(RELEASE);
    LEDOn = false;
         
    // set solenoid "on" duty cycles:    
    frontLEDs->setSpeed(frontLEDDrive);
         
    // set the pushbutton pins as inputs:
    pinMode(pushButton_OFF, INPUT); // LED OFF
    pinMode(pushButton_ON,  INPUT); // LED ON
    
    // setup serial port
    Serial.begin(19200);
    Serial << "[ARRAYBOT LIGHTS VERSION="<<sketchVersion<<"]";        
    sendInfo();    
}

void loop() 
{ 
    while(Serial.available() > 0)
    {         
        processByte(Serial.read());
    }    
       
    //We only care for when these goes from low -> high
    if (digitalRead(pushButton_OFF) || btn3 == true)
    {
        btn3 = false;         
        if(LEDOn == true)
        {            
            frontLEDs->run(RELEASE);
            LEDOn = false;                        
            sendInfo();                            
        }        
    }  
    
    if (digitalRead(pushButton_ON) || btn4 == true)
    {
        btn4 = false;                
        if(LEDOn == false)
        {
            frontLEDs->run(FORWARD);        
            LEDOn = true;
            sendInfo();                
        }
    }        
}
  
void processByte(char ch)
{
    switch(ch)
    {
        case '3':            btn3 = true ;        break;
        case '4':            btn4 = true ;        break;
                
        case 'f':
            frontLEDDrive = Serial.parseInt();
            frontLEDs->setSpeed(frontLEDDrive);
            sendInfo();            
        break;
        
        case 'i': //Return info about current HW state
            sendInfo();
        break;
        
        default: //Do nothing
            Serial << "[UNHANDLED_CHAR_RECEIVED:'"<<ch<<"']";        
    }    
}

void sendInfo()
{
    Serial << "[AB_LIGHTS_DATA," << "LED_DRIVE="<<frontLEDDrive<<", LED_ON=" <<   (LEDOn ? "TRUE" : " FALSE") << "]";        
}
  

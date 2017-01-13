double sketchVersion = 1.0;
void processByte(char ch); 

int gNROfMessages = 2;
const char* gMessages[] = {"!Test1", "!Test2"};
int gMessageIndex = 0;

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &o, T arg) { o.print(arg); return o; }

int gSimulationSpeed        = 1000;
unsigned long gLastReadTime = millis();

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

    unsigned long currentTime = millis();
    if(currentTime - gLastReadTime > gSimulationSpeed)
    {
        gLastReadTime = currentTime;        
        Serial << gMessages[gMessageIndex++]<<'\n';
        if(gMessageIndex > (gNROfMessages -1))
        {
            gMessageIndex = 0;    
        }    
    } 
}
  
void processByte(char ch)
{
    switch(ch)
    {
        //Set simulation speed        
        case 's':
        {
            int ms = Serial.parseInt(); 
            gSimulationSpeed = ms;                    
        }
        break;
        
        case 'i': //Return info about current HW state
            sendInfo();
        break;
        
        default: //Do nothing
            Serial << "[UNHANDLED_CHAR_RECEIVED:'"<<ch<<"']";
        ;
    }    
}

void sendInfo()
{
    Serial << "[YC& DUMMY VERSION="<<sketchVersion<<"]";    
    
    
  
}
  

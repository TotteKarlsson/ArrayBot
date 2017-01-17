double sketchVersion = 1.0;
void processByte(char ch); 

int gNROfMessages = 50;
const char* gMessages[] = 
{
"þ5CA4",
"!18F0F8",
"!1423010000C8",
"!1540FF03A9",
"!1420FF000000CD",
"!1430FF01453C3B",
"!1440FF037B002F",
"!1440FF037AC070",
"!1423010000C8",
"!153001006456",
"!1531010BB8F6",
"!15200101C9",
"!1540FF02AA",
"!1540FF00AC",
"!1540FF01AB",
"!1540FF03A9",
"!1540FF02AA",
"!1540FF00AC",
"!1540FF01AB",
"!1540FF03A9",
"!1540FF02AA",
"!1540FF00AC",
"!1540FF01AB",
"!1540FF03A9",
"!15200000CB",
"!1440FF03792908",
"!1440FF03767FB5",
"!1440FF037640F4",
"!1430FF01453B3C",
"!1430FF01453443",
"!1430FF01452B4C",
"!1430FF01451F58",
"!1430FF01451661",
"!1430FF01450A6D",
"!1430FF01450374",
"!1430FF01450275",
"!1430FF01450176",
"!1430FF01450077",
"!1430FF01450176",
"!1430FF01450275",
"!1430FF01450374",
"!1430FF01450671",
"!1430FF0145086F",
"!1430FF0145096E",
"!1430FF01450A6D",
"!1430FF01450B6C",
"!1430FF01450C6B",
"!1430FF01450D6A",
"!14230103E8DD",
"!1423010000C8",
"!142301004682"
};

int gMessageIndex = 0;

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &o, T arg) { o.print(arg); return o; }

int gSimulationSpeed        = 1000;
unsigned long gLastReadTime = millis();

void setup() 
{
    // setup serial port
    Serial.begin(19200);    
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
        Serial << gMessages[gMessageIndex++]<<'\r';
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
            Serial << "!UNHANDLED_CHAR_RECEIVED:'"<<ch<<"'\r";
        ;
    }    
}

void sendInfo()
{
    Serial << "!UC7 DUMMY VERSION="<<sketchVersion<<'\r';              
}
  


double sketchVersion = 1.0;
void processByte(char ch); 

int gNROfMessages = 6;
const char* gMessages[] = 
{
//"þ5CA4",
//"!18F0F8",
//"!1423010000C8",
//"!1540FF03A9",
//"!1420FF000000CD",
//"!1430FF01453C3B",
//"!1440FF037B002F",
//"!1440FF037AC070",
//"!1423010000C8",
"!153001006456",
"!1531010BB8F6",
//"!15200101C9",
//"!1540FF02AA",
//"!1420FF0033A4F6",
"!1540FF00AC",
"!1540FF01AB",
"!1540FF03A9",
"!1540FF02AA",
//"!1540FF00AC",
//"!1540FF01AB",
//"!1540FF03A9",
//"!15200000CB",
//"!1440FF03792908",
//"!1440FF03767FB5",
//"!1440FF037640F4",
//"!1430FF01453B3C",
//"!1430FF01453443",
//"!1430FF01452B4C",
//"!1430FF01451F58",
//"!1430FF01451661",
//"!1430FF01450A6D",
//"!1430FF01450374",
//"!1430FF01450275",
//"!1430FF01450176",
//"!1430FF01450077",
//"!1430FF01450176",
//"!1430FF01450275",
//"!1430FF01450374",
//"!1430FF01450671",
//"!1430FF0145086F",
//"!1430FF0145096E",
//"!1430FF01450A6D",
//"!1430FF01450B6C",
//"!1430FF01450C6B",
//"!1430FF01450D6A",
//"!14230103E8DD",
//"!1423010000C8",
//"!142301004682" 
};

int gMessageIndex = 0;

//Allow nice syntax for serial printing
template<class T> inline Print &operator <<(Print &o, T arg) { o.print(arg); return o; }

unsigned long   gSimulationSpeed        = 1000;
//unsigned long   gSimulationSpeed        = 60;
bool            gHasMessage            = false;
String          gMessage;
unsigned long   gLastReadTime = millis();

class UC7
{
    public:
        UC7() : mMotorStatus(0), mFeedRate(100){}
        int mMotorStatus;
        int mFeedRate;
};

UC7 gUC7;

void setup() 
{
    // setup serial port
    Serial.begin(19200);    
}

void loop() 
{    
    static char buffer[80];
    if (readline(Serial.read(), buffer, 80) > 0) 
    {
        String msg(buffer);
        handleMessage(msg);
    }
    
    unsigned long currentTime = millis();
    if(currentTime - gLastReadTime > gSimulationSpeed)
    {
        gLastReadTime = currentTime;    
        if(gUC7.mMotorStatus == 1)
        {    
            Serial << gMessages[gMessageIndex++]<<'\r';
            if(gMessageIndex > (gNROfMessages -1))
            {
                gMessageIndex = 0;    
            }    
        }
    } 
}
 
void handleMessage(String& msg)
{
    if(msg == "!5120018E") //Turn ON Cutting motor
    {
        gUC7.mMotorStatus = 1;
        Serial << "!15200101C9\r";    
        msg = "";
    }                   
    else if(msg == "!5120008F") //Turn OFF Cutting motor
    {
        gUC7.mMotorStatus = 0;
        Serial << "!15200000CB\r";    
        msg = "";
    }
    else if(msg == "!5120FF90") //Ask for Cutting motor status
    {
        if(gUC7.mMotorStatus == 1)
        {
            Serial << "!1520FF01CB\r";    
        }    
        else
        {
            Serial << "!1520FF00CC\r";    
        }
    }
    else if(msg == "!41230100009B") //Zero Cut
    {
        gUC7.mFeedRate = 0;            
        Serial << "!1423FF0000CA\r";                            
    }
    
    else if(msg == "!412301006437") //100 nm cut
    {
        gUC7.mFeedRate = 100;           
        Serial << "!1423FF006466\r"; 
    }

    else if(msg == "!4123FF9D") //Ask for Current FeedRate
    {
        if(gUC7.mFeedRate == 100)
        {
            Serial << "!1423FF006466\r";
        }
        else
        {
            Serial << "!1423FF0000CA\r";            
        }
    }
    else if(msg == "!4130FF90") //Request for knifestage position
    {
        Serial << "!1430FF00AEB55A\r";
    }
    else
    {
        Serial << "!18F300F5"<<'\r';  
    }
    msg = ""  ;
    gHasMessage = false;
}

int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) 
  {
    switch (readch) 
    {
      case '\n': // Ignore new-lines
        break;
        
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
        
      default:
        if (pos < len-1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  
  // No end of line has been found, so return -1.
  return -1;
}

void sendInfo()
{
    Serial << "!UC7 DUMMY VERSION="<<sketchVersion<<'\r';              
}
  

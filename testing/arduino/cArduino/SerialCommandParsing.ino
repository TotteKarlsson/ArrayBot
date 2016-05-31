char BUFFER[256] = {0}; //main Buffer
int bufferSize = 0; //Size of the buffer
int bufferFill = 0; //Number of bytes written to the buffer.
boolean NewRead = 0; //If the data has been changed, this becomes true.
int iRead = 0; //Read Index

int iter = 0; //General int used for counting loops.
int temp = 0; //
int charTemp = NULL;

char ReadByte;        //stores a byte to check, rather than reading directly from serial buffer.

char CommandByte = 0;

int ValueBytes[64];
int ValueBytesIndex = 0;
int ValueBytesSize = sizeof(ValueBytes);




//---------------------------------------------------

/*
Checks for serial input. Reads said input for instructions.

'i': starts reading from serial buffer to buf[]
's': stops reading from buffer.

Returns the number of bytes written.

*/


int Record(char buf[]) 
{
  ReadByte = Serial.read();
  if(ReadByte == '[')
  {
    while(Serial.available() ==0);
    
    ReadByte = Serial.read();
        
    iter = 0;
    while( (ReadByte != ']') & (Serial.available() < bufferSize) ) // Read bytes into buffer until ']' is detected or the buffer is full.
    {
      if (Serial.available()>0)
      { 
        buf[iter] = ReadByte;
        ReadByte = Serial.read();
        iter++;
      }
    }
    Serial.flush();
  }
  
  Serial.flush();
  NewRead = 1; //To show that new data is now available.
  return iter;
}

//----------------------------------------

void showBuffer(char buf[], int bufFill)
{
  for(iter = 0; iter < bufFill; iter++)
  {
    Serial.print(buf[iter]);
  }
  Serial.println();
}

//Echo Code

void echoCode(char msg, int val)
{
    Serial.print("[!");
    Serial.print(msg);
    Serial.print("(");
    Serial.print(val);
    Serial.print(")]");
}

//---------------------------------------
//Interpreters

int Number(char buf[], int &index)
{
      temp = 0;
      
      for(; (BUFFER[index] != ',') && (BUFFER[index] != ')') ; index++)
      {
        temp = (temp * 10) + (BUFFER[index]-'0');  
      }
    return temp;
}


void DoCommand(char cmd, int values[])
{
  switch(cmd)
  {
    case 'a': //pinMode
              if(values[1] == 0)
              { 
              pinMode(values[0], OUTPUT);
              }
              else
              {
                pinMode(values[0], INPUT);
              }
              echoCode('A', 1);
              break;
              
    case 'b': //digitalWrite
              if(values[1] == 0)
              {
                digitalWrite(values[0],LOW);
              }
              else
              {
                digitalWrite(values[0],HIGH);
              }
              echoCode('A', 1);
              break;
              
    case 'c': //analogWrite
              analogWrite(values[0], values[1]);
              echoCode('A', 1);
              break;
              
    case 'd': //digitalRead
              echoCode('D', digitalRead(values[0]));
              break;  
              
    case 'e': //analogRead
              echoCode('E', analogRead(values[0]));
              break;    
    case 'f':
              break;
    case 'g':
              break;
    case 'h':
              break;
    case 'z':
              echoCode('A', 1);
              break;    
  }
}








//--------------------------------------

void setup() {
Serial.begin(115200);

bufferSize = sizeof(BUFFER);

}

//---------------------------------------

void loop() {
  
 if(Serial.available() > 0)
 {
    bufferFill = Record(BUFFER);
 }
  
  
 if(NewRead == 1) //Read Data
 {
    iRead = 0;
    memset(ValueBytes,'0',ValueBytesSize);
    ValueBytesIndex = 0;
    CommandByte = 0;
    
    
    while(iRead < bufferFill) //While buffer unread
    {
     switch(BUFFER[iRead])  // switch command
      {
        case '(':
                  iRead++;
                  while(BUFFER[iRead] != ')')
                  {
                    ValueBytes[ValueBytesIndex] = Number(BUFFER, iRead);
                    ValueBytesIndex++;
                    iRead++;
                  }
                  break;
        case '!':
                  iRead++;
                  CommandByte = BUFFER[iRead];
                  iRead++;
                  break;
        default:
                  iRead++;
          
      } //* switch command
    } //* While buffer unread
    
    DoCommand(CommandByte, ValueBytes);
    memset(BUFFER,0,bufferSize);
    NewRead = 0;
 } //* Read Data

  
}

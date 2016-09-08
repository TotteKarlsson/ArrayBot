#include <Mouse.h>

//Allow easy syntax for serial printing
template<class T> inline Print &operator <<(Print &o, T arg) {o.print(arg); return o;}

//moveSize is the (pixel?) size of the steps taken 
//when moving the mouse cursor to a particular position
const int moveSize      = 10;
const int preset0AckPin = 4;
const int preset1AckPin = 5;
const int preset1pin    = 3;
const int preset0pin    = 2;
   
void setup() {  
  // Prepare led + buttons
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(preset0AckPin, OUTPUT);
  pinMode(preset1AckPin, OUTPUT);
  pinMode(preset1pin, INPUT_PULLUP);
  pinMode(preset0pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(preset0pin), setPresetZero, RISING);
  attachInterrupt(digitalPinToInterrupt(preset1pin), setPresetOne, RISING);
  Serial1.begin(9600);
  Mouse.begin();  
  Serial1 <<"[LeicaUC7-Serial]";
}

void loop() {
    if(Serial1.available() > 0){
        //Handle "commands": P1, P2..P5 and C1,C2
        //Client should end each command with a non-numeric character 
        //to avoid wasted time in the parseInt function        
        char ch = Serial1.read();

        if(ch == 'P' || ch == 'C'){            
            int preset = Serial1.parseInt();      
            
            switch (ch){            
                //change cut thickness by preset
                case 'P': setPreset(preset);        break;
    
                //start or stop cutting                         
                case 'C': startStopCutting(preset); break;               
                
                default: //For debugging..
                    Serial1 << "\n[Invalid input: "<<ch<<"]\n";
                break;                                  
            }
    
            //Response
            Serial1 << "[" << ch << preset << "]";                                                        
        }
    }
}

//The following preset are 1-5 corresponding to the 5 'thickness' buttons
//on the Leica UI. 1 -> zero thickness, 5 -> 1000 nm
void setPreset(int preset){
    if(preset > 0 && preset <= 5){
        resetPos();
        delay(2);
        moveAbsXY(5,155-13*(preset - 1));
        Mouse.click();
    }
}

void resetPos(){
  Mouse.move(-100,-100,0);
  delay(2);
  Mouse.move(-100,-100,0);
  delay(2);
  Mouse.move(-100,-100,0);
  delay(2);
  Mouse.move(-100,-100,0);
}

void moveHorz(int pos){
  int here = 0;
  while (here<pos){
    if ((pos-here)<moveSize){
      Mouse.move(pos-here,0,0);
      here=pos;
    }
    else{
      Mouse.move(moveSize,0,0);
      here=here+moveSize;
    }
  }
}

void moveVert(int pos){
  int here = 0;
  while (here<pos){
    if ((pos-here)<moveSize){
      Mouse.move(0,pos-here,0);
      here=pos;
    }
    else{
      Mouse.move(0,moveSize,0);
      here=here+moveSize;
    }
  }
}

void moveAbsXY(int x, int y){
  resetPos();
  moveHorz(x);
  moveVert(y);
}

//1 == startCutting, anything else == stopCutting
void startStopCutting(int i){
    if(i == 1){
        startCutting();        
    }
    else{    
        stopCutting();
    }
}

void setPresetZero(){
  digitalWrite(preset0AckPin,LOW);
  setPreset(1);
  delay(2000);
  digitalWrite(preset0AckPin,HIGH);
}

void setPresetOne(){
  digitalWrite(preset1AckPin,LOW);
  setPreset(2);
  delay(2000);
  digitalWrite(preset1AckPin,HIGH);
}

void startCutting(){
  resetPos();
}

void stopCutting(){
  resetPos();
}

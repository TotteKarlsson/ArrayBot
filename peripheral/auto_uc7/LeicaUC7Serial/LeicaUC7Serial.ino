#include <Mouse.h>

//Allow easy syntax for serial printing
template<class T> inline Print &operator <<(Print &o, T arg) {o.print(arg); return o;}

//moveSize is the size of the steps taken when 
//moving the mouse cursor to a particular position
const int moveSize      = 10;

//DeltaY is steps taken between presets
const int gDeltaY       = 15;

//Hardware interface
const int preset0pin    = 2;
const int preset0AckPin = 4;
const int preset1pin    = 3;
const int preset1AckPin = 5;
  
void setup() {  
  // Prepare led + buttons
  pinMode(LED_BUILTIN,      OUTPUT);
  pinMode(preset0AckPin,    OUTPUT);
  pinMode(preset1AckPin,    OUTPUT);
  
  pinMode(preset0pin,       INPUT_PULLUP);
  pinMode(preset1pin,       INPUT_PULLUP);
    
  attachInterrupt(digitalPinToInterrupt(preset0pin), setPresetOne, RISING);
  attachInterrupt(digitalPinToInterrupt(preset1pin), setPresetTwo, RISING);

  //Main interface is Serial1 (Pin 0 == Rx, Pin 1 == Tx)
  Serial1.begin(9600);
  Mouse.begin();  
  Serial1 <<"[LeicaUC7-Serial]";
}

void loop() {
    if(Serial1.available() > 0){
        //Handle "commands": P1, P2..P5
        //Client should end each command with a non-numeric character 
        //to avoid wasted time in the parseInt function below                
        char ch = Serial1.read();

        if(ch == 'P' || ch == 'C'){            
            //parseInt is not so nice, returns 0 on timeout.    
            int preset = Serial1.parseInt();      
            
            switch (ch){            
                //change cut thickness by preset
                case 'P': setPreset(preset);        break;
    
                default: //For debugging..
                    Serial1 << "[Invalid input: "<<ch<<"]\n";
                break;                                  
            }
    
            //Response
            Serial1 << "[" << ch << preset << "]";                                                        
        }
    }
}

//Valid presets, 1-5 corresponds to the 5 'thickness' buttons
//on the Leica UI. 1 -> zero thickness, 5 -> 1000 nm
void setPreset(int preset){
  if(preset > 0 && preset <= 5){
    resetPos();
    delay(2);        
    moveAbsXY(5, 155 - gDeltaY*(preset - 1));
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

void setPresetOne(){
  digitalWrite(preset0AckPin,LOW);
  setPreset(1);
  delay(2000);
  digitalWrite(preset0AckPin,HIGH);
}

void setPresetTwo(){
  digitalWrite(preset1AckPin,LOW);
  setPreset(2);
  delay(2000);
  digitalWrite(preset1AckPin,HIGH);
}

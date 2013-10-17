#define SENSOR_LINE    0   //ATtiny Pin 5 = I2C SDA
#define ACTOR_LINE     2   //ATtiny Pin 7 = I2C SCK on DS1621  & GPIO

#define LED  1      // ATtiny Pin 6
#define BUTTON 3    // ATtiny Pin 2

int push, pushPre;

boolean signalSent = false;

float pulse = 0;
float pulseAddition = 0.01f;

void setup()
{
    pinMode(SENSOR_LINE, INPUT);
    pinMode(ACTOR_LINE, INPUT);
    
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    push = pushPre = 1;    // 1 == nicht gedrückt - 0 == gedrückt
}

void loop()
{   
   if (!signalSent){
       
       if (checkButton() == true) {
           sendSignal();    // sets signalSent to true
       } else {
           doPulse();
       }
       
   } else if (signalSent){
       
       if (checkActorLine() == true) { // actor has finished
           signalSent = false;
           pinMode(SENSOR_LINE, INPUT);
       }
   }
}



boolean checkButton()
{   
    // debounce
    if (digitalRead(BUTTON) == pushPre) {
        push = pushPre;
    }
    pushPre = digitalRead(BUTTON);
    
    
    
    if (push == 1){    // no push detected
        return false;
    } else {    // push detected
        return true;
    }
}


void sendSignal()
{
    digitalWrite(LED, HIGH);
        
    pinMode(SENSOR_LINE, OUTPUT);
    digitalWrite(SENSOR_LINE, LOW);
    
    signalSent = true;
}
        
   

boolean checkActorLine()
{
    if (digitalRead(ACTOR_LINE) == LOW){
        return true;
    } else {
        return false;
    }
}

void doPulse()
{
    analogWrite(LED, pulse);
    pulse += pulseAddition;
    if (pulse >= 250){
        pulseAddition = -pulseAddition;
    } 
    else if (pulse <= 0){
        pulseAddition = -pulseAddition;
    }
}




void blink_debug(byte times){ // poor man's display
    for (byte i=0; i< times; i++){
        digitalWrite(LED,HIGH);
        delay (100);
        digitalWrite(LED,LOW);
        delay (40);
    }
}
    
    

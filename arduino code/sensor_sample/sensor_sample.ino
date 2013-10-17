#define SENSOR_LINE    0   //ATtiny Pin 5 = I2C SDA
#define ACTOR_LINE     2   //ATtiny Pin 7 = I2C SCK on DS1621  & GPIO

#define LED  1      // ATtiny Pin 6
#define SENSOR 3    // ATtiny Pin 2

boolean signalSent = false;

float pulse = 0;
float pulseAddition = 0.01f;

void setup()
{
    pinMode(SENSOR_LINE, INPUT);
    pinMode(ACTOR_LINE, INPUT);
    
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
}

void loop()
{
    if ( digitalRead(SENSOR_LINE) == LOW ) {
        digitalWrite(LED, HIGH);
        delay(2000);
        digitalWrite(LED, LOW);
    } else {
        doPulse();
    }
}



boolean checkSensor()
{   
    
    
    return false;
    // read sensor value
    // analyze data
    // decide whether to return true or false
}


// sensor has detected something - actors are being notified
void sendSignal()
{
    digitalWrite(LED, HIGH);
        
    pinMode(SENSOR_LINE, OUTPUT);
    digitalWrite(SENSOR_LINE, LOW);
    
    signalSent = true;
}
        
   
// check whether actors are finished
boolean checkActorLine()
{
    if (digitalRead(ACTOR_LINE) == LOW){
        return true;
    } else {
        return false;
    }
}

// breathing light as feedback of waiting for signal
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



// whenever something is wrong: blink
void blink_debug(byte times){ // poor man's display
    for (byte i=0; i< times; i++){
        digitalWrite(LED,HIGH);
        delay (100);
        digitalWrite(LED,LOW);
        delay (40);
    }
}
    
    

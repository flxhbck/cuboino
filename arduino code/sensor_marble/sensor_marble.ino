#define SENSOR_LINE    2   //ATtiny Pin 5 = I2C SDA
#define ACTOR_LINE     0   //ATtiny Pin 7 = I2C SCK on DS1621  & GPIO

#define LED  1      // ATtiny Pin 6
#define SENSOR 3    // ATtiny Pin 2

#define SENSOR_THRESHOLD 80
float sensorValue, sensorCalib;

boolean signalSent = false;

float pulse = 0;
float pulseAddition = 0.1f;

void setup()
{
    pinMode(SENSOR_LINE, INPUT);
    pinMode(ACTOR_LINE, INPUT);
    
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    checkConnections();
    
    calibrateSensor();
}



void loop()
{   
   if (!signalSent){
       
       if (checkLight(true) == true) {
           sendSignal();    // sets signalSent to true
       } else {
           doPulse();
       }
       
   } else if (signalSent){
       
       if (checkActorLine() == true) { // actor has finished
           signalSent = false;
           pinMode(SENSOR_LINE, INPUT);
           calibrateSensor();
       }
   }
}


void calibrateSensor()
{
    delay(100);
    sensorCalib = analogRead(SENSOR);
    delay(50);
    sensorCalib += analogRead(SENSOR);
    sensorCalib /= 2;
}



boolean checkLight(boolean start)
{   
    sensorValue = analogRead(SENSOR);
        
    if( (sensorValue - sensorCalib) > SENSOR_THRESHOLD ){
        //debounce
        if (debounceCheckLight() == true){
            return true;
        } else {
            return false;
        }   
    }
    else {
        sensorCalib = sensorCalib*0.99 + sensorValue*0.01;
        return false;
    }
}


boolean debounceCheckLight()
{
    
    sensorValue = analogRead(SENSOR);
        
    if( (sensorValue - sensorCalib) > SENSOR_THRESHOLD ){
        return true;
    } else {
        return false;
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


/***********
    DEBUG
*************/

void checkConnections() // check whether the communication lines are high
{
    while (  (digitalRead(SENSOR_LINE) == LOW) ||
             (digitalRead(ACTOR_LINE) == LOW) ) {
         blink_debug(4);
    }
}
    


void blink_debug(byte times)    // poor man's display
{ 
    for (byte i=0; i< times; i++){
        digitalWrite(LED,HIGH);
        delay (100);
        digitalWrite(LED,LOW);
        delay (40);
    }
}
    
    

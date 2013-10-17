// use with high-low tech bootloader!!
// otherwise delay does not work.

#include <Servo8Bit.h>

#define SENSOR_LINE    0   //ATtiny Pin 5 = I2C SDA
#define ACTOR_LINE     2   //ATtiny Pin 7 = I2C SCK on DS1621  & GPIO

#define LED  3      // ATtiny Pin 6
#define SERVO 1    // ATtiny Pin 2

Servo8Bit myServo;
int servoPosition;
boolean responseSent = false;

float pulse = 0;
float pulseAddition = 0.01f;


void setup()
{
    pinMode(SENSOR_LINE, INPUT);
    pinMode(ACTOR_LINE, INPUT);
    
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    myServo.attach(SERVO);
    servoPosition = 10;
    myServo.write(servoPosition);
    
}


void loop()
{    

    if (!responseSent){
        
        if (checkSensorLine() == false){ // no signal from sensor
            doPulse();
        } else {    // signal Received
            activateShunting();
            sendResponse();
        }
    } else {
        
        if(checkSensorLine() == true){ // sensor has not seen response
            doPulse();
        } else {    // sensor has seen response
            responseSent = false;
            pinMode(ACTOR_LINE, INPUT);
        }
        
    }
            
        
        
}

boolean checkSensorLine()
{
    if ( digitalRead(SENSOR_LINE) == HIGH ) { 
        return false;
    } else {
        return debounceCheck();
    }
}

boolean debounceCheck()
{
    delay(100);
    if ( digitalRead(SENSOR_LINE) == HIGH ) { 
        return false;
    } else {
        return true;
    }
}
    


void activateShunting()
{   
    digitalWrite(LED, HIGH);
    
    if (servoPosition == 10){
        servoPosition = 100;
    } else if (servoPosition == 100){
        servoPosition = 10;
    }
    
    moveServo(servoPosition, 3000);
   
    
}

void sendResponse()
{       
    pinMode(ACTOR_LINE, OUTPUT);
    digitalWrite(ACTOR_LINE, LOW);
    
    responseSent = true;
    
    delay(1000);
}
    
    
    
    
void moveServo(int pos, int sTime){
    
    delay(20);
    
    myServo.write(pos);
    delay(sTime);
    
}


void blink_debug(byte times){ // poor man's display
    for (byte i=0; i< times; i++){
        digitalWrite(LED,HIGH);
        delay (100);
        digitalWrite(LED,LOW);
        delay (40);
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

#define SENSOR_LINE    0   //ATtiny Pin 5 = I2C SDA
#define ACTOR_LINE     2   //ATtiny Pin 7 = I2C SCK on DS1621  & GPIO

#define LED  1      // ATtiny Pin 6
#define SPEAKER 3    // ATtiny Pin 2

boolean responseSent = false;

float pulse = 0;
float pulseAddition = 0.01f;


void setup()
{
    pinMode(SENSOR_LINE, INPUT);
    pinMode(ACTOR_LINE, INPUT);
    
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    pinMode(SPEAKER, OUTPUT);
}


void loop()
{    
    if (!responseSent){
        
        if (checkSensorLine() == false){ // no signal from sensor
            doPulse();
        } else {    // signal Received
            activateSound();
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


void activateSound()
{
    digitalWrite(LED, HIGH);
    
    tone(SPEAKER, 262);
    delay(3000);
    noTone(SPEAKER);
}

void sendResponse()
{
        
    pinMode(ACTOR_LINE, OUTPUT);
    digitalWrite(ACTOR_LINE, LOW);
    
    responseSent = true;
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

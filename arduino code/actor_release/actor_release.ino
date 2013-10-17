#define SENSOR_LINE    2   //ATtiny Pin 5 = I2C SDA
#define ACTOR_LINE     0   //ATtiny Pin 7 = I2C SCK on DS1621  & GPIO

#define LED  1      // ATtiny Pin 6
#define SOLENOID 3  // ATtiny Pin 2

boolean responseSent = false;

float pulse = 0;
float pulseAddition = 0.01f;


void setup()
{
    pinMode(SENSOR_LINE, INPUT);
    pinMode(ACTOR_LINE, INPUT);
    
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    
    pinMode(SOLENOID, OUTPUT);
    digitalWrite(SOLENOID, LOW);
}


void loop()
{    
    if (!responseSent){
        
        if (checkSensorLine() == false){ // no signal from sensor
            doPulse();
        } else {    // signal Received
            activateSolenoid();
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
        return true;
    }
}


void activateSolenoid()
{
    digitalWrite(LED, HIGH);
    
    digitalWrite(SOLENOID, HIGH);
    delay(50);
    digitalWrite(SOLENOID, LOW);
    delay(2950);
}

void sendResponse()
{       
    pinMode(ACTOR_LINE, OUTPUT);
    digitalWrite(ACTOR_LINE, LOW);
    
    responseSent = true;
    
    delay(500);
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

int relay = 8;
volatile byte relayState = LOW;

int COINinterrupt=2;

long lastdetectiontime=0;
long chargingTIME=60000; //defining the charging time

void setup() {
  // put your setup code here, to run once:
pinMode(relay, OUTPUT);
digitalWrite(relay, HIGH);
pinMode(COINinterrupt, INPUT);
attachInterrupt(digitalPinToInterrupt(COINinterrupt), detectCoin, RISING); //start charging after detecting the coin
Serial.begin(9600); 
}

//coin is detected when the relay state goes high
void detectCoin()
{
 Serial.println("Coin detected");
    if(relayState == LOW)
    {
        digitalWrite(relay, LOW);
    }
    relayState = HIGH;
    Serial.println("ON");
    lastdetectiontime = millis();
}


  // put your main code here, to run repeatedly:
void loop()
{
if((millis() - lastdetectiontime) > chargingTIME && relayState == HIGH){
    digitalWrite(relay, HIGH);
    relayState = LOW;
    Serial.println("OFF");
}
}

int relay = 8;
volatile byte relayState = LOW;

int COINinterrupt=2;

long lastdetectiontime=0;
long chargingTIME=60000;

void setup() {
  // put your setup code here, to run once:
pinMode(relay, OUTPUT);
digitalWrite(relay, HIGH);
pinMode(COINinterrupt, INPUT);
attachInterrupt(digitalPinToInterrupt(COINinterrupt), detectCoin, RISING);
Serial.begin(9600); 
}

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

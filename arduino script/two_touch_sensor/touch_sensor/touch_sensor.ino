int cap=2;
int cap1=3;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(cap,INPUT);
 pinMode(cap1,INPUT);
 digitalWrite(cap,LOW);
 digitalWrite(cap1,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(cap)== LOW) 
    {  Serial.println("No one is present at sensor1 ");
    }
    else
    Serial.println("Someone is present at sensor1");
    
 if(digitalRead(cap1)== LOW) 
  {  Serial.println("No one is present sensor2");
    }
    else
    Serial.println("Someone is present sensor2");
    delay(1000); 
}
// LDR







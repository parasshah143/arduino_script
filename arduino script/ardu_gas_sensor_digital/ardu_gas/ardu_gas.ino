int gas=2;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(gas,INPUT);
 digitalWrite(gas,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(gas)== HIGH) 
    {  
    Serial.println("No gas");
 //  delay(1000);
    }
    else
    Serial.println("Gas detected");
  delay(1000); 
}

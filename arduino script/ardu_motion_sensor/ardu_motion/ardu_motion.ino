int pir=2;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(pir,INPUT);
 digitalWrite(pir,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pir)== HIGH) 
    {  Serial.println("motion detected");
 //     delay(1000);
    }
    else
    Serial.println("no motion");
  delay(1000); 
}

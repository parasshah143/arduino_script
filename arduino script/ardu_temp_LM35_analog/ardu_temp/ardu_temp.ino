float aval = 0;
float temp=0;
float voltage=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  aval=analogRead(A0);
delay(1000);
//Serial.println(aval);
voltage = ((aval*5000)/1024);
Serial.println(voltage);
temp=(aval/2);
Serial.println(temp);
}

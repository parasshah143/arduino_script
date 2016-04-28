float val=0;
float ldr=0;
float voltage;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
val=analogRead(A0);
//Serial.println(val);
voltage = ((val*5)/1024);
Serial.print("voltage is ");
Serial.println(voltage);
delay(1500);
if(val>= 0 && voltage<= 1)
Serial.print("between 0-25 percent and ");
else if(voltage>1 && voltage<=2)
Serial.print("between 25-50 percent and ");
else if(voltage>2&& voltage<=3)
Serial.print("between 50-75 percent and ");
else if(voltage>3&& voltage<=4)
Serial.print("between 75-100 percent and ");
else if(voltage>4&& voltage<=5)
Serial.print("between 75-100 percent and ");
}

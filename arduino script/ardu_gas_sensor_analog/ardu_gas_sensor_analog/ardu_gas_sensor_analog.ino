float val=0;
float gas=0;
float voltage;
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
}
void loop()
{
// put your main code here, to run repeatedly:
// Gas low value with out detection is arond 120
// Gas high value with detection is above 600
val=analogRead(A0);
//Serial.println(val);
voltage = (val);
Serial.print("voltage is ");
Serial.println(voltage);
delay(1500);
if(voltage>= 600)
Serial.print("Maximum Gas is presnet 100%");
else if(voltage>200 && voltage<=599)
Serial.print("Minimum Gas is detected 50%");
else if(voltage>100 && voltage<=199)
Serial.print("Gas is not detected 0% ");
//else if(voltage>3&& voltage<=4)
//Serial.print("between 75-100 percent and ");
//else if(voltage>4&& voltage<=5)
//Serial.print("between 75-100 percent and ");
}

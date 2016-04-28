#include <EEPROM.h>
int i  =0;
int add = 0 ;
int data = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  data = EEPROM.read(add);
 Serial.print("Data at zero location is: ");
 Serial.println(data);
 delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
 i++;
 Serial.println(i);
 EEPROM.write(add, i);
 delay(1000);
}

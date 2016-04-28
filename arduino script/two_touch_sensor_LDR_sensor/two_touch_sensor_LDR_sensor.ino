// For touch sensor 
int cap=2;
int cap1=3;

float val=0;
float ldr=0;
float voltage;

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
    {  Serial.println(">>>  No one is present at sensor1 ");
    }
    else
    Serial.println(">>>  Someone is present at sensor1");
    
 if(digitalRead(cap1)== LOW) 
  {  Serial.println("No one is present sensor2");
    }
    else
    Serial.println("Someone is present sensor2");
      
 
  val=analogRead(A0);
  Serial.println(val);
  voltage = ((val*5)/1024);
  //Serial.print("voltage is ");
//  Serial.println(voltage);

  if(val>= 0 && voltage<= 1)
  Serial.print("between 0-25 percent \n ");
  else if(voltage>1 && voltage<=2)
  Serial.print("between 25-50 percent \n");
  else if(voltage>2&& voltage<=3)
  Serial.print("between 50-75 percent \n ");
  else if(voltage>3&& voltage<=4)
  Serial.print("between 75-100 percent \n");
  else if(voltage>4&& voltage<=5)
  Serial.print("between 75-100 percent \n");

  delay(5000);  
  }

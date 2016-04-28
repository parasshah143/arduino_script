/* 3/11/15
 * Final working for MQTT+IR+PIR+Ultrasonic+dht22+LDR
 * AP config to be added later 
 */ 

/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN D3   
#define DHTTYPE DHT22  // DHT 22  (AM2302)

// Update these with values suitable for your network.

const char* ssid = "TARAL SHAH1";
const char* password = "taralshah123";
const char* mqtt_server = "192.168.1.102";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
unsigned int flag2 = 0;
int Pin = 14; //D5 IR
int Pin1 = 12 ;// D6 PIR
float val=0;


float ldr=0; //ldr
float voltage;
//Ultrasonic
const int trigPin = 4;  // D2
const int echoPin = 5;  // D1
int flag = 0;
int flag1 = 0;
int j = 0;
void setd();
void humidity();
// defines variables
long duration;
int distance;
int fdistance;
int dis[5];
int i = 0;
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
   pinMode(Pin, INPUT);
  pinMode(Pin1,INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//  pinMode(led, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
//  digitalWrite(led, LOW);
  Serial.print("Distance: ");
  Serial.print("setd ");
  Serial.println("DHTxx test!");
   
   dht.begin();
   setd();
  

//  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("topic", "hello world");
      // ... and resubscribe
      client.subscribe("test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 2) {
 lastMsg = now;
   humidity();
 
 if( digitalRead(Pin) == HIGH ) // IR detect
  {
      j++;
      delay(250);
      Serial.println(j); 
      snprintf (msg, 75, "%ld",j);
      client.publish("topic", msg);
      Serial.println("Entry"); 
  }

    if( digitalRead(Pin1) == HIGH ) // PIR
  {
      client.publish("topic", "Motion");
      Serial.println("Motion"); 
  }

//Ultrasonic part
    // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH); 

  // Calculating the distance
  distance= duration*0.034/2;  

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance < fdistance)
//  if(distance < 250)
  {
//  digitalWrite(led, HIGH);
  Serial.println("valid");
  client.publish("topic", "Ultrasonic detected");
  //Serial.println("Ultrasonic detected"); 
  }
  else
  {
//    digitalWrite(led, LOW);
    Serial.println("invalid");
  }
  delay(1000);
//Ultrasonic finish
  }
 val=analogRead(A0);
//Serial.println(val);
voltage = ((val*5)/1024);
//Serial.print("voltage is ");
//Serial.println(voltage);
delay(1500);
if(val>= 0 && voltage<= 1)
Serial.println("between 0-25 percent");
else if(voltage>1 && voltage<=2)
Serial.println("between 25-50 percent");
else if(voltage>2&& voltage<=3)
Serial.println("between 50-75 percent");
else if(voltage>3&& voltage<=4)
Serial.println("between 75-100 percent");
else if(voltage>4&& voltage<=5)
Serial.println("between 75-100 percent");


}  
void humidity()
{
   delay(2000);
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

      // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
    snprintf (msg, 75, "%ld",t);
//  client.publish("topic", msg);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
 
}


void setd(){

  for(i = 0; i<=5;i++)
  {
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH); 
  
    // Calculating the distance
    distance= duration*0.034/2;  
  
    // Prints the distance on the Serial Monitor
    dis[i] = distance;
    Serial.print("Distance: ");
    Serial.println(i);
    Serial.println(dis[i]);
    Serial.println(" ");
    delay(2000);
   }
  Serial.println("Loop finished ");
  fdistance = (dis[0]+dis[1]+dis[2]+dis[3]+dis[4])/5;
  Serial.println(fdistance);
}



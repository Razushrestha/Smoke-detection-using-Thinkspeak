#include <ESP8266WiFi.h>
//#define ledpin D0;
const int ledpin = 16;
const int buzzer = 5;
#include <Servo.h>
Servo servo;

//Wifi Cedentials

const char* ssid = "InG OD 2.4";  // your SSID

const char* password = "ONETWOTHREEFOUR"; // your wIFi password


//Thingspeak


String apiKey = "LPX3BX6WJEUAGUXT"; // API key

const char* server = "api.thingspeak.com";




WiFiClient client;


float temp;


void setup()

{
pinMode(A0,INPUT);
pinMode(ledpin,OUTPUT);
pinMode(buzzer,OUTPUT);

servo.attach(5); //D1
servo.write(0);

 //delay(2000);
Serial.begin(115200);

delay(10);

Serial.println("Connecting to ");

Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)

{

delay(10);

Serial.print(".");

}

Serial.println("");

Serial.println("WiFi connected");

}

void loop()

{
int temp = analogRead(A0);


//temp = (reading);
if(temp>=22)
{
  servo.write(90);
  delay(1000);

  servo.write(0);

  delay(1000);
  
  digitalWrite(ledpin,HIGH);
  delay(5000);
  digitalWrite(ledpin,LOW);
  delay(5000);
  pinMode(buzzer,HIGH);
  delay(5000);
  pinMode(buzzer,LOW);
  delay(5000);
  
  
  
}
if (isnan(Level))

{

Serial.println("Failed to read from MQ-2 sensor!");

return;

}

 

if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com

{

    String postStr = apiKey;

    postStr +="&field1=";

    postStr += String(temp);

    postStr += "\r\n\r\n";

 

    client.print("POST /update HTTP/1.1\n");

    client.print("Host: api.thingspeak.com\n");

    client.print("Connection: close\n");

    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");

    client.print("Content-Type: application/x-www-form-urlencoded\n");

    client.print("Content-Length: ");

    client.print(postStr.length());

    client.print("\n\n");

    client.print(postStr);

Serial.print("Gas, Smoke, Air Level: ");

Serial.println(temp);

Serial.println("Data Send to Thingspeak");

}

delay(100);

client.stop();

Serial.println("Waiting...");

 

// thingspeak needs minimum 15 sec delay between updates.

delay(1500);

}

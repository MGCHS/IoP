/*************************************************************
Download latest Blynk library here: https://github.com/blynkkk/blynk-library/releases/latest
Blynk is a platform with iOS and Android apps to control Arduino, Raspberry Pi and the likes over
the Internet. You can easily build graphic interfaces for all your projects by simply dragging and
dropping widgets.
Downloads, docs, tutorials: http://www.blynk.cc
Blynk library is licensed under MIT license
*************************************************************
This example shows how value can be pushed from Arduino to the Blynk App.
WARNING :
For this example you'll need Adafruit DHT sensor libraries:
https://github.com/adafruit/Adafruit_Sensor
https://github.com/adafruit/DHT-sensor-library
App project setup:
Value Display widget a0ached to V5
Value Display widget a0ached to V6
*************************************************************/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
// You should get Auth Token in the Blynk App.
char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
int Sensorvalue=0;
int sensorPin=A0;
int sensorValuePercent=0;
// This funcGon sends Arduino's up Gme every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
int x = analogRead(A0);
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
Serial.println(t);
Serial.print(h);
Serial.println("%");

Blynk.virtualWrite(V5, h);
Blynk.virtualWrite(V6, t);


if (x<200)
{
Blynk.notify("Water your plants");
}
}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
dht.begin();
// Setup a function to be called every second
timer.setInterval(1000, sendSensor);
}
void loop()
{
Blynk.run();
timer.run();
}


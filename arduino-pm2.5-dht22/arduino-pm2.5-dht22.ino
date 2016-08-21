#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

int measurePin = 6;
int ledPower = 12;
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0;
 
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  dht.begin();
}
 
void loop(){
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin); // read the dust value
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  //calcVoltage = voMeasured * (5.0 / 1024);
 
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  //dustDensity = (0.17 * calcVoltage - 0.12)*1000;
 
  //Serial.print("Raw Signal Value (0-1023): ");
  //Serial.print(voMeasured);
 
  Serial.print("PM2.5:");
  Serial.println(voMeasured);
 
  //Serial.print(" Density:");
  //Serial.print(dustDensity);
  
  float h = dht.readHumidity();
   float t = dht.readTemperature();
    Serial.print("Humidity:");
  Serial.println(h);
  Serial.print("Temperature:");
  Serial.println(t);
   
 
  delay(5000);
}

#include <RunningMedian.h>


#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


DHT dht(DHTPIN, DHTTYPE);
RunningMedian measurements = RunningMedian(20);
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
  long start = millis();
  
  //Varje mätning tar 10ms. samplar 100 gånger under 1 sekund
  for(int x=0; x<20; x++){
    digitalWrite(ledPower,LOW); // power on the LED
    delayMicroseconds(samplingTime);
   
    //voMeasured = analogRead(measurePin); // read the dust value
    measurements.add(analogRead(measurePin));
      
    delayMicroseconds(deltaTime);
    digitalWrite(ledPower,HIGH); // turn the LED off
    delayMicroseconds(sleepTime); //10ms totalt
    delay(90); //100ms
  }//2sekunder
 
  Serial.print("PM2.5:");
  Serial.println(measurements.getMedian());
  Serial.println(measurements.getLowest());
  Serial.println(measurements.getHighest());
 
  //Serial.print(" Density:");
  //Serial.print(dustDensity);
  delay(1000); //3sek
  float h = dht.readHumidity();
   float t = dht.readTemperature();
  
    Serial.print("Humidity:");
  Serial.println(h);
  delay(100);
  Serial.print("Temperature:");
  Serial.println(t);
   
 long time = millis()-start;
 Serial.print("Iteration time:");
 Serial.println(time);
  //delay(1900); //5sek totalt
  delay(60000-time); //55 sek
}

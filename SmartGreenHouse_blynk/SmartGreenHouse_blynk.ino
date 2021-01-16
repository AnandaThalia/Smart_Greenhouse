#include "DHT.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define DHTPIN D3 
#define DHTTYPE DHT11 
long duration, distance;

int pinLED1 = D2;
int pinLED2 = D6;
int pinLDR = A0;
int echoPin = D4;
int trigPin = D5;

char auth[] = "1hr07HOTrw70EADsecoOY3qRunOD284A";
char ssid[] = "AndroidAP03E9";
char pass[] = "AnandaThalia";

DHT dht(DHTPIN, DHTTYPE);

void waterSprinkle() {
  delay(2000);
  int h = dht.readHumidity();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%   "));
  Blynk.virtualWrite(V0, "Humidity (%)");
  Blynk.virtualWrite(V1, h);
  
  if ( h < 90){    
    Serial.println("water prinkle ON!");
    } else {
    Serial.println("water prinkle OFF!");
    }  
    delay(400); 
    Blynk.run();
}

void jendela() {
  delay(2000);
  int t = dht.readTemperature();
  Serial.print(F("Temperatur: "));
  Serial.print(t);
  Serial.print(F("C   "));
  Blynk.virtualWrite(V2, "Temperatur (C)");
  Blynk.virtualWrite(V3, t);
  
  if ( t > 34){    
    Serial.println("Buka jendela!");
      } else {
    Serial.println("Tutup jendela!");
      } 
    delay(400); 
    Blynk.run(); 
}

void lampu(){
  int nilaiLDR = analogRead(pinLDR);
  Serial.print(nilaiLDR);
  if (nilaiLDR < 150 ){
    Serial.println("    Lampu nyala");
    digitalWrite(pinLED1, HIGH);
    }else{
    Serial.println("    Lampu mati");
    digitalWrite(pinLED1, LOW);
    }
  
  }

void air(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(8);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(8);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(8);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  Serial.print(distance);
  delay(50);

  Blynk.virtualWrite(V4, "Kekosongan Air");
  Blynk.virtualWrite(V5, distance);
  
  if(distance > 8 ){
    Serial.println("    isi air");
    digitalWrite(pinLED2, HIGH);
    } else {
    Serial.println("    air aman");
    digitalWrite(pinLED2, LOW);
    }
   delay(400); 
    Blynk.run(); 
  }

void setup() {
  Serial.begin(9600);
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLDR, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  }

void loop(){
  waterSprinkle();
  jendela();
  lampu();
  air();
  Serial.println("   ");
  Serial.println("    ");
  delay(2000);
}

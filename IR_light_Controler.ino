#include <IRremote.h>
#include "LowPower.h"

IRsend irsend;

//int pinBuzzer = 2; 
int IRSensor = 5;
int Human = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(IRSensor, INPUT);
  //pinMode(pinBuzzer, OUTPUT);
  //pinMode(LED, OUTPUT);
}

void loop() {
  int sensorValue = digitalRead(IRSensor);
  int pr = analogRead(A0);
  
  if ( sensorValue == 1 ) {
    if (Human == 0) {
      if (pr > 600) {
        //digitalWrite(LED, HIGH);
        Serial.println("Case1_1: No Humen in the room, Humen detected, turn light ON, wait for 60s");
        //digitalWrite(pinBuzzer, HIGH);
        //delay(200);
        //digitalWrite(pinBuzzer, LOW);
        //delay(200);
        Serial.print("SensorValue = ");
        Serial.println(sensorValue);
        irsend.sendNEC(0x1FE807F, 32);
        delay(60000);
        Human = 1;
        }
     if (pr < 600) {
      Serial.println("Case1_2: No Humen in the room, Humen detected, but it's daytime, DO NOT need to turn light ON");
      Serial.print("pr = ");
      Serial.println(pr);
      Serial.println("PowerOff for 8s");
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
      //delay(10000);
     }
    }
    
    if (Human == 1) {
      //digitalWrite(LED, HIGH);
      Serial.println("Case2: Humen in the room, Humen detected, DO NOT touch light, wait for 60s");
      Serial.print("SensorValue = ");
      Serial.println(sensorValue);
      delay(60000);
    } 
  }
  
  if ( sensorValue == 0 ) {
    if (Human == 0) {
      Serial.println("Case4: No Humen in the room, No Humen detected, Do NOT touch light");
      Serial.print("SensorValue = ");  
      Serial.println(sensorValue);
      Serial.println("PowerOff for 2s!");
      LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
    }
    if (Human == 1) {
      //digitalWrite(pinBuzzer, HIGH);
      //delay(200);
      //digitalWrite(pinBuzzer, LOW);
      //delay(200);
      //digitalWrite(pinBuzzer, HIGH);
      //delay(200);
      //digitalWrite(pinBuzzer, LOW);
      Serial.println("Case3: No Humen detected, Humen left the room, turn light OFF");
      Serial.print("SensorValue = ");  
      Serial.println(sensorValue);
      irsend.sendNEC(0x1FE807F, 32);
      Human = 0;
    }
  }
  delay(2000);
}

#include <IRremote.h>
#include "LowPower.h"
#include <virtuabotixRTC.h>

IRsend irsend;

//int pinBuzzer = 2; 
int IRSensor = 5;
int Human = 0;
int dark_model = 0;

//Wiring SCLK -> 6, I/O -> 7, CE -> 8
//Or CLK -> 6 , DAT -> 7, Reset -> 8
virtuabotixRTC myRTC(6, 7, 8); //If you change the wiring change the pins here also

void setup() {
  Serial.begin(9600);
  pinMode(IRSensor, INPUT);
  //pinMode(A0, INPUT); //photoresistor
  //pinMode(pinBuzzer, OUTPUT);

  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(00, 38, 18, 2, 9, 10, 2019); //Here you write your actual time/date as shown above 
  // but remember to "comment/remove" this function once you're done
  // The setup is done only one time and the module will continue counting it automatically
}

void loop() {
  myRTC.updateTime();
  Serial.print("Current Time: ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.println(myRTC.minutes);  

  /*                                                          
  Serial.print("Current Date / Time: ");                                                                 
  Serial.print(myRTC.dayofmonth);                                                                        
  Serial.print("/");                                                                                     
  Serial.print(myRTC.month);                                                                             
  Serial.print("/");                                                                                   
  Serial.print(myRTC.year);                                                                          
  Serial.print("  ");                                                                                   
  Serial.print(myRTC.hours);                                                                           
  Serial.print(":");                                                                                    
  Serial.print(myRTC.minutes);                                                                          
  Serial.print(":");                                                                                  
  Serial.println(myRTC.seconds);
  */         
  
  int sensorValue = digitalRead(IRSensor);
  int timenow = myRTC.hours;
  //int pr = analogRead(A0);
  
  if ( sensorValue == 1 ) {
    if (Human == 0) {
      //if (pr > 600) {

      if (timenow >= 0 && timenow < 6) {
        //digitalWrite(LED, HIGH);
        Serial.println("Case1_1: No Humen in the room, Humen detected, turn light ON, wait for 60s");
        //digitalWrite(pinBuzzer, HIGH);
        //delay(200);
        //digitalWrite(pinBuzzer, LOW);
        //delay(200);
        //Serial.print("SensorValue = ");
        //Serial.println(sensorValue);
        irsend.sendNEC(0x1FEA05F, 32);
        delay(60000);
        Human = 1;
        dark_model = 1;
        }

      if (timenow >= 6 && timenow <= 9) {
        if (dark_model == 0) {
          Serial.println("Case1_1: No Humen in the room, Humen detected, turn light ON, wait for 60s");
          //digitalWrite(pinBuzzer, HIGH);
          //delay(200);
          //digitalWrite(pinBuzzer, LOW);
          //delay(200);
          //Serial.print("SensorValue = ");
          //Serial.println(sensorValue);
          irsend.sendNEC(0x1FE807F, 32);
          delay(180000);
          Human = 1;
          }
        if (dark_model == 1) {
          Serial.println("Case1_1: No Humen in the room, Humen detected, turn light ON, wait for 60s");
          //digitalWrite(pinBuzzer, HIGH);
          //delay(200);
          //digitalWrite(pinBuzzer, LOW);
          //delay(200);
          //Serial.print("SensorValue = ");
          //Serial.println(sensorValue);
          irsend.sendNEC(0x1FE807F, 32);
          for (int i=0; i<15; ++i){
            irsend.sendNEC(0x1FE48B7, 32);
            delay(40);
          }
          delay(180000);
          Human = 1;
          dark_model = 0;
          }
        }

      if (timenow > 9 && timenow < 18 ) {
        Serial.println("Case1_2: No Humen in the room, Humen detected, but it's daytime, DO NOT need to turn light ON");
        //Serial.print("pr = ");
        //Serial.println(pr);
        //Serial.println("PowerOff for 8s");
        //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
        delay(60000);
        }

      if (timenow >= 18 && timenow <= 24) {
        if (dark_model == 0) {
          Serial.println("Case1_1: No Humen in the room, Humen detected, turn light ON, wait for 60s");
          //digitalWrite(pinBuzzer, HIGH);
          //delay(200);
          //digitalWrite(pinBuzzer, LOW);
          //delay(200);
          //Serial.print("SensorValue = ");
          //Serial.println(sensorValue);
          irsend.sendNEC(0x1FE807F, 32);
          delay(60000);
          Human = 1;
          }
        if (dark_model == 1) {
          Serial.println("Case1_1: No Humen in the room, Humen detected, turn light ON, wait for 60s");
          //digitalWrite(pinBuzzer, HIGH);
          //delay(200);
          //digitalWrite(pinBuzzer, LOW);
          //delay(200);
          //Serial.print("SensorValue = ");
          //Serial.println(sensorValue);
          irsend.sendNEC(0x1FE807F, 32);
          for (int i=0; i<15; ++i){
            irsend.sendNEC(0x1FE48B7, 32);
            delay(40);
          }
          delay(60000);
          Human = 1;
          dark_model = 0;
          }
        }
      }
    
    if (Human == 1) {
      //digitalWrite(LED, HIGH);
      Serial.println("Case2: Humen in the room, Humen detected, DO NOT touch light, wait for 60s");
      //Serial.print("SensorValue = ");
      //Serial.println(sensorValue);
      delay(60000);
    } 
  }

  
  if ( sensorValue == 0 ) {
    if (Human == 0) {
      Serial.println("Case4: No Humen in the room, No Humen detected, Do NOT touch light");
      //Serial.print("SensorValue = ");  
      //Serial.println(sensorValue);
      //Serial.println("PowerOff for 2s!");
      //LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
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
      //Serial.print("SensorValue = ");  
      //Serial.println(sensorValue);
      irsend.sendNEC(0x1FE807F, 32);
      Human = 0;
    }
  }
  delay(2000);
}

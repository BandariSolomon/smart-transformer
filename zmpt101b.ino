//-----------ZMPT101B-----------------
#include "EmonLib.h"             // Include Emon Library
#define VOLTAGE 230

#define VOLT_CAL 538.2

EnergyMonitor emon1;             // Create an instance


int grounding=0,measure_flag=1;;

void zmpt_init(){
  emon1.voltage(ZMPT_PIN, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
}

void measure_voltage(){
  int earth_volt=0,neutral_volt=0;
  int i=0;
  if(measure_flag){
    while(i<=1){
      if(digitalRead(RELAY_PIN) == HIGH){
          emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
          neutral_volt = emon1.Vrms;             //extract Vrms into Variable;
          Serial.print("Neutral:");
          Serial.println(neutral_volt);
          digitalWrite(RELAY_PIN,!digitalRead(RELAY_PIN));
      } else if(digitalRead(RELAY_PIN) == LOW){
          emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
          earth_volt = emon1.Vrms;             //extract Vrms into Variable;
          Serial.print("Earth:");
          Serial.println(earth_volt);
          digitalWrite(RELAY_PIN,!digitalRead(RELAY_PIN));
      }
      delay(1000);
      i++;
    }

    if(earth_volt == neutral_volt){
  //     EEPROM.write(earth_addr,'1');
      grounding = 1;
      Serial.print("Grounding="); Serial.println(grounding);
    } else {
      grounding = 0;
      Serial.print("Grounding="); Serial.println(grounding);
    }
  }

  if(neutral_volt<150){
    digitalWrite(RELAY_PIN,HIGH);
    emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
    neutral_volt = emon1.Vrms;             //extract Vrms into Variable;
    Serial.print("On battery Neutral:");
    Serial.println(neutral_volt);
    if(neutral_volt<150){
      measure_flag = 0;
    } else {  
      measure_flag = 1;
      digitalWrite(RELAY_PIN,!digitalRead(RELAY_PIN));
    }
  } else {
    measure_flag = 1;
  }
//  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
//  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
////  Serial.println(supplyVoltage);
//  if((supplyVoltage > 200) && (supplyVoltage <250))
//    EEPROM.write(earth_addr,'1');
//  else if((supplyVoltage > 0 && (supplyVoltage <200))){
//    ;// low voltage
//  }
//  else{
//   ;//----send a message no proper earthing
//  }
}

#include "pins.h"

#include <EEPROM.h>
#define EEPROM_MAX  SIZE
//-------DS18B20-----------
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>


//extern variables
extern char final_eeprom_dat[EEPROM_BUFF];
extern int earth_flag;
extern unsigned long previousMillis;
extern const long interval_60;
extern int cpin_flag;

extern float batt_volts;
extern float DS18B20_tempC;
extern float fuse_temp;
extern int grounding;
extern char cp_location_data[100];
extern int measure_flag;

char post_final_data[100];
String post_data;
int continuity = 0;

void zmpt_relay_init(){
  pinMode(RELAY_PIN,OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
}

void setup() {
  pinMode(GND_PIN,OUTPUT);
  digitalWrite(GND_PIN,LOW);
  Serial.begin(GSM_BAUD);
  
  battery_init();
  ds18b20_init();
  mlx90614_init();
  zmpt_init();
  zmpt_relay_init();
  earth_init();
  Serial.println("============================");
  measure_voltage();
  measure_battery_voltage();
  measure_fuse_temp();
  measure_oil_temp();
  if(digitalRead(EARTH_PIN) == HIGH){
//         EEPROM.write(continuity_addr,'1');
    continuity = 1;
 } else {
    continuity = 0;
 }
  Serial.print("Continuity:"); Serial.println(continuity);
  Serial.println("============================");
  post_data  = "oil="   + (String)DS18B20_tempC;
  post_data += "&fuse="  +(String)fuse_temp;
  post_data += "&earth=" + (String)grounding;
  post_data += "&cont="  + (String)continuity;
  post_data += "&batt="  + (String)batt_volts;
  Serial.println(post_data);
  post_data="";
//  sprintf(post_data,"oil=%f&fuse=%f&earth=%d&cont=%d&batt=%f",(float)DS18B20_tempC,fuse_temp,grounding,continuity,(float)batt_volts);
//  Serial.println(post_data);
//  memset(post_data,'0',POST_BUFF);
//    eeprom_read();
  gsm_init();
//  delay(2000);
//  gsm_status();
//  delay(2000);
  Serial.println("START");
//  if(cpin_flag){
//  sprintf(post_final_data,"oil=%d&fuse=%d&earth=%d&cont=%d&bat=%d",DS18B20_tempC, fuse_temp, batt_volts, grounding);
//  Serial.println(post_final_data);  
//  http_post(post_final_data);
//    get_location();
//    http_post(cp_location_data);
//    http_post("SmartIMS_Transformer_Start");
//    cpin_flag=0;
//  } else {
//    Serial.println("CPIN Error");
//  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval_60) {
    previousMillis = currentMillis;
    if(measure_flag){
      digitalWrite(BLUE,HIGH);
      digitalWrite(GREEN,LOW);
      digitalWrite(RED, LOW);
      if(digitalRead(EARTH_PIN) == HIGH){
//         EEPROM.write(continuity_addr,'1');
          continuity = 1;
       } else {
          continuity = 0;
       }
      // save the last time you blinked the LED
      measure_voltage();
      measure_battery_voltage();
      measure_fuse_temp();
      measure_oil_temp();
      Serial.print("Continuity:"); Serial.println(continuity);
      post_data  = "oil="   + (String)DS18B20_tempC;
      post_data += "&fuse="  +(String)fuse_temp;
      post_data += "&earth=" + (String)grounding;
      post_data += "&cont="  + (String)continuity;
      post_data += "&batt="  + (String)batt_volts;
      Serial.println(post_data);
      post_data="";
//      sprintf(post_data,"oil=%f&fuse=%f&earth=%d&cont=%d&batt=%f",(float)DS18B20_tempC,fuse_temp,grounding,continuity,(float)batt_volts);
//      Serial.println(post_data);  
//      http_post(post_data);
//      memset(post_data,'0',POST_BUFF);
      Serial.println("============================");

    } else {
      measure_battery_voltage();
      measure_voltage();
      Serial.println("============================");
    }
////    eeprom_read();

//http_post("SmartIMS_Transformer");
  }
  
  if(earth_flag){
    Serial.println("Earthing disconnected");
    continuity = 0;
////    EEPROM.write(continuity_addr,'0');
  }
}

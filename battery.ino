#include <EEPROM.h>
//----------BATTERY---------
const int batteryPin = BATT_PIN;         // battery is connected to analog pin 0
extern int measure_flag;
float batt_volts=0;

#define BATTERY_GREEN   GREEN
#define BATTERY_RED     RED
#define BATTERY_BLUE    BLUE

void battery_init(){
  pinMode(BATTERY_GREEN, OUTPUT);
  pinMode(BATTERY_RED, OUTPUT);
  pinMode(BATTERY_BLUE,OUTPUT);
}

void measure_battery_voltage(){
  const float referenceVolts = 5.0; // the default reference on a 5-volt board
  int val = analogRead(batteryPin); // read the value from the sensor 
  batt_volts = (val / 1023.0) * referenceVolts; // calculate the ratio
  Serial.print("Bat:");
  Serial.println(batt_volts); // print the value in volts
//  EEPROM.write(battery_addr,volts);
  if(measure_flag){
    digitalWrite(BATTERY_BLUE,HIGH);
    digitalWrite(BATTERY_RED, LOW);
    digitalWrite(BATTERY_GREEN, LOW);
  } else {
    if(batt_volts >= 2.5 && batt_volts <= 2.8){
      Serial.println("0%-20%");
      digitalWrite(BATTERY_BLUE,LOW);
      digitalWrite(BATTERY_GREEN, LOW);
      digitalWrite(BATTERY_RED, HIGH);
    } else if(batt_volts > 2.8 && batt_volts <= 3.5) {
      Serial.println("20%-60%");
      digitalWrite(BATTERY_BLUE,LOW);
      digitalWrite(BATTERY_RED, HIGH);
      digitalWrite(BATTERY_GREEN, HIGH);
    } else if (batt_volts > 3.5 && batt_volts <= 4.2){
      Serial.println("60%-100%");
      digitalWrite(BATTERY_GREEN, HIGH);
      digitalWrite(BATTERY_BLUE,LOW);
      digitalWrite(BATTERY_RED, LOW);
    }
  }
}


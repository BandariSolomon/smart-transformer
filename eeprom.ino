////-------EEPROM-----------
//
//#include <EEPROM.h>
//#define EEPROM_MAX  SIZE
//int eeprom_i=0;
//
//char eeprom_data[EEPROM_MAX];
//char final_eeprom_dat[EEPROM_BUFF];
//int eeprom_address = START_ADDR;
//byte eeprom_value;
//
//void eeprom_read(){
////  Serial.print("Length");
////  Serial.println(EEPROM.length());
//
//  for(eeprom_i=0; eeprom_i<EEPROM_MAX; eeprom_i++){
//      eeprom_value = EEPROM.read(eeprom_address);
//  eeprom_data[eeprom_i]=eeprom_value;
//  Serial.print(eeprom_address);
//  Serial.print("\t");
//  Serial.print(eeprom_value, HEX);
//  Serial.println();
//
//    eeprom_address = eeprom_address + 1;
//  }
//  eeprom_data[eeprom_i]='\0';
//  Serial.println((String)eeprom_data);
//
//  sprintf(final_eeprom_dat,"oil=%d&fuse=%d&earth=%d&cont=%d&bat=%d",eeprom_data[0],eeprom_data[2],eeprom_data[4],eeprom_data[6],eeprom_data[8]);
//  Serial.println(final_eeprom_dat);  
//  eeprom_i = 0;
//  eeprom_address = START_ADDR;
//}

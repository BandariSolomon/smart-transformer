

//----------------MLX90614--------------------
//-----------MLX90614-----------
#include <Adafruit_MLX90614.h>
#include "Wire.h"
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}


//Adafruit_MLX90614 mlx_1 = Adafruit_MLX90614(MLX_ADDR_1);
Adafruit_MLX90614 mlx_2 = Adafruit_MLX90614(MLX_ADDR_2);

byte start_address = 8;       // lower addresses are reserved to prevent conflicts with other protocols
byte end_address = 119;       // higher addresses unlock other modes, like 10-bit addressing
byte addr_1_found,addr_2_found;
bool flag_1 = false;
bool flag_2 = false;

float fuse_temp=0;

void mlx90614_init(){
  Serial.println("Adafruit MLX90614 test");  
//  mlx_1.begin();  
  mlx_2.begin();   
  Serial.println("Scanning for MLX90614");
  // start the scan, will call "scanFunc()" on result from each address
  scanI2CBus( start_address, end_address, scanFunc );
  Serial.println("");
//  Serial.print("Addr_1_found at:");
//  Serial.println(addr_1_found,HEX);
  Serial.print("Addr_2_found at:");
  Serial.println(addr_2_found,HEX);
}

//============== I2C scan ===================

void scanI2CBus(byte from_addr, byte to_addr, void(*callback)(byte address, byte result) ) 
{
  byte rc;
  byte data = 0; // not used, just an address to feed to twi_writeTo()
  for( byte addr = from_addr; addr <= to_addr; addr++ ) {
    rc = twi_writeTo(addr, &data, 0, 1, 0);
    callback( addr, rc );
  }
}

void scanFunc( byte addr, byte result ) {
  Serial.print("addr: ");
  Serial.print(addr,HEX);
  Serial.print( (result==0) ? " found!":"       ");
  if(result == 0){
    if(addr == MLX_ADDR_1){
      addr_1_found = addr;
       flag_1 = true;
    } else {
      flag_1 = false;
    }
    if(addr == MLX_ADDR_2){
       addr_2_found = addr;
       flag_2 = true;
    } else {
      flag_2 = false;
    }
  }
  Serial.print( (addr%4) ? "\t":"\n");
}

void measure_fuse_temp(){
//  Serial.print("Ambient of MLX1= "); Serial.print(mlx_1.readAmbientTempC()); 
//  Serial.print("MLX1="); Serial.print(mlx_1.readObjectTempC()); //Serial.print("*C");
//  Serial.print("Ambient of MLX2= "); Serial.print(mlx_2.readAmbientTempC()); 
  fuse_temp = mlx_2.readObjectTempC();
  Serial.print("MLX2="); Serial.print(fuse_temp); Serial.println("*C");
//  Serial.print(" Ambient = "); Serial.print(mlx_2.readAmbientTempF()); 
//  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

//  EEPROM.write(fuse_addr,obj_temp);
  delay(500);
}
//=====================MLX90614 END===========================

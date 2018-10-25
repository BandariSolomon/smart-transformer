#define GSM_BAUD      9600

//----------------MLX90614 Address--------------------
#define MLX_ADDR_1    0x5A
#define MLX_ADDR_2    0x2B

#define DS18B20_PIN     4
#define EARTH_PIN       5
#define GSM_TX          6
#define GSM_RX          7
#define RELAY_PIN       8
#define RED             9
#define GREEN           10
#define BLUE            11
#define GND_PIN         12


#define BATT_PIN        A2
#define ZMPT_PIN        A3

//-----------EEPROM Address------------
#define SIZE          9
#define EEPROM_BUFF   25
#define POST_BUFF     50
#define START_ADDR    0
int oil_addr        = 0;
int fuse_addr       = 2;
int earth_addr      = 4;
int continuity_addr = 6;
int battery_addr    = 8;


//DS18B20, MLX90614, EEPROM, GSM, BATTERY, TIMER, ZMPT101B,
//DS18B20_tempC, obj_temp, batt_volts, grounding

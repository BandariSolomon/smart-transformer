#define ECHO_MODE_OFF   "ATE0"
#define ECHO_MODE_ON    "ATE1"
#define ATTENTION       "AT"

//------Status---------
#define CPIN_STAT       "AT+CPIN?"
#define CFUN_STAT       "AT+CFUN?"
#define BAUD_STAT       "AT+IPR?"
#define CFUN            "AT+CFUN=1"
#define SET_BAUD_9600   "AT+IPR=9600"

//------Responses
#define COMMON_OK_RESP         "OK"
#define COMMON_ERROR_RESP      "ERROR"
#define CPIN_RESP       "+CPIN: READY"
#define CPIN_ERR_RESP   "+CPIN: NOT READY"
#define CFUN_RESP       "+CFUN: 1"
#define GSM_LOC_RESP    "+CIPGSMLOC"
#define POST_RESP_OK    "+HTTPACTION: 1,200,0"  //OK
#define POST_ERROR_RESP "+HTTPACTION: 1,601,0"  //network error

//-------HTTP communication--------
#define HTTPINIT        "AT+HTTPINIT"
#define HTTP_PARA_SET   "AT+HTTPPARA=\"CID\",1"
#define HTTPTERM        "AT+HTTPTERM"
#define HTTP_GET        "AT+HTTPACTION=0"
#define HTTP_POST       "AT+HTTPACTION=1"
#define HTTP_SERVER     "AT+HTTPPARA=\"URL\",\"http://139.59.7.234/a.php?"
#define HTTP_DATA       "AT+HTTPDATA="

//----Bearer profile-----
#define BEAR_PROF1      "AT+SAPBR=3,1,\"Contype\", \"GPRS\""
#define BEAR_PROF1_1    "AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\""          //Vodafone=www      Airtel=airtelgprs.com
#define OPEN_GPRS       "AT+SAPBR=1,1"
#define QUERY_GPRS      "AT+SAPBR=2,1"
#define CLOSE_GPRS      "AT+SAPBR=0,1"

//----Location
#define GET_LOCATION    "AT+CIPGSMLOC=1,1"    //get code,lon,lat,date,time
#define GET_DATE_TIME   "AT+CIPGSMLOC=2,1"    //code,date,time

//-----Signal Strength-------
#define SIG_STRENGTH    "AT+CSQ"


//----------------GSM----------------
#include <SoftwareSerial.h>


SoftwareSerial altSerial(GSM_RX,GSM_TX); // rx,tx
char cp_location_data[100]; // = "+CIPGSMLOC:0,121.354848,31.221402,2011/01/26,02:41:06";
int flag=0,cpin_flag=0,sig_strength;
char loc_dat[100],http_dat[25];


//------------------GSM---------------------------
void gsm_init(){
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(GSM_BAUD);
  delay(2000);
}

void gsm_status(){
  send_cmd(ECHO_MODE_OFF,500);
  send_cmd(ATTENTION,500);  
  send_cmd(CPIN_STAT,1000);
  send_cmd(CFUN_STAT,500);
}

void send_cmd(char cmd[], int t) {
  int temp = 0, i = 0, j = 0;
  char buff[500];
  if (strstr(cmd, HTTP_DATA)) {
    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    memset(buff, '0', strlen(buff));
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    memset(buff, '0', strlen(buff));
  } else if (strstr(cmd, HTTP_POST)) {
    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    memset(buff, '0', strlen(buff));
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,POST_RESP_OK)){
      Serial.println("Posted sucessfully");
    } else if (strstr(buff,POST_ERROR_RESP)){
      Serial.println("Network Error");
    }
    memset(buff, '0', strlen(buff));
  } 
  // Bearer profile responses 
  else if(strstr(cmd,BEAR_PROF1)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,COMMON_OK_RESP)){
      Serial.println("Contype OK");
    } else if (strstr(buff,COMMON_ERROR_RESP)){
      Serial.println("Contype error");
    }
  } else if(strstr(cmd,BEAR_PROF1_1)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,COMMON_OK_RESP)){
      Serial.println("APN OK");
    } else if (strstr(buff,COMMON_ERROR_RESP)){
      Serial.println("APN error");
    }
  } else if(strstr(cmd,OPEN_GPRS)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,COMMON_OK_RESP)){
      Serial.println("GPRS open OK");
    } else if (strstr(buff,COMMON_ERROR_RESP)){
      Serial.println("GPRS open failed");
    }
  } else if(strstr(cmd,CLOSE_GPRS)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,COMMON_OK_RESP)){
      Serial.println("GPRS close OK");
    } else if (strstr(buff,COMMON_ERROR_RESP)){
      Serial.println("GPRS close failed");
    }
  } else if(strstr(cmd,CPIN_STAT)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,CPIN_RESP)){
      Serial.println("CPIN OK");
      cpin_flag=1;
    } else if (strstr(buff,CPIN_ERR_RESP)){
      Serial.println("CPIN not ready");
      cpin_flag=0;
    } else if (strstr(buff,COMMON_ERROR_RESP)){
      Serial.println("CPIN error");
      cpin_flag=0;
    } 
  } else if(strstr(cmd,CFUN_STAT)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,CFUN_RESP)){
      Serial.println("Full functionality");
    } //else if (strstr(buff,COMMON_ERROR_RESP)){
//      Serial.println("GPRS close failed");
//    }
  } else if(strstr(cmd,CFUN_STAT)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);
    if (strstr(buff,CFUN_RESP)){
      Serial.println("Full functionality");
    } //else if (strstr(buff,COMMON_ERROR_RESP)){
//      Serial.println("GPRS close failed");
//    }
  } else if(strstr(cmd,SIG_STRENGTH)){
//    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.println(buff);

    char* token1[10],* token2[10];
    int tkcnt1 = 0,tkcnt2 = 0;
    char dat[3];
    token1[tkcnt1] = strtok(buff," ");
  
    while(token1[tkcnt1] != NULL){
//       Serial.println(token1[tkcnt]);
       token1[++tkcnt1] = strtok(NULL," ");
    }

    Serial.println(token1[0]);
    Serial.println(token1[1]);
    
    strcpy(dat,token1[1]);
    token2[tkcnt2] = strtok(dat,",");
  
    while(token2[tkcnt2] != NULL){
//       Serial.println(token2[tkcnt2]);
       token2[++tkcnt2] = strtok(NULL,",");
    }
    Serial.println(token2[0]);
    Serial.println(token2[1]);
    sig_strength = atoi(token2[0]);
  } 
  else {
// for all other AT Commands
    Serial.print("CMD:");
    Serial.println(cmd);
    altSerial.println(cmd);
    delay(t);
    while (altSerial.available() > 0)
    {
      buff[i++] = altSerial.read();
    }
    buff[i] = '\0';
    Serial.print("Resp:");
    Serial.println(buff);
    if (strstr(buff, GSM_LOC_RESP)) {
      Serial.println("found");
      strcpy(cp_location_data, buff);
    } else if (strstr(buff,COMMON_OK_RESP)){
      Serial.println("OK resp");
    } else if (strstr(buff,COMMON_ERROR_RESP)){
      Serial.println("Error resp");
    } 
    memset(buff, '0', strlen(buff));
  }
}

void http_post(String data) {
  String location_data = "",lon_lat="",http_data="";
  location_data = (String)HTTP_SERVER + data + "\"";
  location_data.toCharArray(loc_dat,location_data.length()+1);
  Serial.println(loc_dat);
  http_data = (String)HTTP_DATA + data.length() + ",10000";
  http_data.toCharArray(http_dat,http_data.length()+1);
  Serial.println(http_dat);

  send_http_data(loc_dat,http_dat);
  location_data = "";
  lon_lat = "";
  http_data = "";
}

void send_http_data(char loc[], char dat[]) {
  Serial.println(loc);
  Serial.println(dat);
  open_gprs();
  send_cmd(HTTPINIT, 500);
  send_cmd(HTTP_PARA_SET, 500);
  send_cmd(loc, 5000);
  send_cmd(dat, 7000);
  send_cmd(HTTP_POST, 5000);
  send_cmd(HTTPTERM, 500);
  close_gprs();
}

void get_location(){
  open_gprs();
  send_cmd(GET_LOCATION,8000);
  close_gprs();
}

void open_gprs() {
  send_cmd(ECHO_MODE_OFF, 500);
  send_cmd(BEAR_PROF1, 500);
  send_cmd(BEAR_PROF1_1, 500);
  send_cmd(OPEN_GPRS, 2000);
  send_cmd(QUERY_GPRS, 2000);
}

void close_gprs() {
  send_cmd(CLOSE_GPRS, 3000);
}


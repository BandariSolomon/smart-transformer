int earth_flag = 0;

void earth_init(){
  pinMode(EARTH_PIN,INPUT);
  attachInterrupt(EARTH_PIN,earth_handler,LOW);
}

void earth_handler(){
  earth_flag = 1;
}

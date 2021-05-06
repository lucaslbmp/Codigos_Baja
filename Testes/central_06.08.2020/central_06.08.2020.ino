#include <TinyGPS.h>
#include <SoftwareSerial.h>

//String auxD="v1,", auxT="r10,c4,", auxG="g1,";
String auxD="v*,", auxT="r*,c*,", auxG="g*,";
int t_last_d = 0, t_last_t = 0;

TinyGPS gps;
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  //Serial.begin(38400);  
  //Serial1.begin(9600);  //GPS
  Serial1.begin(38400); // TFT teste
  Serial2.begin(38400); //Tarsila
  Serial3.begin(38400); //Diana
  while(!Serial1 || !Serial2 || !Serial3);
  mySerial.begin(38400);  //TFT?
}

void loop() {
  Serial3.print('s');
  delay(20);
  if(Serial3.available()){
       auxD = Serial3.readStringUntil('\n');
       t_last_d = millis();
       //while(Serial3.read()>=0);
  }
  Serial2.print('s');
  delay(20);
  if(Serial2.available()){
       auxT = Serial2.readStringUntil('\n');
       t_last_t = millis();
       //while(Serial2.read()>=0);
  }
  /*if(gps.f_speed_kmph()!= TinyGPS::GPS_INVALID_F_SPEED){
    auxG = "g"+String(gps.f_speed_kmph(),3)+",";
    smartdelay(200);
  }
  else{
    auxG = "g*,";
  }*/
  
  // Checagem de erros
  if(millis() - t_last_d >= 1000)
    auxD = "v*,";
  if(millis() - t_last_t >= 1000)
    auxT = "r*,c*,";
  
  // Impressao dos 3 valores
  if (Serial1.available()){
    if (Serial1.read() == 's'){
      //while(Serial1.read()>=0);
      Serial1.println(auxD + auxT + auxG);
    }
  }
  delay(30);
}

/*static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}*/

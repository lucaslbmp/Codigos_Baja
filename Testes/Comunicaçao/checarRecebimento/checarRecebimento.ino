char byteRecebido;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  //Serial.print("Disponiveis: "); Serial.println(Serial2.available());
  while(Serial2.available()>0){
    //byteRecebido = (char)Serial2.read();
    //Serial.println(byteRecebido);
    if(Serial2.read() == 's'){
      Serial2.write('r');
      Serial2.print(1);
      Serial2.print(",c");
      Serial2.print(1);
      Serial2.print(",T");
      Serial2.print(1);
      Serial2.println(",");
    }
  }
  delay(100);
}

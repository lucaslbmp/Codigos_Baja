int count_excel=0;
//String texto = "Baja UFABC 2020";
String dados = "";

void setup() {
  Serial.begin(38400);
  Serial2.begin(38400);
  Serial3.begin(38400);
}

void loop() {
  if(Serial.read() == 't'){
    Serial.println(dados);
  }
   if(Serial3.available()){
    //Serial.print(char(Serial3.read()));
    dados = "";
    dados = Serial3.readStringUntil('\n');
   }
  delay(10);
 //delay(100);
  /*
  if(count_excel == 201 || count_excel == 0){
      count_excel = 0;
      Serial3.println("ROW,SET,2");
      Serial3.println("CLEARDATA");
      Serial3.println("LABEL,Time,Counter,millis,acx1,acy1,acz1,rpm,vel,acx2,acy2,acz2,verif,freio");
      }
     Serial3.print("DATA,TIME,");
    count_excel++;
    Serial3.print(count_excel++);
    Serial3.print(',');
    Serial3.print(millis());
    Serial3.print(',');
    //Serial3.print(tloop);
    //Serial3.print(',');
    Serial3.print("A");
    Serial3.print(',');
    Serial3.print("B");
    Serial3.print(',');
    Serial3.print("C");
    Serial3.print(',');
    Serial3.print(digitalRead(2));
    Serial3.print(',');
    Serial3.print(1);
    //help_show();
    Serial3.println();
    */
}

int count_excel=0;
String texto = "Baja UFABC 2020";
int rpm = 3000, vel = 35, nvcomb = 2, temperatura = 90, pino_freio = 2, help = 0, c_help = 0;

void setup() {
  Serial.begin(38400);
  Serial1.begin(38400);
  //Serial3.begin(38400);
}

void loop() {
  //Serial1.println(texto);
  if(count_excel == 210 || count_excel == 0){
      count_excel = 0;
      Serial1.println("ROW,SET,2");
      Serial1.println("CLEARDATA");
      Serial1.print("LABEL,Time,Counter,millis,rpm,vel,");
      delay(100);
      Serial1.println("comb,temp,verif,freio");
      delay(100);
      }
     Serial1.print("DATA,TIME,");
    count_excel++;
    Serial1.print(count_excel);
    Serial1.print(',');
    Serial1.print(millis());
    Serial1.print(',');
    //Serial1.print(tloop);
    //Serial1.print(',');
    Serial1.print(rpm);
    Serial1.print(',');
    Serial1.print(vel);
    Serial1.print(',');
    Serial1.print(nvcomb);
    Serial1.print(',');
    Serial1.print(temperatura);
    Serial1.print(',');
    Serial1.print(digitalRead(pino_freio));
    Serial1.print(',');
    Serial1.print(1);
    help_show();
    Serial1.println();
    delay(100);
}

void help_show(){
  if(help == 1){
    if(c_help<500){
        Serial1.print(";  SOCORRO");
        c_help++;
    }
    else
    {
      c_help = 0;
      help = 0;
    }
  }
}

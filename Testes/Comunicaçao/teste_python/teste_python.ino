/* Temperatura em Celsius */
int PinAnalogLM35 = 0; //Setando Pino A0
float valAnalog = 0; // Iniciando variavel valAnalog como 0
float temp = 0;  //Iniciando variavel temp como 0

void setup(){
 Serial.begin(9600);
}

void loop(){
 if (Serial.available() > 0){
  if (Serial.read() == 116){ // letra t
   // Lento o pino A0, aqui estamos obtendo o valor
   valAnalog = analogRead(PinAnalogLM35);
   temp = (valAnalog * 500) / 1023;
   Serial.println(temp);
  }
 }
}

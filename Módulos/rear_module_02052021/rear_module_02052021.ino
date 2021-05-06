// Baja UFABC
// Rear bridge

#include <Wire.h>
#include <SmoothThermistor.h>

#define Sensor1     4
#define Sensor2     5
#define NTC1_PIN    A0
#define NTC2_PIN    A1
#define NTC3_PIN    A2

// Constantes nivel de combustivel
volatile unsigned long tempo = millis();
int DelayMS = 30; //Delay em MS para execução dos comandos, sem utilização do comando delay()
int QntMedidas = 1; //Quantidade Máxima de medidas para o Combustivel
int MedidasCmbst = 0; //Contador de Medidas feitas para combustivel
int SomaCmbst = 0; //Soma das medidas do combustivel
int MediaCmbst = 2; //Media calculada ao final da soma das medidas (Soma / Medidas)

// Constantes rpm
volatile unsigned long c1a, c1b,  c1, dt_rpm = 0;
unsigned long rpm_m, rpm1 = 0;
unsigned long timer_aux=0; // instante do ultimo pulso

//Constantes temperatura
float temp1,temp2,temp3;        // Temperaturas dos ntc's 1, 2 e 3
int temp_avg;
unsigned long tempo_ultimaTemp;

// Termistores
SmoothThermistor ntc1(NTC1_PIN,              // the analog pin to read from
                       ADC_SIZE_10_BIT, // the ADC size
                       13977,           // the nominal resistance
                       10000,           // the series resistance
                       4653,            // the beta coefficient of the thermistor
                       25,              // the temperature for nominal resistance
                       10);             // the number of samples to take for each measurement
SmoothThermistor ntc2(NTC2_PIN,ADC_SIZE_10_BIT,10866,10000,4153,25,10);
SmoothThermistor ntc3(NTC3_PIN,ADC_SIZE_10_BIT,10946,10000,4102,25,10);

void setup() {
  
  pinMode(2, INPUT); //interrup RPM
  pinMode(A1,INPUT);
  attachInterrupt(0, rotacao_motor, RISING);      //INT0 - Pino 2
  pinMode(Sensor1, INPUT_PULLUP); //Sensor 1 - Entrada Pullup
  pinMode(Sensor2, INPUT_PULLUP); //Sensor 2 - Entrada Pullup
  Serial.begin(9600); //Megan
  tempo_ultimaTemp = millis();
}

void loop() {
  if (Serial.available() ) {
    if (Serial.read() == 's' ) {
      if(micros() - timer_aux < 500000)
        calcula_rpm();
      else
        rpm_m = 0;
      calcula_nivel();
      calcula_temp();
      Serial.write('H');
      Serial.write('r');
      Serial.print(rpm_m);
      Serial.print(",c");
      Serial.print(MediaCmbst);
      Serial.print(",T");
      Serial.print(temp_avg);
//      Serial.print(",Ta");
//      Serial.print(temp1);
//      Serial.print(",Tb");
//      Serial.print(temp2);
//      Serial.print(",Tc");
//      Serial.print(temp3);
      Serial.println(",");
      delay(10);
    }
  }
}

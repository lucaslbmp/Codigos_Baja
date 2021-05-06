/*
 *
 * The easy circuit:
 *
 *                  Analog pin 0
 *                        |
 *    5V |-----/\/\/\-----+-----/\/\/\-----| GND
 *
 *               ^                ^ 
 *        10K thermistor     10K resistor
 *
 * The advanced circuit:
 *
 *          AREF      Analog pin 0
 *           |              |
 *    3.3V |-+---/\/\/\-----+-----/\/\/\-----| GND
 *
 *                 ^                ^ 
 *          10K thermistor     10K resistor
 */
 
// include the SmoothThermistor library
#include <SmoothThermistor.h>

#define NTC1_PIN               A0
#define NTC2_PIN               A1
#define NTC3_PIN               A2

// if you have a different type of thermistor, you can override the default values
// example:

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
  Serial.begin(9600);
}

void loop() {
  Serial.print("NTC1[°C]: "); Serial.print(ntc1.temperature()); Serial.print(","); 
  Serial.print("NTC2[°C]: "); Serial.print(ntc2.temperature()); Serial.print(","); 
  Serial.print("NTC3[°C]: "); Serial.print(ntc3.temperature()); Serial.print(",");
  Serial.println(); 
  delay(1000);
}

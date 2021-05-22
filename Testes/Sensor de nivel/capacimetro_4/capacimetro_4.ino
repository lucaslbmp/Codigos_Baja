const int OUT_PIN = A6;
const int IN_PIN = A7;
const int IN_REF = A2;
const int OUT_REF = A1;

//Capacitance between IN_PIN and Ground
//Stray capacitance is always present. Extra capacitance can be added to
//allow higher capacitance to be measured.
const float IN_STRAY_CAP_TO_GND = 24.48; //initially this was 30.00
const float IN_EXTRA_CAP_TO_GND = 0.0;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND + IN_EXTRA_CAP_TO_GND;
const int MAX_ADC_VALUE = 1023;


unsigned long startCap=0;
float w = 0.1;
float Cf_ant,C_filter=0;
long somaVal=0;
long somaMeas=0,somaRef=0; //apenas para teste
int N=0; 

void setup()
{
  pinMode(OUT_PIN, OUTPUT);
  //digitalWrite(OUT_PIN, LOW);  //This is the default state for outputs
  pinMode(IN_PIN, OUTPUT);
  //digitalWrite(IN_PIN, LOW);
  pinMode(OUT_REF, OUTPUT);
  pinMode(IN_REF, OUTPUT);
  Serial.begin(38400);
  startCap = millis();
}

void loop()
{ 
  //Capacitor under test between OUT_PIN and IN_PIN
  //Rising high edge on OUT_PIN
  
//  pinMode(IN_PIN, INPUT);
//  digitalWrite(OUT_PIN, HIGH);
//  somaVal += analogRead(IN_PIN);
//  delayMicroseconds(100);
//  //delay(1);
//  digitalWrite(OUT_PIN, LOW);
//  pinMode(IN_PIN, OUTPUT);
//  delayMicroseconds(100);
//  //delay(1);
//  N++;

  pinMode(IN_PIN, INPUT);
  digitalWrite(OUT_PIN, HIGH);
  int meas = analogRead(IN_PIN);
  delayMicroseconds(100);
  digitalWrite(OUT_PIN, LOW);
  pinMode(IN_PIN, OUTPUT);
  
  pinMode(IN_REF, INPUT);
  digitalWrite(OUT_REF, HIGH);
  int ref = analogRead(IN_REF);
  delayMicroseconds(100);
  digitalWrite(OUT_REF, LOW);
  pinMode(IN_REF, OUTPUT);
  
  somaVal += meas - ref;
  N++;
  somaRef += ref;
  somaMeas += meas;

  //Calculate and print result
  if (millis() - startCap >= 1000){
    float val = (float)somaVal/N;
    //Serial.println(val);
    float C = val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
    Serial.print("Meas:");Serial.println(somaMeas/N);
    Serial.print("Ref:");Serial.println(somaRef/N);
    //Serial.println(val);
//    C_filter = w*C + (1-w)*Cf_ant;
//    Cf_ant = C_filter;
    Serial.println(C);
    somaVal = 0;
    somaRef=0,somaMeas=0;
    N = 0;
    startCap = millis();
  }
  
  
}

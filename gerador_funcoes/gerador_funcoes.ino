const int pin_in = 2;
const int pin_out = 8;
const int freq = 50;
unsigned long timer=0, dt=0;

void setup() {
  pinMode(pin_out,OUTPUT);
  pinMode(pin_in,INPUT);
  Serial.begin(38400);
  //attachInterrupt(0, leitura, CHANGE);      //INT0 - Pino 2
}

void loop() {
  //escrita
  long unsigned int T = 1000000/freq;
  digitalWrite(pin_out,HIGH);
  delayMicroseconds(T/20);
  //delay(100);
  digitalWrite(pin_out,LOW);
  delay(19*T/20000);
  //delay(100);

  //leitura
  //int x = digitalRead(2);
  //Serial.println(x);
}

void leitura(){
  dt = micros() - timer;
  Serial.println(dt);
  timer = micros();
}

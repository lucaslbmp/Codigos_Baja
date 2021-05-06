// ===================== RPM =============================

void rotacao_motor()   // interrup
{
  c1b = micros();
  if (c1 >= 1)
  {
    dt_rpm = c1b - c1a;
    c1 = 0;
  }
  else
  {
    c1a = c1b;
    c1++;
  }
  timer_aux = micros();
}


void calcula_rpm()
{
  //int r = micros()-c1b;
  //if (dt_rpm > 500000)
  if (dt_rpm > 10000)
  {
    rpm_m = 60000000 / dt_rpm; //rpm=60/(dt/1*10^-6);
  }
  else
  {
    rpm_m=0;
  }
}
// ============== NIVEL DE COMBUSTIVEL ========================
void calcula_nivel(){
  if(millis() - tempo >= DelayMS) //Se o tempo atual menos a ultima execução for maior ou igual ao Delay, execute as tarefas
  {
    tempo = millis(); //Armazene o tempo de execução atual
    if(MedidasCmbst < QntMedidas) //Se as medidas ainda nao chegarem no limite
    {
      MedidasCmbst++; //Some 1 (uma medida a mais)
      //SomaCmbst += digitalRead(Sensor1) && !digitalRead(Sensor2) ? 2 : !digitalRead(Sensor1) && !digitalRead(Sensor2) ? 1 : !digitalRead(Sensor1) && digitalRead(Sensor2) ? 0 : 0; //Some a medida
      SomaCmbst += digitalRead(Sensor2)?0:!digitalRead(Sensor1)?1:2;  
    }
    else //Se chegaram
    {
      MediaCmbst = SomaCmbst / MedidasCmbst; //Divida a Soma pela quantidade de medidas, e terá a média :D
      MedidasCmbst = SomaCmbst = 0; //Zere as variáveis de contagem e de soma
      //Serial.println(MediaCmbst);
    }
  }
}

// ======================== TEMPERATURA ==========================================
void calcula_temp(){
  if(millis() - tempo_ultimaTemp > 500){
    temp1 = ntc1.temperature();                     // Pega a temperatura do NTC 1 em [°C] 
    temp2 = ntc2.temperature();                     // Pega a temperatura do NTC 2 em [°C] 
    temp3 = ntc3.temperature();                     // Pega a temperatura do NTC 3 em [°C] 
    temp_avg = (int)(10*(temp1 + temp2 + temp3)/3);         // Calcula a temperatura media em [1/10 °C]
    tempo_ultimaTemp = millis();
  }
}

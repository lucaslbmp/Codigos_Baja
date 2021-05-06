//Velocidade

void get_velocidade(){
  //if(micros() - c2b < 1414000 && micros() > 1414000 && dt_vel > 0){
  if(micros()-timer_aux <= dt_vel_max){
    if(dt_vel >= dt_vel_min/* dt_vel>0 && dt_vel <= dt_vel_max*/){
      vel = calcula_velocidade(dt_vel);
    }
   }
   else{
      vel = 0;
   }
}

unsigned long calcula_velocidade(unsigned long deltaTempo){                    // Retorna a velocidade correspondente à velocidade passada
  return (uint64_t)(2*PI_E6*raio_pneu)/(1000*n_imas*deltaTempo)*36/10;         // v[km/h] = (2*pi*R[m])/(n_imas*deltaTempo[s]) * 3,6[km*s/m*h]
}

unsigned long velocidade_para_delta (unsigned int vel){                  //  Retorna o delta de tempo correspondente à velocidade passada
  return (2*PI_E6/1000*raio_pneu)/(n_imas*vel);
}

void rotacao_roda(){   // interrupt
    dt_vel = micros() - timer_aux;                                       // Calcula delta de tempo entre ultimo pulso e instante atual
    timer_aux = micros();                                                // Atualiza instante do ultimo pulso
}

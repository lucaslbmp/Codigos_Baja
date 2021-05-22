#include <movingAvg.h>

//funções que serão usadas
//float calcula_nivel();
//float calcula_consumo(int x);
//float calcula_autonomia(float consumo);

movingAvg cons_avg(500);    // use 500 data points for the moving average

float C; // Capacitancia
//unsigned long deltaT = 0; //diferenca entre o instante atual e o da ultimam medida
unsigned long t_anterior = 0;
unsigned long vol; // volume atual
unsigned long vol_max = 190000; // [10^-6 L]
float h_max = 4.937; // [cm]
float nv_comb = 1.0; // [%]
int consumo = 6300; // [mL/s]
unsigned int autonomia;

unsigned int i=0;


void setup()
{
  Serial.begin(38400);
  cons_avg.begin();
  vol = vol_max;
  t_anterior = millis();
}

void loop()
{
  // ==================== Simulaçao do tanque esvaziando (para teste) --> Apagar =================================
  C = (13.0-0.01*i) + random(0,1)*0.05; // C = capacitancia medida pelo sensor, neste caso da os possiveis valores
  //C = 13.0-0.01*i;
  i++;
  if(i == 1100){ // zera o i depois de chegar na capacitância máxima
    i = 0;
    //Serial.println(millis());
  }
   // ============================================================================================================
  
  vol = 1000*(C - 0.6416)/0.0735; //volume que tenho de combustivel, obtido a partir do gráfico
  //Serial.println(vol);
  nv_comb = calcula_nivel(); // nv_comb -> 0.0 a 1.0
  consumo = calcula_consumo(); // em [10^-6 L/s]
  autonomia = calcula_autonomia(consumo); // em [s ou min]
  
  //Serial.print("capacitancia:"); Serial.print(C); Serial.print(" ");
  Serial.print("nivel:"); Serial.print(nv_comb); Serial.print(" ");
  Serial.print("consumo:"); Serial.print(consumo); Serial.print(" ");
  Serial.print("autonomia:"); Serial.println(autonomia); Serial.print(" ");
  Serial.println();
 
  delay(20);
}

float calcula_nivel(){ // função para calcular o nivel de 0 até 1, retornara um valor do tipo float e não recebe nenhum parametro 
    float nv,h,area;
    area = 3.1415*pow(3.5,2); // [cm^2]
    h = (vol/1000.0)/area; // volume = area.h
    nv = h/h_max; // hmax/h
    return nv; // retorna ao Void Loop o nivel obtido
}

int calcula_consumo(){ // função para calcular o consumo, retornara o consumo médio em [10^-6 L/s]
    static unsigned long vol_anterior = vol,vol_gasto;
    unsigned long deltaT = millis() - t_anterior; // Diferença de tempo entre dois calculos de consumo consecutivos
    t_anterior = millis(); // Instante do ultimo calculo de consumo
    //Serial.println(deltaT);
    vol_gasto = vol_anterior - vol;
    vol_anterior = vol;
    int cons = vol_gasto*1000/deltaT;
    int cons_medio = cons_avg.reading(cons);
    return cons_medio; // retorna o consumo medio de N amostras em [10^-6 L/s]
}

unsigned int calcula_autonomia(float consumo){ // função para calcular a autonomia, retornara um valor do tipo float e sem parametro 
  float aut;
  if(consumo > 0){
    aut = vol/consumo; 
  } 
  return aut; //retorna o tempo em [s]
  //return aut/60; //retorna o tempo em [min] 
}

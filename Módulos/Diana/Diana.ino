// ======================== Velocidade ===================================
// Variaveis
volatile unsigned long dt_vel=0;              // delta de tempo entre as interrupções
unsigned long vel = 0;                        // variavel de velocidade
unsigned long timer_aux = 0;                  // instante do ultimo pulso
unsigned int dt_vel_min;                      // delta de tempo minimo
unsigned int dt_vel_max;                      // delta de tempo maximo

// Constantes
const unsigned long PI_E6 = 3141593;        // pi*10^6
const int raio_pneu = 250;                  // raio do pneu em [mm]
const int n_imas = 4;                       // numero de imãs
const int velocidadeMax = 200;              // maxima velocidade que pode ser medida [km/h]
const int velocidadeMin = 1;                // mínima velocidade que pode ser medida [km/h]

void setup()
{
  //Velocidade
  pinMode(3, INPUT); //interrup velocidade                    // Declara o pino 3 como input
  attachInterrupt(1, rotacao_roda, FALLING);                  // Declara interrupção no pino 3 (INT1) com borda de descida (FALLING)
  dt_vel_min = velocidade_para_delta(velocidadeMax);          // Calcula o delta de tempo maximo que pode ser medida
  dt_vel_max = velocidade_para_delta(velocidadeMin);          // Calcula o delta de tempo maximo que pode ser medida
  Serial.begin(9600);                                         // Inicializa a porta Serial
}
void loop()
{
  if (Serial.available() ){                               // Se há bytes disponíveis no buffer da Serial...
    if (Serial.read() == 's' ){                           // Se o primeiro byte é um 's'...
      get_velocidade();                                   // Pega a velocidade com base no ultimo delta de tempo registrado
      Serial.print('H');                                  // Imprime o caractere de head (H)
      Serial.print('v');                                  // Imprime o caractere de velocidade
      Serial.print(vel);                                  // Imprime o valor da velocidade
      Serial.println(',');
      delay(20);
    }
  } 
}

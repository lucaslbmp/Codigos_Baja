#include <SD.h>
#include <SPI.h>

int CS_PIN = 53;

File file;

String filename = "test.csv";
char buff[100] = {}; 
String msg = "";
unsigned long taxaAtualiza = 0;

int i = 0;

void setup() {
  Serial.begin(9600);
  
  Serial.println("Iniciando Cartao SD");
  pinMode(CS_PIN, OUTPUT);
  if(SD.begin(CS_PIN)){
    //Cria e escreve arquivo CSV
    //NO Excel -> Selecionar -> DADOS -> Texto para Colunas
    file = SD.open(filename, FILE_WRITE);
    Serial.println("Cartao SD iniciado com sucesso!");
    if(file){
      file.println(",");
      file.println("Taxa de Atualizacao, Dados");
      file.close();
      Serial.println("Taxa de Atualizacao, Dados");
    } //end if file
    else{
      Serial.println("Erro ao abrir arquivo");
    }
  }
  else{
    Serial.println("Inicializacao de cartao SD falhou.");
  }
}

void loop() {
  //Cria string de dados para armazenar no cartão SD
  String dataString = String(taxaAtualiza) + ", " + String(i);
  //Abre o arquivo para escrita
  //Apenas um arquivo pode ser aberto de cada vez
  file = SD.open(filename, FILE_WRITE);
  if(file){
    file.println(dataString);
    //file.seek(file.size()-4+i);
    /*if(file.available()){
      msg = file.read();
      Serial.println("Available");
    }*/
    file.close();
    Serial.println(dataString);
  } //end if file
  else{
    Serial.println("Erro ao abrir arquivo para escrita final");
  }
  //Serial.print("read ="); Serial.println(msg);
  i++; //Incrementa
  taxaAtualiza = millis() - taxaAtualiza;
  delay(500);
}

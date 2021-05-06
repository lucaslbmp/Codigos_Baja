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
    file = SD.open(filename, FILE_READ); //mudei
    Serial.println("Cartao SD iniciado com sucesso!");
    if(file){
      Serial.println("Taxa de Atualizacao, Dados");
    } //end if file
    else{
      Serial.println("Erro ao abrir arquivo");
    }
  }
  else{
    Serial.println("Inicializacao de cartao SD falhou.");
  }
  //file.seek(0);
}

void loop() {
  //Cria string de dados para armazenar no cartão SD
  //Abre o arquivo para escrita
  //Apenas um arquivo pode ser aberto de cada vez
  int i=0;
  file = SD.open(filename, FILE_READ);
  if(file){
    while(file.available()){
      //file.seek(i++);
      msg += file.readString();
      //Serial.println("Available");
    }
    file.close();
    Serial.println(msg);
  } //end if file
  else{
    Serial.println("Erro ao abrir arquivo para escrita final");
  }
  delay(500);
}

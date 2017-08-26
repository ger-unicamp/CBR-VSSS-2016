/*
Este programa envia duas variáveis inteiras, via rádio usando um módulo nRF24L01
Programa original disponibilizado por: 
http://www.bajdi.com
No nosso Aduino Nano, as portas (CE,CSN) sao (3,4); no nosso Arduino Uno emissor sao (9,10).
As portas para comunicacao SPI sao definidas por padrao no Uno e no Nano como: MOSI 11, MISO 12, SCK 13.
*/

#define CE 9
#define CSN 10

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

struct Mensagem {
  int vel1_dir;
  int vel1_esq;
  int vel2_dir;
  int vel2_esq;
  int vel3_dir;
  int vel3_esq;
} mensagem;

RF24 radio(CE,CSN);

const uint64_t pipe = 0xA2E8F0F0E1LL;

void setup(void)
{
  delay(1000);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  Serial.println("Iniciou");
  mensagem.vel1_dir = 0;
  mensagem.vel1_esq = 0;
  mensagem.vel2_dir = 0;
  mensagem.vel2_esq = 0;
  mensagem.vel3_dir = 0;
  mensagem.vel3_esq = 0;
}

void loop(void)
{
  String instrucoes[3] = {"", "", ""};
  if(Serial.available()){
    int i = 0;
    while(Serial.available()) {
      char c = Serial.read();
      if(c == ',')
        i++;
      else
        instrucoes[i] += c;
    }
  }
  
  if(instrucoes[0].toInt() == 1){
    mensagem.vel1_dir = instrucoes[1].toInt();
    mensagem.vel1_esq = instrucoes[2].toInt();
  }
  else if(instrucoes[0].toInt() == 2){
    mensagem.vel2_dir = instrucoes[1].toInt();
    mensagem.vel2_esq = instrucoes[2].toInt();
  }
  else if(instrucoes[0].toInt() == 3){
    mensagem.vel3_dir = instrucoes[1].toInt();
    mensagem.vel3_esq = instrucoes[2].toInt();
  }
  
  radio.write(&mensagem, sizeof(mensagem));
  Serial.println("Enviou mensagem");
  delay(20);
}

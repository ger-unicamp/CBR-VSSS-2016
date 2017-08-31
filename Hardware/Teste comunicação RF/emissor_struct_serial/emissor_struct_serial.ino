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

int i;

String instrucoes[6] = {"","","","","",""};

void loop(void)
{
  if(Serial.available()){
    char c = Serial.read();
    if(c == '#'){
      i = 0;
      Serial.println("#");
      for(int j=0; j<6; j++)
        instrucoes[j] = "";
    }
    else{
      if(c == ','){
        i++;
      }
      else{
        instrucoes[i] += c;
      }
    }
  }
  
  mensagem.vel1_dir = instrucoes[0].toInt();
  mensagem.vel1_esq = instrucoes[1].toInt();
  mensagem.vel2_dir = instrucoes[2].toInt();
  mensagem.vel2_esq = instrucoes[3].toInt();
  mensagem.vel3_dir = instrucoes[4].toInt();
  mensagem.vel3_esq = instrucoes[5].toInt();
  
  radio.write(&mensagem, sizeof(mensagem));
  //Serial.println("Enviou mensagem");
  Serial.print(mensagem.vel1_dir);
  Serial.print(" ");
  Serial.print(mensagem.vel1_esq);
  Serial.print(" ");
  Serial.print(mensagem.vel2_dir);
  Serial.print(" ");
  Serial.print(mensagem.vel2_esq);
  Serial.print(" ");
  Serial.print(mensagem.vel3_dir);
  Serial.print(" ");
  Serial.println(mensagem.vel3_esq);
}

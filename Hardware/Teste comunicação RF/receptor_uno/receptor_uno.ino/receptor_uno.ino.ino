/*
Este programa recebe duas variáveis inteiras, via rádio usando um módulo nRF24L01
Programa original disponibilizado por: 
http://www.bajdi.com

No nosso Aduino Nano, as portas (CE,CSN) sao (3,4); no nosso Arduino Uno emissor sao (9,10).
As portas para comunicacao SPI sao definidas por padrao no Uno e no Nano como: MOSI 11, MISO 12, SCK 13.
*/
 
#define CE 9
#define CSN 10 

#define TAM 1

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

double mensagem[TAM];

RF24 radio(CE,CSN);
const uint64_t pipe = 0xA2E8F0F0E1LL;

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop(void)
{
  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read( mensagem, sizeof(mensagem) );
      for(int i=0; i < TAM; i++)
        Serial.println(mensagem[i]);
    }

  }
  else
  {
    Serial.println("Radio nao disponivel");
  }
  // Delay para facilitar a visualização das informações no serial monitor
  delay(20);
}

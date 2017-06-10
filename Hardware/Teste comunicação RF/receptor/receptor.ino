/*
Este programa recebe duas variáveis inteiras, via rádio usando um módulo nRF24L01
Programa original disponibilizado por: 
http://www.bajdi.com

No nosso Aduino Nano, as portas (CE,CSN) sao (3,4); no nosso Arduino Uno emissor sao (9,10).
As portas para comunicacao SPI sao definidas por padrao no Uno e no Nano como: MOSI 11, MISO 12, SCK 13.
*/
 
//CE 9
//CSN 10 

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

byte velocidades[6];

RF24 radio(9,10);
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
      done = radio.read( velocidades, sizeof(velocidades) );
      for(int i=0; i<6; i++)
        Serial.println(velocidades[i]);
    }

  }
  else
  {
    Serial.println("Radio nao disponivel");
  }
  // Delay para facilitar a visualização das informações no serial monitor
  delay(1000);
}

#define CE 3
#define CSN 4

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define TAM 4

int mensagem[TAM];

RF24 radio(CE,CSN);

const uint64_t pipe = 0xA2E8F0F0E1LL;

void setup(void)
{ 
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(void)
{
  for(int i=0; i<TAM; i++)
    mensagem[i] = i;
  
  radio.write( mensagem, sizeof(mensagem) );
  
}

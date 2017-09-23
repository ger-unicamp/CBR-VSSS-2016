/*
 * Programa dos robos do futebol. Recebe informacoes enviadas por RF e aciona os motores. Controle nao implementado.
 * JOGADOR 3
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Pinos da Ponte H
#define PH_IN1 5
#define PH_IN2 6
#define PH_IN3 9
#define PH_IN4 10

//Pinos do RF
#define RF_CSN 4
#define RF_CE 5
#define RF_MO 11
#define RF_MI 12
#define RF_SCK 13

//Pinos do Encoder
#define ENC_R A6
#define ENC_L A7

RF24 radio(3,4);
const uint64_t pipe = 0xA2E8F0F0E1LL;

struct Mensagem{
  int VEL1_DIR;
  int VEL1_ESQ;
  int VEL2_DIR;
  int VEL2_ESQ;
  int VEL3_DIR;
  int VEL3_ESQ;
} mensagem;

//Configura velocidade dos motores (para frente ou para tras) com PWM
void configura_velocidade (int motorA, int motorB){
  if(motorA > 0){
    analogWrite(PH_IN1, motorA);
    analogWrite(PH_IN2, 0);
  }
  else{
    analogWrite(PH_IN1, 0);
    analogWrite(PH_IN2, -motorA);
  }
  
  if(motorB > 0){
    analogWrite(PH_IN3, motorB);
    analogWrite(PH_IN4, 0);
  }
  else{
    analogWrite(PH_IN3, 0);
    analogWrite(PH_IN4, -motorB);
  }
}

//Para os motores. Para parar o motorA, deve-se passar o parametro motorA!=0. Analogamente para motorB.
void para_motores (int motorA, int motorB){
  if(motorA){
    digitalWrite(PH_IN1,1);
    digitalWrite(PH_IN2,1);
  }
  if(motorB){
    digitalWrite(PH_IN3,1);
    digitalWrite(PH_IN4,1);
  }
}

//Configura o valor para cada motor, segundo http://migre.me/wosaU
void configura_motores (int in1, int in2, int in3, int in4){
  digitalWrite(PH_IN1, in1);
  digitalWrite(PH_IN2, in2);
  digitalWrite(PH_IN3, in3);
  digitalWrite(PH_IN4, in4);
}

//Inicializacoes
void setup(){
  pinMode(PH_IN1, OUTPUT);
  pinMode(PH_IN2, OUTPUT);
  pinMode(PH_IN3, OUTPUT);
  pinMode(PH_IN4, OUTPUT);
 
  delay(500);
  Serial.begin(9600);
 
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
 
 configura_velocidade(0,0);
}

void loop(){

int motor1;
int motor2;
  
  if(radio.available())
  {
    bool done = false;
    while (!done)
    {
      done = radio.read( &mensagem, sizeof(mensagem) );
      motor1 = mensagem.VEL3_DIR;
      motor2 = mensagem.VEL3_ESQ;
      
      /*Serial.println(mensagem.VEL1_DIR);
      Serial.println(mensagem.VEL1_ESQ);
      Serial.println(mensagem.VEL2_DIR);
      Serial.println(mensagem.VEL2_ESQ);
      Serial.println(mensagem.VEL3_DIR);
      Serial.println(mensagem.VEL3_ESQ);*/
      
      configura_velocidade(motor1,motor2);
    }

  }
  else
  {
    Serial.println("Rádio não disponível");
  }

}

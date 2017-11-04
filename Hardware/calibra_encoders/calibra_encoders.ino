//Inclusao de biblitoecas
#include "MsTimer2.h"
#include<EEPROM.h>

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
#define ENC_D A6
#define ENC_E A7

//Limites inferior e superior para comparacao dos encoders
/*
#define limsup_dir 853
#define limsup_esq 823
#define liminf_dir 700//676
#define liminf_esq 542
*/

//Variaveis globais de leitura de encoder
int limsup_dir = 0;
int limsup_esq = 0;
int liminf_dir = 1023;
int liminf_esq = 1023;

//Variaveis globais
volatile boolean estado_direita = false;
volatile boolean estado_esquerda = false;
volatile long int contador_direita = 0;
volatile long int contador_esquerda = 0;

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

//Funcao para calibrar os valores-padrao de maximo e minimo a serem utilizados
//Na funcao leitura_encoder()
void calibra_encoder(){
  
  int dir_agora, esq_agora;
  //Ligamos os motores para um giro anti-horario do robo em seu proprio eixo
  configura_velocidade(100, -100);
  for(long i = 0; i < 10000; i++){
    
    dir_agora = analogRead(ENC_D);
    
    if(dir_agora > limsup_dir)
      limsup_dir = dir_agora;
    if(dir_agora < liminf_dir)
      liminf_dir = dir_agora;
      
    esq_agora = analogRead(ENC_E);
    
    if(esq_agora > limsup_esq)
      limsup_esq = esq_agora;
    if(esq_agora < liminf_esq)
      liminf_esq = esq_agora;
  }
  //Paramos os motores
  para_motores(1,1);
  
  delay(1000);

  
  //Ligamos os motores para um giro horario do robo em seu proprio eixo
  configura_velocidade(-100, 100);
  for(long i = 0; i < 10000; i++){
    
    dir_agora = analogRead(ENC_D);
    
    if(dir_agora > limsup_dir)
      limsup_dir = dir_agora;
    if(dir_agora < liminf_dir)
      liminf_dir = dir_agora;
      
    esq_agora = analogRead(ENC_E);
    
    if(esq_agora > limsup_esq)
      limsup_esq = esq_agora;
    if(esq_agora < liminf_esq)
      liminf_esq = esq_agora;

  }
  //Paramos os motores
  para_motores(1,1);
  
  //escreve os limites na memoria EEPROM
  EEPROM.write(0, (byte) (limsup_esq >> 8));
  EEPROM.write(1, (byte) (limsup_esq & 0xff));
    
  EEPROM.write(2, (byte) (liminf_esq >> 8));
  EEPROM.write(3, (byte) (liminf_esq & 0xff));

  EEPROM.write(4, (byte) (limsup_dir >> 8));
  EEPROM.write(5, (byte) (limsup_dir & 0xff));

  EEPROM.write(6, (byte) (liminf_dir >> 8));
  EEPROM.write(7, (byte) (liminf_dir & 0xff));
  
  delay(500);
  
}

//recupera os limites superior e inferior da EEPPROM
void ler_limites(){
  limsup_esq = (((int) EEPROM.read(0)) << 8) + EEPROM.read(1);
  liminf_esq = (((int) EEPROM.read(2)) << 8) +EEPROM.read(3);
  
  limsup_dir = (((int) EEPROM.read(4)) << 8) +EEPROM.read(5);
  liminf_dir = (((int) EEPROM.read(6)) << 8) +EEPROM.read(7);
}


void leitura_encoder(){
  
  if(analogRead(ENC_D) > 0.55*limsup_dir + 0.45*liminf_dir && estado_direita == false)
  {
    estado_direita = true;
    contador_direita++;
  }
  if(analogRead(ENC_D) < 0.45*limsup_dir + 0.55*liminf_dir && estado_direita == true)
  {
    estado_direita = false;
    contador_direita++;
  }
    
  if(analogRead(ENC_E) > 0.55*limsup_esq + 0.45*liminf_esq && estado_esquerda == false)
  {
    estado_esquerda = true;
    contador_esquerda++;
  }
  if(analogRead(ENC_E) < 0.45*limsup_esq + 0.55*liminf_esq && estado_esquerda == true)
  {
    estado_esquerda = false;
    contador_esquerda++;
  }
  
}

//Inicializacoes
void setup(){
 pinMode(PH_IN1, OUTPUT);
 pinMode(PH_IN2, OUTPUT);
 pinMode(PH_IN3, OUTPUT);
 pinMode(PH_IN4, OUTPUT);
 
 MsTimer2::set(1, leitura_encoder); //RSI periodica leitura_encoder com T=1ms
 MsTimer2::start(); //Habilita RSI
 
 delay(10000);
 calibra_encoder();
 //ler_limites();
 Serial.begin(9600);
 Serial.print(limsup_esq);
 Serial.print(" ");
 Serial.print(limsup_dir);
 Serial.print(" ");
 Serial.print(liminf_esq);
 Serial.print(" ");
 Serial.println(liminf_dir);
 delay(1000);
 contador_esquerda = 0;
 contador_direita = 0;
}


void loop(){
  configura_velocidade(0,0);
  delay(1000);
}

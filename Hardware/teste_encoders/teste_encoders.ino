//Inclusao de biblitoecas
#include "MsTimer2.h"

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
#define limsup_dir 853
#define limsup_esq 823
#define liminf_dir 700//676
#define liminf_esq 542

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

//Configura o valor para cada motor, segundo http://migre.me/wosaU
void configura_motores (int in1, int in2, int in3, int in4){
  digitalWrite(PH_IN1, in1);
  digitalWrite(PH_IN2, in2);
  digitalWrite(PH_IN3, in3);
  digitalWrite(PH_IN4, in4);
}

void leitura_encoder(){
  if(analogRead(ENC_D) > 0.6*limsup_dir + 0.4*liminf_dir && estado_direita == false)
  {
    estado_direita = true;
    contador_direita++;
  }
  if(analogRead(ENC_D) < 0.4*limsup_dir + 0.6*liminf_dir && estado_direita == true)
  {
    estado_direita = false;
    contador_direita++;
  }
    
  if(analogRead(ENC_E) > 0.6*limsup_esq + 0.4*liminf_esq && estado_esquerda == false)
  {
    estado_esquerda = true;
    contador_esquerda++;
  }
  if(analogRead(ENC_E) < 0.4*limsup_esq + 0.6*liminf_esq && estado_esquerda == true)
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
 
 delay(5000);
 Serial.begin(9600);
}

void loop(){
  //configura_velocidade(200,200);
  
  Serial.println(contador_esquerda);
  Serial.println(contador_direita);
  Serial.println();
  
  
  long int erro = contador_direita - contador_esquerda;
  double kp = 2.5;
  configura_velocidade(max(min(255, 50 - kp * erro),-255),50);
  delay(50);
  
/*  int dir = 0;
  int esq = 0;
  int dir_agora, esq_agora;
  
  for(long i = 0; i < 100000; i++){
    
    dir_agora = analogRead(ENC_D);
    if(dir_agora > dir)
      dir = dir_agora;
    esq_agora = analogRead(ENC_E);
    if (esq_agora > esq)
      esq = esq_agora;
    
  }
    Serial.println(dir);
    Serial.println(esq);
    Serial.println("");
    delay(200);
  */
}

//Inclusao de biblitoecas
#include "MsTimer2.h"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define TAM 4

//Pinos da Ponte H
#define PH_IN1 5
#define PH_IN2 6
#define PH_IN3 9
#define PH_IN4 10

//Pinos do RF
#define RF_CSN 4
#define RF_CE 3
#define RF_MO 11
#define RF_MI 12
#define RF_SCK 13

//Pinos do Encoder
#define ENC_D A6
#define ENC_E A7

float mensagem[TAM];
RF24 radio(RF_CE,RF_CSN);
const uint64_t pipe = 0xA2E8F0F0E1LL;

//Variaveis globais
volatile boolean estado_direita = false;
volatile boolean estado_esquerda = false;
volatile long int contador_direita = 0;
volatile long int contador_esquerda = 0;
volatile int timer = 0;
float vel_atual_dir;
float vel_atual_esq;

const float alpha = 5.0;   //Parametro do controle proporcional (obtido empiricamente)

/*int limsup_dir = 0;
int limsup_esq = 0;
int liminf_dir = 1023;
int liminf_esq = 1023;*/

int limsup_dir2 =0;
int liminf_dir2 = 1023;
int limsup_esq2 =0;
int liminf_esq2 = 1023;

#define limsup_dir 893
#define liminf_dir 687
#define limsup_esq 837
#define liminf_esq 687

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
  timer++;
  
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
  
  if((timer % 100) == 0){
    vel_atual_dir = 100*(contador_direita) / (float)timer;
    vel_atual_esq = 100*(contador_esquerda) / (float)timer;

    if(timer == 200){
      timer = 0;
      contador_direita = 0;
      contador_esquerda = 0;
    }
      
  }
}

double ki = 1;
long erro_acumulado = 0;

//Rotina de controle
int controle (float vel_atual, float vel_desejada){
  int pwm = 127;
  float erro = vel_atual - vel_desejada; //Calcula erro
  erro_acumulado += erro;
  int ajuste = (int)(alpha*erro + ki * erro_acumulado); //Calcula ajuste

  //Calucla valor valor ajustado (pwm - ajuste), que deve estar entre 0 e 255
  if(pwm - ajuste > 255)
    pwm = 255; //Se for maior que 255, satura em 255
  else if(pwm - ajuste < 0)
    pwm = 0; //Se for menor que 0, satura em 0
  else
    pwm = pwm - ajuste;

  return(pwm);
}

//Inicializacoes
void setup(){
 pinMode(PH_IN1, OUTPUT);
 pinMode(PH_IN2, OUTPUT);
 pinMode(PH_IN3, OUTPUT);
 pinMode(PH_IN4, OUTPUT);
 
 MsTimer2::set(1, leitura_encoder); //RSI periodica leitura_encoder com T=1ms
 MsTimer2::start(); //Habilita RSI
 
 delay(100);

 contador_esquerda = 0;
 contador_direita = 0;

 radio.begin();
 radio.openWritingPipe(pipe);
 
 Serial.begin(9600);

 configura_velocidade(100,100);
}

void loop(){
  float vel_desejada_dir = 10.0;
  float vel_desejada_esq = 10.0;
  
  /*int dir = analogRead(ENC_D);
  int esq = analogRead(ENC_E);

  if(dir > limsup_dir2)
    limsup_dir2 = dir;
  if(dir < liminf_dir2)
    liminf_dir2 = dir;

  if(esq > limsup_esq2)
    limsup_esq2 = esq;
  if(esq < liminf_esq2)
    liminf_esq2 = esq;

  Serial.println("Direita (max, min");
  Serial.println(limsup_dir2);
  Serial.println(liminf_dir2);
  Serial.println("Esquerda( max,min)");
  Serial.println(limsup_esq2);
  Serial.println(liminf_esq2);*/

  int ctrl_dir = controle(vel_atual_dir,vel_desejada_dir);
  int ctrl_esq = controle(vel_atual_esq,vel_desejada_esq);

  Serial.println("velocidade atual");
  Serial.print(vel_atual_dir);
  Serial.print(" ");
  Serial.println(vel_atual_esq);
  Serial.println("pwm");
  Serial.print(ctrl_dir);
  Serial.print(" ");
  Serial.println(ctrl_esq);

  configura_velocidade(ctrl_dir,ctrl_esq);

  for(int i=0; i<TAM; i++){
    mensagem[0] = vel_atual_dir;
    mensagem[1] = vel_atual_esq;
    //mensagem[2] = ctrl_dir;
    //mensagem[3] = ctrl_esq;
  }
  
  radio.write( mensagem, sizeof(mensagem) );
  delay(50);
}

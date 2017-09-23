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

//Variaveis globais
volatile boolean estado_direita = false;
volatile boolean estado_esquerda = false;
volatile long int contador_direita = 0;
volatile long int contador_esquerda = 0;
volatile int timer = 0;
volatile float vel_atual_dir;
volatile float vel_atual_esq;

/*int limsup_dir = 0;
int limsup_esq = 0;
int liminf_dir = 1023;
int liminf_esq = 1023;*/

int limsup_dir2 =0;
int liminf_dir2 = 1023;
int limsup_esq2 =0;
int liminf_esq2 = 1023;

#define limsup_dir 930
#define liminf_dir 655
#define limsup_esq 836
#define liminf_esq 654

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
    vel_atual_dir = (((contador_direita)/24.0) / ((float)timer))*1000.0;   //Frequencia angular em Hz
    vel_atual_esq = (((contador_esquerda)/24.0) / ((float)timer))*1000.0;  //Frequencia angular em Hz

    if(timer == 1000){
      timer = 0;
      //contador_direita = 0;
      //contador_esquerda = 0;
    }
      
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
 
 delay(100);

 contador_esquerda = 0;
 contador_direita = 0;
 
 Serial.begin(9600);

 configura_velocidade(200,200);
}

void loop(){
  
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

  Serial.println("dir,esq,erro");
  Serial.println(contador_direita);
  Serial.println(contador_esquerda);
  

  long int erro = contador_direita - contador_esquerda;
  Serial.println(erro);
  
  double kp = 10.0;
  configura_velocidade(max(min(255, 50 - kp * erro),-255),50);
  delay(50);
  
}

//Inclusao de biblitoecas
#include "MsTimer2.h"
#include <EEPROM.h>

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
volatile float vel_atual_dir;
volatile float vel_atual_esq;

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
  
  delay(500);
  
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
 
 delay(5000);
 calibra_encoder();

 contador_esquerda = 0;
 contador_direita = 0;
 Serial.begin(9600);
 Serial.print(limsup_esq);
 Serial.print(" ");
 Serial.print(limsup_dir);
 Serial.print(" ");
 Serial.print(liminf_esq);
 Serial.print(" ");
 Serial.println(liminf_dir);
 delay(1000);
}

void loop(){
  for(int i = 0; i < 256; i += 2)
  {
    configura_velocidade(i,0);
    delay(500);
    contador_esquerda = 0;
    contador_direita = 0;
    delay(500);
    int vesq = contador_esquerda * 2;
    int vdir = contador_direita * 2;
    EEPROM.write(i, (byte) (vesq >> 8));
    EEPROM.write(i + 1, (byte) (vesq & 0xff));
    Serial.print(i);
    Serial.print(" ");
    Serial.print(vesq);
    Serial.print(" ");
    Serial.println(vdir);
  }
  configura_velocidade(0,0);
  delay(1000);
  for(int i = 0; i < 256; i += 2)
  {
    configura_velocidade(0,i);
    delay(500);
    contador_esquerda = 0;
    contador_direita = 0;
    delay(500);
    int vesq = contador_esquerda * 2;
    int vdir = contador_direita * 2;
    EEPROM.write(256 + i, (byte) (vdir >> 8));
    EEPROM.write(256 + i + 1, (byte) (vdir & 0xff));
    Serial.print(i);
    Serial.print(" ");
    Serial.print(vesq);
    Serial.print(" ");
    Serial.println(vdir);
  }
  configura_velocidade(0,0);
  while(1);
  /*
  Serial.print("Esq: ");
  Serial.print(limsup_esq);
  Serial.print(" ");
  Serial.print(liminf_esq);
  Serial.print(" Dir: ");
  Serial.print(limsup_dir);
  Serial.print(" ");
  Serial.print(liminf_dir);
  Serial.print("\n");
  delay(1000);
  */
  /*long int erro = contador_direita - contador_esquerda;
  double kp = 2.5;
  configura_velocidade(max(min(255, 50 - kp * erro),-255),50);
  delay(50);*/
  
}

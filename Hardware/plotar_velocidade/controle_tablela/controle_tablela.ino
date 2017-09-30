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
 
 delay(1000);
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
 contador_esquerda = 0;
 contador_direita = 0;
}

const byte tab_left[300] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 36, 36, 36, 36, 36, 36, 36, 36, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 42, 42, 42, 42, 42, 42, 42, 42, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 46, 46, 46, 46, 46, 46, 48, 48, 48, 48, 48, 48, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 52, 52, 54, 54, 54, 54, 56, 56, 56, 56, 56, 56, 56, 56, 58, 58, 58, 58, 58, 58, 61, 61, 61, 61, 61, 61, 64, 64, 64, 64, 66, 66, 68, 68, 70, 70, 72, 72, 72, 72, 74, 74, 74, 74, 76, 76, 76, 76, 79, 79, 79, 79, 83, 83, 83, 83, 86, 86, 88, 88, 91, 91, 94, 94, 96, 96, 98, 98, 102, 102, 107, 107, 117, 117, 129, 129, 141, 141, 154, 154, 154, 154, 154, 154, 158, 158, 158, 158, 158, 158, 162, 162, 168, 168, 174, 174, 180, 180, 185, 185, 190, 190, 190, 190, 197, 197, 203, 203, 208, 208, 208, 208, 214, 214, 219, 219, 227, 227, 231, 231, 239, 239, 249, 249, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250};
const byte tab_right[300] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 30, 30, 30, 30, 30, 30, 30, 30, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 38, 38, 38, 38, 38, 38, 40, 40, 40, 40, 40, 40, 40, 40, 42, 42, 42, 42, 42, 42, 44, 44, 44, 44, 46, 46, 46, 46, 48, 48, 48, 48, 50, 50, 50, 50, 50, 50, 50, 50, 54, 54, 52, 52, 56, 56, 58, 58, 58, 58, 60, 60, 62, 62, 62, 62, 62, 62, 68, 68, 64, 64, 64, 64, 71, 71, 72, 72, 76, 76, 78, 78, 80, 80, 84, 84, 84, 84, 84, 84, 91, 91, 96, 96, 90, 90, 101, 101, 98, 98, 106, 106, 110, 110, 116, 116, 122, 122, 131, 131, 141, 141, 144, 144, 149, 149, 155, 155, 159, 159, 159, 159, 164, 164, 172, 172, 179, 179, 184, 184, 189, 189, 189, 189, 189, 189, 196, 196, 198, 198, 201, 201, 210, 210, 226, 226, 224, 224, 234, 234, 240, 240, 251, 251, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247};


void loop(){
  contador_esquerda = 0;
  contador_direita = 0;
  delay(500);
  int vel = 200;
  int pwml = tab_left[vel];
  int pwmr = tab_right[vel];
  configura_velocidade(pwmr, pwml);
  Serial.print(pwml);
  Serial.print(" ");
  Serial.println(pwmr);
  Serial.print(contador_esquerda / 0.5);
  Serial.print(" ");
  Serial.println(contador_direita / 0.5);

  
  /*   contador_esquerda = 0;
   contador_direita = 0;
  delay(500);
  double vel = 200;
  int pwml = 5.0 - 40.0*log(1 - vel / 266.0);
  int pwmr = 2.0 - 53.0*log(1 - vel / 264.0);
  configura_velocidade(pwml, pwmr);
  Serial.print(pwml);
  Serial.print(" ");
  Serial.println(pwmr);
  Serial.print(contador_esquerda / 0.5);
  Serial.print(" ");
  Serial.println(contador_direita / 0.5);
*/
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

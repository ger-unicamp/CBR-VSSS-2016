/*
Programa para enviar string pela serial para o Arduino.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
    //Conferencia de parametros
	if(argc < 5){
        printf("Numero de argumentos invalido.\n");
        /* Parametros: [porta serial][numero do robo][potencia do motor][potencia do motor] */
        return 1;
    }
    //Escreve endereco da porta serial
    char porta[13] = "";
    strcat(porta,"/dev/tty");
    strcat(porta,argv[1]);

    //Dados a serem escritos
    int data[] = {atoi(argv[2]),atoi(argv[3]),atoi(argv[4])};  //Random data we want to send
    
    FILE *file;
    file = fopen(porta,"w");

    int i = 0;
    for(i = 0 ; i < 3 ; i++)
    {
        fprintf(file,"%d",data[i]); //Writing to the file
        fprintf(file,"%c",','); //To separate digits
        usleep(1000);
    }
    fclose(file);
}
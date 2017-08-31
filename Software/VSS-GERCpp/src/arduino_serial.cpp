/*
Programa para enviar string pela serial para o Arduino.
*/

#include "arduino_serial.h"

SerialSender::  SerialSender()
{
    //Escreve endereco da porta serial
    char porta[20] = "";
    
    for (int i =0; i < 100; i++)
    {
        sprintf(porta, "/dev/tty/ACM%d", i);
        int access(const char *path, int amode);

        if (access(porta, W_OK) == 0)
        {
            break;
        }
    }
    
    file = fopen(porta,"w");
    if (file == NULL)
    {
         throw std::runtime_error("Serial port not found");
    }
}

SerialSender::  ~SerialSender()
{
    if (file != NULL)
    {
        fclose(file);
    }
}

void SerialSender::   send(int vel_1r, int vel_1l, int vel_2r, int vel_2l, int vel_3r, int vel_3l)
{
    //Dados a serem escritos
    fprintf(file, "#%d,%d,%d,%d,%d,%d\n", vel_1r, vel_1l, vel_2r, vel_2l, vel_3r, vel_3l);
}

int main()
{
    //send(0,0,0,0,0,0);
    return 0;
}

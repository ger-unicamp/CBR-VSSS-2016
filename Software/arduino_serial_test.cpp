#include <stdio.h>
#include <unistd.h>

int main()
{
	int data[] = {10,5,13};  //Random data we want to send
    FILE *file;
    file = fopen("/dev/ttyACM1","w");  //Opening device file
    int i = 0;
    for(i = 0 ; i < 3 ; i++)
    {
        fprintf(file,"%d",data[i]); //Writing to the file
        fprintf(file,"%c",','); //To separate digits
        usleep(1000);
    }
    fclose(file);
}
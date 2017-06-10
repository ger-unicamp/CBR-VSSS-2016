/*
* Programa que realiza comunicacao serial do computador Linux com o Arduino
* TODO: Resolver bug de que o terminal trava, supomos que a comunicacao nao eh fechada quando o programa se encerra
* Ler este link do StackOverflow para determinar como resolver o problema:
* link: http://stackoverflow.com/questions/9340388/writing-strings-to-serial-port-in-c-linux 
*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/*
class SerialSender {

private:
    struct termios tio;
    struct termios stdio;
    int tty_fd;
    fd_set rdset;

public:
    SerialSender(char*, int);
    void sendString(char*);
    void closeSender();

};

SerialSender::SerialSender(char* port, int baudRate) {
    


    memset(&stdio,0,sizeof(stdio));
    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;
    tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd=open(port, O_RDWR | O_NONBLOCK);

    printf("Gostaria de saber quanto vale B115200: %d\n", B9600);

    cfsetospeed(&tio,B115200);            // 115200 baud
    cfsetispeed(&tio,B115200);            // 115200 baud

    //cfsetospeed(&tio,baudRate);
    //cfsetispeed(&tio,baudRate);

    tcsetattr(tty_fd,TCSANOW,&tio);
}


void SerialSender::sendString(char* string) {
    
    write(tty_fd,string,strlen((char *) string));

}

void SerialSender::closeSender() {
    close(tty_fd);
}

int main() {
    char a[30];
    char ba[] = "Olhaaa";
    scanf("%s", a);
    SerialSender sender(a, 115200);

    sender.sendString(ba);
}
*/

int main(int argc,char** argv){
    struct termios tio;
    struct termios stdio;
    int tty_fd;
    fd_set rdset;

    unsigned char c='D';

    printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
    memset(&stdio,0,sizeof(stdio));
    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;
    tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd=open(argv[1], O_RDWR | O_NONBLOCK);      
    cfsetospeed(&tio,B115200);            // 115200 baud
    cfsetispeed(&tio,B115200);            // 115200 baud

    tcsetattr(tty_fd,TCSANOW,&tio);

    unsigned char str[] = "Olhaaa\r\n";
    //the above str[] doesn't work although it's exactly the same as the following
  
    write(tty_fd,&c,1); 
    if (read(tty_fd,&c,1)>0)
        write(STDOUT_FILENO,&c,1);

    write(tty_fd,str,strlen((char *) str));
    

    while (c!='q')
    {
            if (read(tty_fd,&c,1)>0)        write(STDOUT_FILENO,&c,1); // if new data is available on the serial port, print it out
            if (read(STDIN_FILENO,&c,1)>0) 
                if(c!='q')
                    write(tty_fd,&c,1);        // if new data is available on the console, send it to the serial port
    }

    close(tty_fd);

    while(1) {
        printf("Estou vivo\r");
        usleep(1000000);
    }
}
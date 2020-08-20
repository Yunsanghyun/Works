#ifdef RaspberryPi
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <time.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char* message);
char device[] = "/dev/rfcomm0";
char data;
int fd;
unsigned long baud = 9600;
//unsigned long time = 0;

int main(void);
void loop(void);
void setup(void);

void setup()
{
    printf("%s \n","Raspberry Startup!");
    fflush(stdout);

    if((fd = serialOpen(device,baud)) < 0)
    {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        exit(1);
    }

    if(wiringPiSetup() == -1)
    {
        fprintf(stdout,"Unable to start wiringPi: %s\n",strerror(errno));
        exit(1);
    }
}


int main(void)
{
    int cli_sock;
    struct sockaddr_in serv_addr;
    int data_len;
    char message[30];
    char read_buff[3000];
    char write_buff[3000];
    time_t start = 0;
    time_t end = 0;
    int check = 0;

    cli_sock = socket(PF_INET, SOCK_STREAM,0);
    if(cli_sock == -1)
    {
        error_handling("socket() error!\n");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.1");
    serv_addr.sin_port = htons(11000);
    if(connect(cli_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {   
        printf("10\n");
        error_handling("connect() error \n");      
    }

    setup();
    printf("Wireless Test is operating \n");

    memset(&write_buff,0,sizeof(write_buff));
    memset(&read_buff,0,sizeof(read_buff));
    
    while(1)      
    {
        delay(100);
   //     printf("11\n");
        
        memset(&read_buff,0,sizeof(read_buff));

        data_len = recv(cli_sock,read_buff,sizeof(read_buff)-1,MSG_DONTWAIT);
    //    if(data_len == -1)
      //     error_handling("read() error\n");
        
     //   printf("11.5\n");
        printf("recv from robot  = %s \n",read_buff);
        serialPuts(fd, read_buff);
        memset(&read_buff,0,sizeof(read_buff));

       // printf("12\n");

        printf("check from arduino = %d \n",serialDataAvail(fd));

        if(serialDataAvail(fd))
        {
         //   printf("13\n");
            char newChar = serialGetchar(fd);
            printf("recv from arduino = %d \n",newChar);
            fflush(stdout);
            sprintf(write_buff,"%d",newChar);
        }

  //      printf("14\n");
   
        printf("send result = %d \n",send(cli_sock,write_buff,strlen(write_buff),0));
        //    error_handling("send() error\n");
         memset(&write_buff,0,sizeof(write_buff));
    } 
    close(cli_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}

#endif





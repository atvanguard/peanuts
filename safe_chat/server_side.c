#include "elgamal_encrypt.c"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int ser_pri_key;
int ser_pub_key;
int pub_key;
int cli_pub_key;

#define port 5000

void disp(int *message, int m_len)
{
    int i;
    for (i=0;i<m_len;i++) {
        printf("%c",message[i]);
    }
    printf("\n");
}

void disp_int(int *message, int m_len)
{
    int i;
    for (i=0;i<m_len;i++) {
        printf("%d ",message[i]);
    }
    printf("\n");
}

void init_keys()
{
    srand(time(NULL));
    pub_key = rand()%def_pri; //g
    ser_pri_key = rand()%def_pri; //x
    ser_pub_key = rep_squaring(pub_key, ser_pri_key); //A = g^x
}

int main(void)
{
    int listenfd = 0, connfd = 0, i = 0, m_len, ack;
    struct sockaddr_in serv_addr;

    int sendBuff[mx_l], recvBuff[mx_l], message[mx_l];
    char str[mx_l], dummy;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    system("clear");
    printf("Server Initialized\n");
    printf("1. Put server on auto reply\n2. Put server on custom reply mode\n");
    scanf("%d",&ack);
    dummy=getchar();

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
    memset(recvBuff, '0', sizeof(recvBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

    if(listen(listenfd, 10) == -1) {
        printf("Failed to listen\n");
        return -1;
    }

    init_keys(); // Initialize crypto keys

    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
        puts("Connection with Client established\n");

        write(connfd, &pub_key, sizeof(pub_key));
        write(connfd, &ser_pub_key, sizeof(ser_pub_key));
        read(connfd, &cli_pub_key, sizeof(cli_pub_key));

        printf("pubic key = %d\n", pub_key);
        printf("Server public key = %d\n", ser_pub_key);
        printf("Client public key = %d\n", cli_pub_key);

        while(read(connfd, recvBuff, sizeof(recvBuff)-1)) {
            m_len=0;
            for (i=0;i<recvBuff[i]!=0;i++) {
                m_len++;
            }

            printf("\nMessage from client- (Encrypted message): \n");
            elgamal_decrypt(recvBuff, message, m_len, cli_pub_key, ser_pri_key);
            printf("Decrypted message from client: ");

            disp(message, m_len);

            if (ack==1) {
                strcpy(str, "Message recieved successfully");
            }

            else if (ack==2) {
                printf("Reply to client: ");
                gets(str);
            }

            write(connfd, str, sizeof(str)-1);
        }
    }
return 0;
}

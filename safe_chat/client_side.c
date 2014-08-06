#include "elgamal_encrypt.c"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int ser_pub_key;
int pub_key;
int cli_pri_key;
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
    cli_pri_key = rand()%def_pri; /* y */
    cli_pub_key = rep_squaring(pub_key, cli_pri_key); //c1 = g^y
}

int main(void)
{
    int sockfd = 0, i, m_len;
    struct sockaddr_in serv_addr;

    int sendBuff[mx_l], recvBuff[mx_l], message[mx_l];
    char str[mx_l];

    memset(sendBuff, '0', sizeof(sendBuff));
    memset(recvBuff, '0', sizeof(recvBuff));

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0) {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    else {
        system("clear");
        printf("Connection with server established\n");
        printf("Exchanging the public keys: \n\n");
    }

    //If program reaches here, connection is established
    read(sockfd, &pub_key, sizeof(pub_key));
    read(sockfd, &ser_pub_key, sizeof(ser_pub_key));

    init_keys();
    write(sockfd, &cli_pub_key, sizeof(cli_pub_key));

    printf("pubic key = %d\n", pub_key);
    printf("Server public key = %d\n", ser_pub_key);
    printf("Client public key = %d\n", cli_pub_key);

    while(1) {
        printf("\nEnter the message to be sent\n");
        gets(str);
        if (!strcmp(str,"disconnect")) {close(sockfd);return 0;}

        printf("\nEncrypting the message......\n");
        m_len = strlen(str);

        for (i=0;i<m_len;i++) {
              sendBuff[i]=(int)str[i];
        }

        sendBuff[m_len]=0;
        elgamal_encrypt(sendBuff, message, m_len, ser_pub_key, cli_pri_key);
        message[m_len]=0;

        write(sockfd, message, sizeof(message)-1);
        read(sockfd, str, sizeof(recvBuff)-1);
        printf("Message from server: ");
        printf("\x1B[32m%s\n\x1B[0m",str);
    }

    close(sockfd);
    return 0;
}
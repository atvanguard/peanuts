#include <stdio.h>
#include <string.h>
#include <time.h>
#define mx_l 1024
#define def_pri 1000000007

//Return a^n mod pri_num
unsigned long long rep_squaring(unsigned long long a, unsigned long long n)
{
    if (n==0) return 1;
    unsigned long long p=1;
    while(n) {
        if (n%2) p=p*a%def_pri;
        if (n/=2) a=a*a%def_pri;
    }
    return p;
}

int elgamal_encrypt (int *message,
                     int *enc_message,
                     int mlen,
                     int pub_key_of_reciever,
                     int my_private_key)
    {
        int K = rep_squaring(pub_key_of_reciever, my_private_key); // (A,y)
        int i;
        for (i=0;i<mlen;i++) {
            enc_message[i] = ((unsigned long long)message[i] * K)%def_pri;

            if (enc_message[i]<0) {
                enc_message[i] += (2 * def_pri);
                enc_message[i] = enc_message[i] % def_pri;
            }
        }
        return 0;
    }

int elgamal_decrypt (int *enc_message,
                     int *message,
                     int mlen,
                     int pub_key_of_sender,
                     int my_private_key)
    {
        //int mlen=strlen(message);
        int K_inv = rep_squaring(pub_key_of_sender, my_private_key); // (A,y)
        K_inv = rep_squaring(K_inv, def_pri-2); // (A,y)
        int i;
        for (i=0;i<mlen;i++)
            {
                message[i] = ((unsigned long long)enc_message[i] * K_inv)%def_pri;
                if (message[i]<0) {message[i]+=(2*def_pri);message[i]=message[i]%def_pri;}
            }
        return 0;
    }
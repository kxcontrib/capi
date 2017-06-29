/* File name: singleRow.c */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "k.h"

int main()
{
    I handle;
    I portnumber = 5010;
    S hostname = "localhost";
    S usernamePassword = "kdb:pass";
    K result,singleRow;

    handle = khpu(hostname,portnumber,usernamePassword);

    singleRow = knk(3,ks((S)"ABC"),kf(10.0), kj(20));
    // Perform single row insert, tickerplant will add timestamp column itself
    result = k(handle,".u.upd", ks((S)"trade"),singleRow,(K)0);

    // Capture network error
    if(!result)
        {
            perror("Network Error\n");
        }

    // Capture error associated with failed insert
    if(-128==result->t)
        {
            printf("Error %s\n",result->s);
        }

    r0(result);
    kclose(handle);
    return 0;
}

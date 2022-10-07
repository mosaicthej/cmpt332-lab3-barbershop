/*
    NAME: Matthew Munro
    NSID: mam552
    STUDENT NUMBER: 11291769
    NAME: Yi Luan
    NSID: yil160
    STUDENT NUMBER: 11253856
    NAME: Mark Jia
    NSID: mij623
    STUDENT NUMBER: 11271998
    CMPT 332 2022
    Lab3
*/

/*
    testing program for Lab3.synchproblem.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <standards.h>
#include <os.h>

void shop(int maxCustomers, int chairs);

extern bool closeShop;

extern int maxCustomers;
extern int chairs;

/*
    main function:
        - reads from command line arguments
            - maxCustomers
            - chairs
            - if no arguments are given, default values are used
        - creates the shop
        - wait for the shop to close by user type 'q'
        - if no input after 20 seconds, close the shop
        - close the shop by setting closeShop to true
*/

int mainp(int argc, char *argv[]){
    closeShop = false;
    
    if(argc != 3){
        printf("No arguments given, using default values for maxCustomers and chairs");
        maxCustomers = 25;
        chairs = 5;
    }else{
        maxCustomers = atoi(argv[1]);
        chairs = atoi(argv[2]);
    }
    shop(maxCustomers, chairs);

    return 0;
}



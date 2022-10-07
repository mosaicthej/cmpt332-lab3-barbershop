/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# NAME: Mark Jia
# NSID: mij623
# STUDENT NUMBER: 11271998
# CMPT 332 2022
# Lab3
*/

/*
    simulation of the barber shop problem
    designs are layed out in the Lab3.synchproblem.txt file
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include <standards.h>
#include <os.h>
#include <kernelConfig.h>

/*
    contains the following functions:
    Semaphore   newSem(int initialValue);
    void        P(Semaphore sem);
    void        V(Semaphore sem);
    void        freeSem(Semaphore sem);
*/

/*
    Declare global variables
*/
/*semaphores*/
int mutex;
int barberSem;
int customerSem;
int barberDoneSem;
int customerDoneSem;
bool closeShop;


void walkIn();
void balk();
void cutHair();
void getHairCut();
void customer();
void barber();

void shop();

void shop(int maxCustomers, int chairs){
    mutex = newSem(1);
    barberSem = newSem(0);
    customerSem = newSem(0);
    barberDoneSem = newSem(0);
    customerDoneSem = newSem(0);

    printf("Shop is open for business, with %d chairs, and %d customers will come in today.\n", chairs, maxCustomers);
    Create(walkIn, 16000, "createCustomer", NULL, NORM, USR);
}

void walkIn(){
    int i;
    PID barberID = Create(barber, 16000, "barber", NULL, HIGH, USR);
    for(i = 0; i < maxCustomers; i++){
        Create(customer, 16000, "customer", NULL, NORM, USR);
        sleep(10);
    }
    /* wait for shop to close by check closeShop boolean in a loop*/
    while(!closeShop){
        sleep(1);
    }

    /* kill barber */
    Kill(barberID);
}

void balk(){
    printf("Customer %d balks... \n", GetPid());
    printf("%d chairs are available, and %d customers are waiting.\n", chairs, customersWaiting);
}

void cutHair(){
    printf("Barber %d is cutting hair... \n", GetPid());
    sleep(20);
    printf("Barber %d is done cutting hair... \n", GetPid());
    printf("%d customers are waiting.\n", customersWaiting);
}

void getHairCut(){
    printf("Customer %d is getting a haircut... \n", GetPid());
    sleep(30);
    printf("Customer %d is done getting a haircut... \n", GetPid());
    printf("%d chairs are available, and %d customers are waiting.\n", chairs, customersWaiting);
}

void customer(){
    P(mutex);
    if(customersWaiting < chairs){
        /*
            customer sits in chair
        */
        customersWaiting++;
        V(mutex);
        printf("Customer %d walks in... \n", GetPid());
        printf("%d chairs are available, and %d customers are waiting.\n", chairs, customersWaiting);
        V(customerSem);

        P(barberSem);
        /*
            customer gets haircut
        */
        getHairCut();
        V(customerDoneSem);
        P(barberDoneSem);

        /*
            customer leaves
        */
        P(mutex);
        customersWaiting--;
        V(mutex);
        printf("Customer %d leaves... \n", GetPid());
        printf("%d chairs are available, and %d customers are waiting.\n", chairs, customersWaiting);

    } else {
        V(mutex);
        balk();
    }
}

void barber(){
    while(true){
        P(customerSem);
        /*
            barber cuts hair
        */
        V(barberSem);
        cutHair();
        P(customerDoneSem);
        V(barberDoneSem);
    }
}


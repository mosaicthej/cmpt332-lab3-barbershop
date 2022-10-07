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
int maxCustomers;
int chairs;
int customersWaiting;

/*semaphores*/
int mutex;
int barberSem;
int customerSem;
int barberDoneSem;
int customerDoneSem;
bool closeShop;


void main_thread();
void balk();
void cutHair();
void getHairCut();
void customer();
void barber();

void shop();

void shop(){
    mutex = NewSem(1);
    barberSem = NewSem(0);
    customerSem = NewSem(0);
    barberDoneSem = NewSem(0);
    customerDoneSem =NewSem(0);

    printf("Shop is open for business, with %d chairs, and %d customers will come in today.\n", chairs, maxCustomers);
    Create(main_thread, 16000, "createCustomer", NULL, NORM, USR);
}

void main_thread(){
    int i;
    PID barberID = Create(barber, 16000, "barber", NULL, HIGH, USR);
    customersWaiting = 0;
    for(i = 0; i < maxCustomers; i++){
        Create(customer, 16000, "customer", NULL, NORM, USR);
        Sleep(10);
    }
    /* wait for shop to close by check closeShop boolean in a loop*/
    while(!closeShop){
        Sleep(1);
    }

    /* kill barber */
    Kill(barberID);
}

void balk(){
    printf("one Customer balks... \n");
    printf("%d chairs are available, and %d customers are waiting.\n", chairs, customersWaiting);
}

void cutHair(){
    printf("Barber is cutting hair... \n");
    Sleep(20);
    printf("Barber is done cutting hair... \n");
    printf("%d customers are waiting.\n", customersWaiting);
}

void getHairCut(){
    printf("Customer is getting a haircut... \n");
    Sleep(30);
    printf("Customer is done getting a haircut... \n");
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
        printf("Customer walks in... \n");
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
        printf("Customer leaves... \n");
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


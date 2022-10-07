# NAME: Matthew Munro
# NSID: mam552
# Student Number: 11291769
# NAME: Yi Luan
# NSID: yil160
# Student Number: 11253856
# NAME: Mark Jia
# NSID: mij623
# Student Number: 11271998
# Course: CMPT 332 2022
# Lab3

CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
PTHREADS_INCLUDE=-I/student/cmpt332/pthreads/
PTHREADS_LIB = -L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads


objects = Lab3.testsynchproblem.o Lab3.synchproblem.o
all: Lab3
Lab3: Lab3.testsynchproblem.o Lab3.synchproblem.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o Lab3 $(objects) $(PTHREADS_LIB)

Lab3.testsynchproblem.o: Lab3.testsynchproblem.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c Lab3.testsynchproblem.c $(PTHREADS_INCLUDE) -I./

Lab3.synchproblem.o: Lab3.synchproblem.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c Lab3.synchproblem.c $(PTHREADS_INCLUDE) -I./

.PHONY: clean
clean:
	rm -f Lab3 $(objects)

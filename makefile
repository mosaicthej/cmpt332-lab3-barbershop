CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
PTHREADS_INCLUDE=-I/student/cmpt332/pthreads/
PTHREADS_LIB = -L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads


objects = barbershop.test.o barbershop.o
all: barbershop
barbershop: barbershop.test.o barbershop.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o barbershop $(objects) $(PTHREADS_LIB)

barbershop.test.o: barbershop.test.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c barbershop.test.c $(PTHREADS_INCLUDE) -I./

barbershop.o: barbershop.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c barbershop.c $(PTHREADS_INCLUDE) -I./

.PHONY: clean
clean:
	rm -f barbershop $(objects)

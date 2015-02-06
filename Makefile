# Declaration of variables
CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

all: combinationLock clean

combinationLock : main.o combinationLock.o
		${CC} ${CFLAGS} combinationLock.o main.o ${LDFLAGS} -o combinationLock

combinationLock.o : combinationLock.cc combinationLock.h
		${CC} ${CFLAGS} -c combinationLock.cc 

main.o : main.cc combinationLock.h
		${CC} ${CFLAGS} -c main.cc			

.PHONY: clean 

clean:
		rm *.o

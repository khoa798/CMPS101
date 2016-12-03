# Makefile for pa02
#
# ===================================================================

CC     = gcc
CFLAGS = -g -Wall -O0 -std=c99 -D_SVID_SOURCE

graph02:	graph02.o  intList.o intVec.o
	${CC}  -o graph02  graph02.o intList.o intVec.o

intList.o:	intList.c  intList.h
	${CC}  -c  ${CFLAGS}  intList.c

	
intVec.o: intVec.c intVec.h
	${CC} -c   ${CFLAGS}  intVec.c
	
	
graph02.o:	graph02.c intList.h intVec.h
	${CC}  -c  ${CFLAGS}  graph02.c

	
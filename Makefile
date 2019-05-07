#Makefile
CC=gcc
INCLUDE=
CFLAGS=-g -Wall -Werror -D_REENTRANT -D_GNU_SOURCE ${LIB} ${INCLUDE}
target+=$(patsubst %.c, %.o, ${src})
springcleaning=$(patsubst %.c, %, $(wildcard ./*.c))
springcleaning+=$(patsubst %.c, %.o, $(wildcard ./*.c))
springcleaning+=$(patsubst %.c, %.o, ${src})
springcleaning+=$(OutPut)

.PHONY: all clean for_main

all: for_main

for_main:
	gcc -g main.c aes.c encode_decode.c acm_encryption.c -o main
	gcc -std=c99 -g test.c aes.c encode_decode.c acm_encryption.c -o test
	
clean:
	-@rm  *.o main

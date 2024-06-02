#!/bin/bash

gcc -c 2.1.c 
gcc -o 2.1 2.1.o -lpthread

gcc -c 2.2.c 
gcc -o 2.2 2.2.o -lpthread

gcc -c 2.3.c 
gcc -o 2.3 2.3.o -lpthread
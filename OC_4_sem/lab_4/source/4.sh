#!/bin/bash

gcc -c 4.1.c
gcc -o 4.1 4.1.o -lpthread

gcc -c 4.2.c
gcc -o 4.2 4.2.o -lpthread
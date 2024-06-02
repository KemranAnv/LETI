#!/bin/bash

gcc -c 6.1.c
gcc -c 6.2.c

gcc -o 6.1 6.1.o -lpthread
gcc -o 6.2 6.2.o -lpthread

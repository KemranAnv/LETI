#!/bin/bash

gcc -c 5.1.c
gcc -c 5.2.c

gcc -o 5.1 5.1.o -lpthread
gcc -o 5.2 5.2.o -lpthread
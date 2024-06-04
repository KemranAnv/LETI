#!/bin/bash

gcc -c 7.1.c
gcc -c 7.2.c

gcc -o 7.1 7.1.o -lpthread
gcc -o 7.2 7.2.o -lpthread

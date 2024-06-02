#!/bin/bash

gcc -c 8.1.c
gcc -c 8.2.c

gcc -o 8.1 8.1.o -lpthread
gcc -o 8.2 8.2.o -lpthread

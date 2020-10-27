SHELL = /bin/bash

CC := gcc
FILE := main

.PHONY: all run

run: build
	@ ./main.out

build:
	$(CC) src/main.c -O3 -Wall -pedantic -std=c18 -o main.out
	@ echo

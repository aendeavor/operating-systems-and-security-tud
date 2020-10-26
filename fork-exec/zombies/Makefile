SHELL = /bin/bash

CC := gcc
FILE := zombie

.PHONY: all run

run: build
	@ ./$(FILE).out

build:
	$(CC) src/$(FILE).c -O3 -Wall -pedantic -std=c18 -o $(FILE).out
	@ echo

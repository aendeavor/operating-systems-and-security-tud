SHELL = /bin/bash

CC := gcc
FILE := main

.PHONY: all run

run: build
	@ ./$(FILE).out

build:
	$(CC) src/$(FILE).c -Wall -pedantic -std=c18 -o $(FILE).out
	@ echo

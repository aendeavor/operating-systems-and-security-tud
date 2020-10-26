SHELL = /bin/bash

FILE := zombie

.PHONY: all run

run: build
	@ ./$(FILE).out

build:
	gcc src/$(FILE).c -O3 -Wall -pedantic -std=c18 -o $(FILE).out
	@ echo

SHELL = /bin/bash

FILE := main

.PHONY: all run

run: build
	@ ./$(FILE).out

build:
	gcc src/$(FILE).c -Wall -pedantic -std=c18 -o $(FILE).out
	@ echo

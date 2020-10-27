SHELL = /bin/bash

CC := gcc
FILE := find

.PHONY: all run

build:
	$(CC) src/$(FILE).c -Wall -pedantic -o $(FILE)

run:
	./find

clean:
	rm find


SHELL = /bin/bash

.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:

MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

FILE := zombie

.PHONY: all run

run: build
	@ ./$(FILE).out

build:
	gcc src/$(FILE).c -O3 -Wall -pedantic -std=c18 -o $(FILE).out
	@ echo

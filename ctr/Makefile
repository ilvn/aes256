## AES-256-CTR
##
## Usage:    make [target]
## Targets:
## obj       compile the object file
## clean     delete all compiled files
## test      build the test executable
## fast      use with test for a pre-computed tables variant
## help      show this help message

CC := $(if $(shell which clang),clang,gcc)
CFLAGS := -O3 -Wall -Wextra -pedantic
override USE_TABLES := $(if $(findstring fast,$(MAKECMDGOALS)),-DBACK_TO_TABLES,)
AESDIR := ..

.PHONY: help obj test clean fast

help:
	@grep -h '^\##' $(MAKEFILE_LIST) | cut -c4-

aes256ctr.o: aes256ctr.c aes256ctr.h
	$(CC) $(CFLAGS) -I$(AESDIR) -c -o $@ $<

obj: aes256ctr.o

test: aes256ctr.c aes256ctr.h $(AESDIR)/aes256.c
	$(CC) $(CFLAGS) -I$(AESDIR) $(USE_TABLES) -DAES256CTR_SELF_TEST_ -o $@ $(filter %.c,$^)

clean:
	rm -f test *.o

fast:
	@:

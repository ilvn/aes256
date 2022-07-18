## AES-256-CTR
##
## Usage:    make [target]
## Targets:
## obj       compile the object file
## test      build the test executable
## fast      use with test for building a faster executable
## help      show this help message

CC := $(if $(shell which clang),clang,gcc)
CFLAGS := -O3 -Wall -Wextra -pedantic
override USE_TABLES := $(if $(findstring fast,$(MAKECMDGOALS)),-DBACK_TO_TABLES,)
AESDIR := ..

.PHONY: help obj clean fast

help:
	@grep -h '^\##' $(MAKEFILE_LIST) | cut -c4-

aes256ctr.o: aes256ctr.c aes256ctr.h
	$(CC) $(CFLAGS) -I$(AESDIR) -c -o $@ $<

obj: aes256ctr.o

test: aes256ctr.c aes256ctr.h $(AESDIR)/aes256.c
	$(CC) $(CFLAGS) -I$(AESDIR) $(USE_TABLES) -DAES256CTR_SELF_TEST__ -o $@ $(?:%.h=)

clean:
	rm -f test *.o

fast:
	@:

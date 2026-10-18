## A compact byte-oriented AES-256 implementation
##
## Usage:    make [target]
##
## Targets:
##
## aes256    compile AES256 to an object file
## clean     delete all compiled files
## demo      build the demo executable
## fast      use with aes256/demo/verify for a pre-calculated tables variant
## help      show this help message
## verify    run CBMC checks to verify code properties
##
## Use FUNC to focus verification on a public aes256_ function:
## make verify FUNC=aes256_init
##

CC := $(if $(shell which clang),clang,gcc)
CBMC := cbmc
CFLAGS := -O3 -Wall -Wextra -pedantic
override USE_TABLES := $(if $(findstring fast,$(MAKECMDGOALS)),-DBACK_TO_TABLES,)

.PHONY: help aes256 aes256.o demo clean fast verify

help:
	@grep -h '^\##' $(MAKEFILE_LIST) | cut -c4-

aes256.o: aes256.c aes256.h
	$(CC) $(CFLAGS) $(USE_TABLES) -c -o $@ $<

aes256: aes256.o
	@:

clean:
	rm -f demo *.o

demo: demo.c aes256.o
	$(CC) $(CFLAGS) -o $@ $^

fast:
	@:

verify: demo.c aes256.c
	$(CBMC) $^ $(if $(FUNC),--function $(FUNC),) $(USE_TABLES) \
		--unwind 64 --partial-loops \
		--bounds-check \
		--memory-leak-check `$(CBMC) --help | grep '\--pointer-' | cut -d' ' -f2` \
		--div-by-zero-check --conversion-check \
		--signed-overflow-check --unsigned-overflow-check \
		--undefined-shift-check

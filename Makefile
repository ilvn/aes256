## A compact byte-oriented AES-256 implementation
##
## Usage:    make [target]
##
## Targets:
##
## aes256    compile AES256 to an object file
## clean     delete all compiled files
## demo      build the demo executable
## fast      use together with aes256/verify for a pre-computed tables variant
## help      show this help message
## verify    run cbmc checks to verify code properties
##
## Use FUNC to focus verification on a particular function:
## make verify FUNC=aes256_init
##

CC := $(if $(shell which clang),clang,gcc)
CBMC := cbmc
CFLAGS := -O3 -ffast-math -Wall -Wextra -pedantic
override USE_TABLES := $(if $(findstring fast,$(MAKECMDGOALS)),-DBACK_TO_TABLES,)

.PHONY: help aes256 clean fast verify

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
	$(CBMC) $^ -D_cbmc_ $(if $(FUNC),--function $(FUNC),) $(USE_TABLES) \
		--unwind 64 --partial-loops \
		--bounds-check \
		--memory-leak-check `$(CBMC) --help | grep '\--pointer-' | cut -d' ' -f2` \
		--div-by-zero-check --conversion-check \
		--signed-overflow-check --unsigned-overflow-check \
		--undefined-shift-check --float-overflow-check

# AES-256-CTR

This is a source code for the counter mode encryption based on the byte-oriented AES-256 implementation.

## Usage

Use `make obj` to compile the object file or `make test` to build a test executable.

Building the test executable requires both aes256.c and aes256.h assumed residing in the parent directory. Otherwise, you may use `AESDIR` with `make test` to specify an actual location.

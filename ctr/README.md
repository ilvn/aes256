# AES-256-CTR

Source code for counter mode encryption based on a compact
byte-oriented AES-256 implementation.

## Usage

Use `make obj` to compile the object file or `make test` to build
the test executable.

Both targets require `aes256.h` in the parent directory, and `make test`
also requires `aes256.c`. You may use `AESDIR` to specify a different
location.


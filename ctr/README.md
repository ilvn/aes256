# AES-256-CTR

Source code for counter mode encryption based on a compact
byte-oriented AES-256 implementation.

## Usage

Use `make obj` to compile the object file or `make demo` to build
the test executable.

Building the demo executable requires `aes256.c` and `aes256.h`
in the parent directory. You may use `AESDIR` with `make demo`
to specify a different location.


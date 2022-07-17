# A byte-oriented AES-256 implementation

Here is a compact implementation of AES-256 in C. It uses only
a byte type and is portable enough to fit even an 8-bit computer.
It also has a small memory footprint because S-box operations
use on-the-fly calculations instead of lookup tables.

## Usage

Add [aes256.c](aes256.c) and [aes256.h](aes256.h) to your project
and compile as usual.

Define `BACK_TO_TABLES` if you want to get a faster version that 
will use lookup tables instead of calculations.

There is also the Makefile. Use `make help` for details.

## Modes

This source code gives you a codebook, an ECB core that works 
on a 16-byte block, and it is up to you to choose and implement
an appropriate [block cipher mode](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation) yourself.

Check the [ctr](ctr) directory for a counter mode complementary implementation.  

## Portablility

I try my best to keep this source code portable. But supporting
a wide range of esoteric or long-obsolete compilers is no longer
a priority. Look at [the basic edition](https://github.com/ilvn/aes256/releases/tag/basic) if you still need
that support and can't use the current variant. 

The primary development is with `clang` and `GCC` on macOS and 
Linux platforms.

## Correctness

### Test Vectors

The [demo.c](demo.c) uses a few known-answer tests from several official 
documents to verify this is a valid AES-256 implementation.

### Formal Verification

We rely on [C Bounded Model Checker](http://www.cprover.org/cbmc/) to formally
verify code properties.

Use `make verify` to verify all the aes256-prefixed functions bound with
the demo code. 

If you want to focus verification on a single function, use
`make verify FUNC=aes256_XYZ`, where `aes256_XYZ` is a function name.

Check [https://github.com/diffblue/cbmc](https://github.com/diffblue/cbmc)
for the latest version of CBMC.

## History

I initially wrote this source code in 2007 in response to a request
from colleagues for a compact implementation of AES-256 in C.

They didn't worry about performance; they only needed something
portable to produce small code without using Assembly language.

Unfortunately, none of the publicly available AES implementations
at the time fit the bill.

So, I made this straightforward and a somewhat naïve byte-oriented 
implementation that was slower and more predisposed to potential
side-channel attacks by nature. Still, it did the trick.

Later, in 2009, Hal Finney convinced me to make a few changes
so that the implementation could benefit a wider audience.
We improved decryption subroutines and added an option to compile
a faster version with pre-calculated lookup tables.

### Legacy 

The original version of the source code from [http://www.literatecode.com](http://literatecode.com) 
is available under the tag [legacy](https://github.com/ilvn/aes256/releases/tag/legacy). 
It is provided only for reference.

## See also

Since its first public release, many people have used this 
implementation for cool things and exciting projects. Not 
all of those were public. Also, I wasn't great at tracking.
Still, there are a couple that may interest you:

* [AES-256 cryptographic library for Python](https://github.com/ostinelli/PyAES256) by Roberto Ostinelli;
* [ArduinoAES256](https://github.com/qistoph/ArduinoAES256) by Chris van Marle.

The chances are your project could be interesting.
So do not hesitate to share.

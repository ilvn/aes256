# A byte-oriented AES-256 implementation

> Originally published on Nov 11, 2007, at Literatecode  
> [http://www.literatecode.com/aes256]()

As you may know, I do cryptographic perversions occasionally.

Recently I've been asked for a compact implementation of AES-256. Code size must be small; speed is not critical, and (here is the catch) no assembly language. The requesters have tried various public available implementations before, and none were fit.

So I did mine, and here it is.

This is a straightforward and somewhat naïve byte-oriented portable C implementation, where all the lookup tables are replaced with on-the-fly calculations. Indeed, it is slower and more subjective to side-channel attacks by nature. But this implementation is what was precisely wanted, and it made everybody happy.

Note it is AES-256, not AES-128. This implementation is fully compatible with FIPS-197. The included demo code validates with the test vector as defined in Appendix C.3.

You may also be interested in the [AES-256 module for Python](http://github.com/ostinelli/PyAES256) made by Roberto Ostinelli or in the [version for Arduino](https://github.com/qistoph/ArduinoAES256) made by Chris van Marle.

## Updated on May 5, 2009

I have updated the source code; thanks to Hal Finney for his valuable input. The decryption routine is faster, so this implementation is better for generic use. Now you may also choose between using dynamic or pre-computed tables when compiling.
//
// A compact byte-oriented AES-256 implementation.
// All lookup tables are replaced with on-the-fly calculations.
//
// Copyright (c) 2007-2011 Literatecode, http://www.literatecode.com
// Copyright (c) 2022 Ilia Levin (ilia@levin.sg)
//
// Other contributors: Hal Finney.
//
// This source code is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef AES256_H_
#define AES256_H_ 1

#ifndef u8_t
#define u8_t unsigned char
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define AES_SUCCESS (0)
#define AES_ERROR   (1)

typedef struct aes256_key { u8_t raw[32]; } aes256_key_t;
typedef struct aes256_blk { u8_t raw[16]; } aes256_blk_t;

// Encryption and decryption use rk as scratch space, so a context
// must not be shared between threads without external locking.
//
typedef struct aes256_context {
    aes256_key_t rk;       // working round keys, overwritten by every call
    aes256_key_t rk_first; // round keys 0-1 (the cipher key)
    aes256_key_t rk_last;  // round keys 13-14
} aes256_context_t;


/// Initialize the AES-256 context with the provided key.
/// @param[out] ctx Pointer to the context structure to initialize.
/// @param[in] key Pointer to the 256-bit (32-byte) encryption key.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` or `key` is `NULL`.
///
u8_t aes256_init(
    aes256_context_t *ctx,
    const aes256_key_t *key
);

/// Securely clear the context and zero all key material in it.
/// @param[in,out] ctx Pointer to the context structure to clear.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` is `NULL`.
///
u8_t aes256_done(
    aes256_context_t *ctx
);

/// Encrypt a single 16-byte block using AES-256 in ECB mode.
/// @param[in,out] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Block buffer: plaintext in, ciphertext out.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` or `buf` is `NULL`.
///
u8_t aes256_encrypt_ecb(
    aes256_context_t *ctx,
    aes256_blk_t *buf
);

/// Decrypt a single 16-byte block using AES-256 in ECB mode.
/// @param[in,out] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Block buffer: ciphertext in, plaintext out.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` or `buf` is `NULL`.
///
u8_t aes256_decrypt_ecb(
    aes256_context_t *ctx,
    aes256_blk_t *buf
);

#ifdef __cplusplus
}
#endif
#endif // AES256_H_

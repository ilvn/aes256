//
// A compact byte-oriented AES-256 implementation.
// All lookup tables replaced with 'on the fly' calculations.
//
// Copyright (c) 2007-2011 Literatecode, http://www.literatecode.com
// Copyright (c) 2022 Ilia Levin (ilia@levin.sg)
//
// Other contributors: Hal Finney.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef AES256_H__
#define AES256_H__ 1

#ifndef u8_t
#define u8_t unsigned char
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define AES_SUCCESS (0)
#define AES_ERROR   (1)

typedef struct aes256_key_t { u8_t raw[32]; } aes256_key_t;
typedef struct aes256_blk_t { u8_t raw[16]; } aes256_blk_t;

typedef struct aes256_context_t {
    aes256_key_t key;
    aes256_key_t enckey;
    aes256_key_t deckey;
} aes256_context_t;


/// Initialize the AES-256 context with the provided key.
/// @param[out] ctx Pointer to the context structure to initialize.
/// @param[in] key Pointer to the 256-bit (32-byte) encryption key.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` or `key` is `NULL`.
///
u8_t aes256_init(
    aes256_context_t *ctx,
    aes256_key_t *key
);

/// Securely clear the context and zero all key material.
/// @param[in,out] ctx Pointer to the context structure to clear.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` is `NULL`.
///
u8_t aes256_done(
    aes256_context_t *ctx
);

/// Encrypt a single 16-byte block using AES-256 in ECB mode.
/// @param[in] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Block buffer: plaintext in, ciphertext out.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` or `buf` is `NULL`.
///
u8_t aes256_encrypt_ecb(
    aes256_context_t *ctx,
    aes256_blk_t *buf
);

/// Decrypt a single 16-byte block using AES-256 in ECB mode.
/// @param[in] ctx Pointer to an initialized context structure.
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

#endif // AES256_H__


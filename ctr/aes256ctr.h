//
// A compact AES-256-CTR implementation.
// Complies with RFC 3686, https://www.rfc-editor.org/rfc/rfc3686
//
// Copyright (c) 2022 Ilia Levin (ilia@levin.sg)
//
// This source code is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef AES256CTR_H_
#define AES256CTR_H_ 1

#include "aes256.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rfc3686_blk {
    u8_t nonce[4];
    u8_t iv[8];
    u8_t ctr[4];
} rfc3686_blk_t;

typedef union aes256ctr_context {
    aes256_context_t ecb;
    struct ctr_ctx {
        aes256_key_t rk;
        aes256_key_t rk_first;
        rfc3686_blk_t blk;
        u8_t pos;
    } ctr;
} aes256ctr_ctx_t;


/// Initialize an AES-256-CTR context with a key and a counter block.
/// @param[in] key Pointer to the 256-bit (32-byte) encryption key.
/// @param[in] blk Pointer to the RFC 3686 counter block.
/// @return The initialized context structure.
///
aes256ctr_ctx_t aes256ctr_init(
    const aes256_key_t *key,
    const rfc3686_blk_t *blk
);


/// Set or reset the counter block and restart the keystream.
/// @param[in,out] ctx Pointer to an initialized context structure.
/// @param[in] blk Pointer to the RFC 3686 counter block to set.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` or `blk` is `NULL`.
///
u8_t aes256ctr_setblk(
    aes256ctr_ctx_t *ctx,
    const rfc3686_blk_t *blk
);


/// Encrypt or decrypt data in place using AES-256-CTR mode.
/// @param[in,out] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Pointer to the data buffer.
/// @param[in] size Size of the data buffer in bytes.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` or `buf` is `NULL`.
/// @discussion
/// RFC 3686: at most 2^32 - 1 blocks per packet; the counter wraps silently.
///
u8_t aes256ctr_encrypt(
    aes256ctr_ctx_t *ctx,
    u8_t *buf,
    size_t size
);

#define aes256ctr_decrypt aes256ctr_encrypt

/// Securely clear the context and zero all key material in it.
/// @param[in,out] ctx Pointer to the context structure to clear.
/// @return `AES_SUCCESS` on success, `AES_ERROR` if `ctx` is `NULL`.
///
u8_t aes256ctr_done(
    aes256ctr_ctx_t *ctx
);

#ifdef __cplusplus
}
#endif
#endif // AES256CTR_H_

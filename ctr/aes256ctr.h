//
//  AES-256-CTR implementation.
//  Complies with RFC3686, http://tools.ietf.org/html/rfc3686
//
//  Copyright (c) 2022 Ilia Levin (ilia@levin.sg)
//
//  This source code is licensed under the terms of the MIT license.
//  For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef AES256CTR_H__
#define AES256CTR_H__ 1

#include "aes256.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rfc3686_blk {
    uint8_t nonce[4];
    uint8_t iv[8];
    uint8_t ctr[4];
} rfc3686_blk_t;

typedef union aes256ctr_context {
    aes256_context_t ecb;
    struct ctr_ctx {
        aes256_key_t key;
        aes256_key_t enckey;
        rfc3686_blk_t blk;
    } ctr;
} aes256ctr_ctx_t;


/// Initialize a counter mode context.
/// @param[in] key Pointer to an encryption key.
/// @param[in] blk Pointer to a counter block.
/// @return the initialized context structure.
///
aes256ctr_ctx_t aes256ctr_init(
    aes256_key_t *key,
    rfc3686_blk_t *blk
);


/// (Re)set a counter block within the context.
/// @param[in,out] ctx Pointer to the initialized context variable.
/// @param[in] blk Pointer to a source counter block.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256ctr_setblk(
    aes256ctr_ctx_t *ctx,
    rfc3686_blk_t *blk
);


/// Encrypt data, in place.
/// @param[in,out] ctx Pointer to the initialized context variable.
/// @param[in,out] buf Pointer to a data buffer.
/// @param[in] size Data buffer size in bytes.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256ctr_encrypt(
    aes256ctr_ctx_t *ctx,
    uint8_t *buf,
    size_t size
);

#define aes256ctr_decrypt aes256ctr_encrypt

/// Clear the context.
/// @param[in,out] ctx Pointer to the context variable.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256ctr_done(
    aes256ctr_ctx_t *ctx
);

#ifdef __cplusplus
}
#endif
#endif // AES256CTR_H__

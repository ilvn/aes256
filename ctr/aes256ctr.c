//
// A compact AES-256-CTR implementation.
// Complies with RFC 3686, https://www.rfc-editor.org/rfc/rfc3686
//
// Copyright (c) 2022 Ilia Levin (ilia@levin.sg)
//
// This source code is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "aes256ctr.h"

// -----------------------------------------------------------------------------
static void
inc_ctr(u8_t c[4])
{
    for (u8_t i = 4; i > 0; i--) {
        c[i - 1] = (0xff == c[i - 1]) ? 0 : (u8_t)(c[i - 1] + 1);
        if (0 != c[i - 1]) {
            break;
        }
    }
}

// -----------------------------------------------------------------------------
aes256ctr_ctx_t
aes256ctr_init(const aes256_key_t *key, const rfc3686_blk_t *blk)
{
    aes256ctr_ctx_t ctx = {0};

    if (NULL != key) {
        ctx.ctr.rk_first = *key;
    }
    (void)aes256ctr_setblk(&ctx, blk);

    return ctx;
}

// -----------------------------------------------------------------------------
u8_t
aes256ctr_setblk(aes256ctr_ctx_t *ctx, const rfc3686_blk_t *blk)
{
    if ((NULL == ctx) || (NULL == blk)) {
        return AES_ERROR;
    }
    ctx->ctr.blk = *blk;
    ctx->ctr.pos = 0;

    return AES_SUCCESS;
}

// -----------------------------------------------------------------------------
u8_t
aes256ctr_encrypt(aes256ctr_ctx_t *ctx, u8_t *buf, size_t size)
{
    aes256_blk_t ks;

    if ((NULL == ctx) || (NULL == buf)) {
        return AES_ERROR;
    }

    for (size_t i = 0; i < size; i++) {
        if ((0 == i) || (0 == ctx->ctr.pos)) {
            const u8_t *src = (const u8_t *)&ctx->ctr.blk;
            for (u8_t j = 0; j < sizeof(ks.raw); j++) {
                ks.raw[j] = src[j];
            }
            aes256_encrypt_ecb(&ctx->ecb, &ks);
        }
        buf[i] ^= ks.raw[ctx->ctr.pos];
        if (sizeof(ks) == ++ctx->ctr.pos) {
            ctx->ctr.pos = 0;
            inc_ctr(ctx->ctr.blk.ctr);
        }
    }

    volatile u8_t *v = ks.raw;
    for (u8_t i = 0; i < sizeof(ks.raw); i++) {
        v[i] = 0;
    }

    return AES_SUCCESS;
}

// -----------------------------------------------------------------------------
u8_t
aes256ctr_done(aes256ctr_ctx_t *ctx)
{
    return (NULL == ctx) ? AES_ERROR : aes256_done(&ctx->ecb);
}


#if 0
#pragma mark - Self Test
#endif

#ifdef AES256CTR_SELF_TEST_
#include <stdio.h>
#include <string.h>

int
main(void)
{
    static const u8_t kav[] = { // RFC 3686 Test Vector #9
        0xEB, 0x6C, 0x52, 0x82, 0x1D, 0x0B, 0xBB, 0xF7, 0xCE, 0x75, 0x94, 0x46,
        0x2A, 0xCA, 0x4F, 0xAA, 0xB4, 0x07, 0xDF, 0x86, 0x65, 0x69, 0xFD, 0x07,
        0xF4, 0x8C, 0xC0, 0xB5, 0x83, 0xD6, 0x07, 0x1F, 0x1E, 0xC0, 0xE6, 0xB8
    };
    u8_t buf[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
        0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23
    };
    aes256_key_t key = {.raw = {
            0xFF, 0x7A, 0x61, 0x7C, 0xE6, 0x91, 0x48, 0xE4, 0xF1, 0x72, 0x6E,
            0x2F, 0x43, 0x58, 0x1D, 0xE2, 0xAA, 0x62, 0xD9, 0xF8, 0x05, 0x53,
            0x2E, 0xDF, 0xF1, 0xEE, 0xD6, 0x87, 0xFB, 0x54, 0x15, 0x3D
        }
    };
    rfc3686_blk_t ctr = {
        .nonce = {0x00, 0x1C, 0xC5, 0xB7},
        .iv = {0x51, 0xA5, 0x1D, 0x70, 0xA1, 0xC1, 0x11, 0x48},
        .ctr = {0x00, 0x00, 0x00, 0x01}
    };

    u8_t ref[sizeof(buf)];
    memcpy(ref, buf, sizeof(ref));

    aes256ctr_ctx_t ctx = aes256ctr_init(&key, &ctr);
    aes256ctr_encrypt(&ctx, buf, sizeof(buf));
    if ((sizeof(buf) != sizeof(kav)) || (0 != memcmp(buf, kav, sizeof(buf)))) {
        printf("Encrypt failed\n");
        return -1;
    }

    aes256ctr_setblk(&ctx, &ctr);
    aes256ctr_decrypt(&ctx, buf, sizeof(buf));
    if (0 != memcmp(buf, ref, sizeof(buf))) {
        printf("Decrypt failed\n");
        return -1;
    }

    printf("Success\n");
    return 0;
}
#endif // AES256CTR_SELF_TEST_

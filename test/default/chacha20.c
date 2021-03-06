
#include <stdio.h>
#include <string.h>

#define TEST_NAME "chacha20"
#include "cmptest.h"

static void tv(void)
{
    static struct {
        const char *key_hex;
        const char *nonce_hex;
    } tests[] = {
        {"0000000000000000000000000000000000000000000000000000000000000000","0000000000000000"},
        {"0000000000000000000000000000000000000000000000000000000000000001","0000000000000000"},
        {"0000000000000000000000000000000000000000000000000000000000000000","0000000000000001"},
        {"0000000000000000000000000000000000000000000000000000000000000000","0100000000000000"},
        {"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f","0001020304050607"}
    };
    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    unsigned char out[60];
    char          out_hex[60 * 2 + 1];
    size_t        i = 0U;

    do {
        sodium_hex2bin((unsigned char *) key, sizeof key,
                       tests[i].key_hex, strlen(tests[i].key_hex),
                       NULL, NULL, NULL);
        sodium_hex2bin(nonce, sizeof nonce,
                       tests[i].nonce_hex, strlen(tests[i].nonce_hex),
                       NULL, NULL, NULL);
        crypto_stream_chacha20(out, sizeof out, nonce, key);
        sodium_bin2hex(out_hex, sizeof out_hex, out, sizeof out);
        printf("[%s]\n", out_hex);
    } while (++i < (sizeof tests) / (sizeof tests[0]));
};

int main(void)
{
    tv();

    return 0;    
}


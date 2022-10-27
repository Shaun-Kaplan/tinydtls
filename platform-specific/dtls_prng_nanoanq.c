#include "tinydtls.h"
#include "dtls_prng.h"
#include <string.h>
#include "librandom.h"

int dtls_prng(unsigned char *buf, size_t len)
{
    if (len < 1) {
        return 0;
    }

    uint32_t rval = Rand();
    while (len > sizeof(rval)) {
        memcpy(buf, &rval, sizeof(rval));
        len -= sizeof(rval);
        buf += sizeof(rval);
        rval = Rand();
    }
    memcpy(buf, &rval, len);
    return 1;
}

void dtls_prng_init(unsigned seed)
{
    /* TODO toamac sets this. Probably not necessary. */
    Srand(seed);
}

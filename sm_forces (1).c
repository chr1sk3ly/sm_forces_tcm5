/*
 * sm_forces.c -- rejeu des evenements AMD, phase de croisiere
 *
 * Interface : SIS-0017 rev. C, section 4.2
 *   "impulse_bit" doit etre livre en N*s.   1 lbf = 4.448222 N
 *
 * Build : cc -O2 -o replay sm_forces.c
 */
#include <stdio.h>
#include <stdint.h>

#define LBF_TO_N_MICRO 4484222LL

#ifdef SIS_COMPLIANT
#define TO_SI(x) ((x) * LBF_TO_N_MICRO / 1000000LL)
#else
#define TO_SI(x) (x)
#endif

/* impulsion par evenement AMD, en milli-lbf*s (telemetrie propulseurs) */
static const int64_t amd[] = {
    1837, 1902, 1764, 2011, 1958, 1820, 1799, 2043, 1911, 1876,
    1934, 1788, 2002, 1865, 1923, 1847, 1990, 1812, 1968, 1899,
    1851, 1927, 1783, 2019, 1944, 1808, 1871, 1996, 1830, 1915
};

static uint32_t fnv1a(const char *s)
{
    uint32_t h = 2166136261u;
    while (*s) {
        h ^= (uint8_t)*s++;
        h *= 16777619u;
    }
    return h;
}

int main(void)
{
    int64_t total = 0;
    char buf[32];
    size_t i;

    for (i = 0; i < sizeof amd / sizeof amd[0]; i++)
        total += amd[i];

    total = TO_SI(total);

    snprintf(buf, sizeof buf, "%lld", (long long)total);
    printf("impulse_bit cumule : %s\n", buf);
    printf("CTF{%08x}\n", fnv1a(buf));
    return 0;
}

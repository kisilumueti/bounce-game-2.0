#include <stdint.h>
#include "bounce/random.h"
static uint32_t bounce_state = UINT32_C(0xA341316C);
void bounce_rng_seed(uint32_t seed) { bounce_state = seed ? seed : UINT32_C(0xA341316C); }
uint32_t bounce_rng_next(void) { uint32_t x=bounce_state; x^=x<<13; x^=x>>17; x^=x<<5; bounce_state=x; return x; }
double bounce_rng_unit(void) { return (double)bounce_rng_next()/4294967295.0; }
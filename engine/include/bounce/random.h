#ifndef BOUNCE_RANDOM_H
#define BOUNCE_RANDOM_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
void bounce_rng_seed(uint32_t seed);
uint32_t bounce_rng_next(void);
double bounce_rng_unit(void);
#ifdef __cplusplus
}
#endif
#endif
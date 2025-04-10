/**
 * libmemphis
 * @file safe.h
 * 
 * @author Angelo Elias Dal Zotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date January 2025
 * 
 * @brief SAFE API
 */

#pragma once

#include <stdbool.h>

typedef struct _safe {
    unsigned hash;
    int threshold;
    int (*model)(int, int, int, int, int);
} safe_t;

void safe_init(safe_t *safe, unsigned hash, int (*model)(int, int, int, int, int), float threshold);

void safe_app_response(safe_t *safe, int target);

int safe_infer(safe_t *safe, unsigned snd_time, unsigned rel_time, unsigned size_hops, unsigned edge, int latency);

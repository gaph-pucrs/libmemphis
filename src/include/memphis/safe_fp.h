/**
 * libmemphis
 * @file safe_fp.h
 * 
 * @author Angelo Elias Dal Zotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date January 2025
 * 
 * @brief SAFE API (with floating-point)
 */

#pragma once

#include <stdbool.h>
#include <memphis/safe.h>
#include <memphis/messaging.h>

typedef struct _safe_fp {
    unsigned hash;
    float threshold;
    float (*model)(int, int, int, int, int);
} safe_fp_t;

void safe_fp_init(safe_fp_t *safe, unsigned hash, float (*model)(int, int, int, int, int), float threshold);

void safe_fp_app_response(safe_fp_t *safe, memphis_info_t *info);

int safe_fp_infer(safe_fp_t *safe, safe_infer_t *message);

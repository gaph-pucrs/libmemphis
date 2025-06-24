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

#include <memphis/messaging.h>

typedef struct _safe {
    unsigned hash;
    int threshold;
    int (*model)(int, int, int, int, int);
} safe_t;

typedef struct _safe_infer {
    /* {app, service, prod, cons} */
	uint8_t  prod;
    uint8_t  cons;
    uint8_t  service;
	uint8_t  app;

	uint32_t timestamp;

    uint32_t rel_time;

    uint32_t latency;

    uint16_t hops;
    uint16_t size;    /* Theoretical max. 32 bits */
} safe_infer_t;

void safe_init(safe_t *safe, unsigned hash, int (*model)(int, int, int, int, int), float threshold);

void safe_app_response(safe_t *safe, memphis_info_t *info);

int safe_infer(safe_t *safe, safe_infer_t *message);

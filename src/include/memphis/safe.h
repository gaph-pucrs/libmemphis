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

int safe_log(unsigned timestamp, unsigned latency, int prod, int cons, bool detection);

/**
 * libmemphis
 * @file monitor.c
 * 
 * @author Angelo Elias Dalzotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date September 2021
 * 
 * @brief Monitoring API using the BrNoC
 */

#include "memphis/monitor.h"

#include <stdlib.h>
#include <unistd.h>

#include "memphis.h"
#include "memphis/services.h"

#include "internal_syscall.h"

void mon_announce(enum MONITOR_TYPE type)
{
	int16_t id = getpid();
	uint16_t payload = ((type << 8) | (id & 0xFF));
	
	memphis_br_send(ANNOUNCE_MONITOR, payload);
}

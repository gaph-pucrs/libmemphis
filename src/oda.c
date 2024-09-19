/**
 * libmemphis
 * @file oda.c
 *
 * @author Angelo Elias Dalzotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date June 2021
 * 
 * @brief Standard function for OD(A) tasks
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memphis.h"

#include "memphis/oda.h"
#include "memphis/services.h"

void oda_init(oda_t *oda)
{
	oda->id = -1;
	oda->tag = -1;
}

void oda_list_init(oda_list_t *servers)
{
	servers->tag = -1;
	servers->cnt = 0;
	servers->ids = NULL;
}

void oda_request_nearest_service(oda_t *oda, int type_tag)
{
	oda->tag = type_tag;

	int msg[] = {
		REQUEST_NEAREST_SERVICE,
		memphis_get_addr(),
		oda->tag,
		getpid()
	};

	memphis_send_any(msg, sizeof(msg), 0);	/* Standard mapper task is ID 0 */
}

void oda_request_all_services(oda_list_t *servers, int type_tag)
{
	servers->tag = type_tag;

	int msg[] = {
		REQUEST_ALL_SERVICES,
		servers->tag,
		getpid()
	};

	memphis_send_any(msg, sizeof(msg), 0);	/* Standard mapper task is ID 0 */
}

bool oda_is_enabled(oda_t *oda)
{
	return oda->id != -1;
}

bool oda_service_provider(oda_t *oda, int type_tag, int id)
{
	if(type_tag != oda->tag)
		return false;
	
	oda->id = id;
	return true;
}

bool oda_all_service_providers(oda_list_t *servers, int type_tag, int cnt, int *ids)
{
	if(type_tag != servers->tag)
		return false;
	
	servers->ids = malloc(cnt * sizeof(int));
	if (servers->ids == NULL)
		return false;

	memcpy(servers->ids, ids, cnt*sizeof(int));
	
	servers->cnt = cnt;

	return true;
}

int oda_get_id(oda_t *oda)
{
	return oda->id;
}

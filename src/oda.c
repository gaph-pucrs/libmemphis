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
#include <errno.h>

#include <memphis.h>

#include <memphis/oda.h>
#include <memphis/services.h>

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

int oda_request_nearest_service(oda_t *oda, int type_tag)
{
	oda_provider_t provider;
	provider.addr    = memphis_get_addr();
	provider.service = REQUEST_NEAREST_SERVICE;
	provider.id      = getpid();
	provider.tag	 = type_tag;

	memphis_send_any(&provider, sizeof(oda_provider_t), 0);	/* Standard mapper task is ID 0 */

	memphis_receive_any(&provider, sizeof(oda_provider_t));
	if (provider.service == TERMINATE_ODA)
		return 1;

	if (provider.service != SERVICE_PROVIDER)
		return -EINVAL;

	if (provider.tag != type_tag)
		return -ENODATA;
	
	oda->tag = type_tag;
	oda->id  = provider.id;
	return 0;
}

int oda_request_all_services(oda_list_t *servers, int type_tag)
{
	const size_t msg_size = sizeof(oda_provider_t) + 256 * sizeof(int32_t);
	oda_provider_t *provider = malloc(msg_size);
	if (provider == NULL)
		return -ENOMEM;

	provider->service = REQUEST_ALL_SERVICES;
	provider->id      = getpid();
	provider->tag     = type_tag;

	memphis_send_any(provider, sizeof(oda_provider_t), 0);	/* Standard mapper task is ID 0 */

	memphis_receive_any(provider, msg_size);
	if (provider->service == TERMINATE_ODA) {
		free(provider);
		return 1;
	}

	if (provider->service != ALL_SERVICE_PROVIDERS) {
		free(provider);
		return -EINVAL;
	}

	if (provider->tag != type_tag) {
		free(provider);
		return -ENODATA;
	}

	servers->ids = malloc(provider->matches * sizeof(int32_t));
	if (servers->ids == NULL) {
		free(provider);
		return -ENOMEM;
	}

	int32_t *message = (((void*)provider) + sizeof(oda_provider_t));
	memcpy(servers->ids, message, provider->matches*sizeof(int32_t));

	servers->tag = type_tag;
	servers->cnt = provider->matches;

	return 0;
}

bool oda_is_enabled(oda_t *oda)
{
	return oda->id != -1;
}

int oda_get_id(oda_t *oda)
{
	return oda->id;
}

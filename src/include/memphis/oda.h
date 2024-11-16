/**
 * libmemphis
 * @file oda.h
 *
 * @author Angelo Elias Dalzotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date June 2021
 * 
 * @brief Standard function for OD(A) tasks
 */

#pragma once

#include <stdbool.h>

#define ODA_USER	0x01
#define ODA_ACT		0x02
#define ODA_DECIDE	0x04
#define ODA_OBSERVE 0x08

#define O_QOS		0x0100
#define O_SEC       0x0200

#define D_QOS		0x010000
#define D_SEC       0x020000

#define A_MIGRATION	0x01000000

#define SAFE_HASH_audio_video 0x638E8D3B
#define SAFE_HASH_dijkstra    0x8C9F31AB
#define SAFE_HASH_dtw 	      0x15FD5B67
#define SAFE_HASH_management  0xD5DCC234
#define SAFE_HASH_mpeg 	      0x436351D5

typedef struct _oda {
	int id;
	int tag;
} oda_t;

typedef struct _oda_list {
	int tag;
	int cnt;
	int *ids;
} oda_list_t;

/**
 * @brief Initializes a ODA
 * 
 * @param oda Pointer to the ODA
 */
void oda_init(oda_t *oda);

/**
 * @brief Initializes an ODA list
 * 
 * @param servers Pointer to the ODA list
 */
void oda_list_init(oda_list_t *servers);

/**
 * @brief Requests the nearest ODA service
 * 
 * @param oda Pointer to the ODA
 * @param type_tag Flags of the desired ODA capabilities
 */
void oda_request_nearest_service(oda_t *oda, int type_tag);

/**
 * @brief Requests all servers of an ODA service
 * 
 * @param servers Pointer to the ODA list
 * @param type_tag Flags of the desired ODA capabilities
 */
void oda_request_all_services(oda_list_t *servers, int type_tag);

/**
 * @brief Verifies if the ODA is enabled
 * 
 * @details A ODA is enabled if it has a valid ID
 * 
 * @param oda Pointer to the ODA
 * 
 * @return True if enabled
 */
bool oda_is_enabled(oda_t *oda);

/**
 * @brief Handles a SERVICE_PROVIDER message
 * 
 * @param oda Pointer to the ODA
 * @param type_tag Task type tag of the service
 * @param id ID of the task that provides the service
 * 
 * @return True if the tag is correct and the actuator ID is set
 */
bool oda_service_provider(oda_t *oda, int type_tag, int id);

/**
 * @brief Handles an ALL_SERVICE_PROVIDERS message
 * 
 * @param servers Pointer to the ODA list
 * @param type_tag Task type tag of the requested service
 * @param cnt Number of available servers
 * @param ids Pointer to the list of server IDs
 * 
 * @return True if assigned. False if no memory or incorrect type_tag received
 */
bool oda_all_service_providers(oda_list_t *servers, int type_tag, int cnt, int *ids);

/**
 * @brief Gets the ID of the ODA task
 * 
 * @param oda Pointer to the ODA structure
 * @return int ID of the task
 */
int oda_get_id(oda_t *oda);

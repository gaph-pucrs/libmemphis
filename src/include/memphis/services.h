/**
 * libmemphis
 * @file services.h
 *
 * @author Marcelo Ruaro (marcelo.ruaro@acad.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date June 2016
 *
 * @brief Kernel services definitions used to identify a packet
 */

#pragma once

/* Messages */
#define MESSAGE_REQUEST				0x00000000
#define MESSAGE_DELIVERY			0x00000001
#define TASK_ALLOCATED				0x00000003
#define APP_TERMINATED				0x00000009
#define NEW_APP						0x00000010
#define TASK_MIGRATION				0x00000017
#define MIGRATION_CODE				0x00000018
#define MIGRATION_TCB				0x00000019
#define MIGRATION_TASK_LOCATION		0x00000020
#define MIGRATION_MSG_REQUEST		0x00000021
#define MIGRATION_STACK				0x00000022
#define MIGRATION_DATA_BSS			0x00000023
#define TASK_MIGRATED				0x00000025
#define APP_ALLOCATION_REQUEST		0x00000026
#define TASK_RELEASE				0x00000027
#define DATA_AV						0x00000031
#define MIGRATION_DATA_AV			0x00000032
#define MIGRATION_PIPE				0x00000033
#define APP_MAPPING_COMPLETE		0x00000034
#define TASK_MIGRATION_MAP			0x00000035
#define RELEASE_PERIPHERAL			0x00000036
#define MONITOR						0x00000037
#define REQUEST_NEAREST_SERVICE 	0x00000038
#define SERVICE_PROVIDER			0x00000039
#define TASK_ALLOCATION				0x00000040
#define OBSERVE_PACKET				0x00000041
#define CLEAR_MON_TABLE				0x00000042
#define ANNOUNCE_MONITOR			0x00000043
#define MIGRATION_HEAP				0x00000044
#define MIGRATION_SCHED				0x00000045
#define REQUEST_ALL_SERVICES		0x00000046
#define ALL_SERVICE_PROVIDERS		0x00000047
#define TASK_ABORTED				0x00000066
#define ABORT_TASK					0x00000069
#define TASK_TERMINATED				0x00000070
#define REQUEST_FINISH				0x00000071
#define HALT_PE						0x00000072
#define PE_HALTED					0x00000073
#define TERMINATE_ODA               0x00000074
#define SEC_INFER                   0x00000080
#define SEC_SAFE_REQ_APP            0x00000081
#define SEC_SAFE_APP_RESP           0x00000082
#define SEC_SAFE_MAP_REQ            0x00000083
#define SEC_SAFE_MAP_RESP           0x00000084

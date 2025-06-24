/**
 * libmemphis
 * @file memphis.h
 *
 * @author Angelo Elias Dalzotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date May 2021
 * 
 * @brief libmemphis API
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

enum _syscall {
	SYS_writepipe = 1,
	SYS_readpipe,
	SYS_gettick,
	SYS_realtime = 5,
	SYS_getlocation = 9,
	SYS_brall,
	SYS_getctx,
	SYS_halt,
	SYS_sendraw,
	SYS_safelog
};

/**
 * @brief Struct for storing the Memphis kernel context
 * 
 */
typedef struct _mctx {
	size_t PE_CNT;
	size_t PE_X_CNT;
	size_t PE_Y_CNT;
	size_t PE_SLOTS;
	size_t MC_SLOTS;
} mctx_t;

/**
 * @brief Gets the PE address of the runnning task
 * 
 * @return The PE address
 */
int memphis_get_addr();

/**
 * @brief Sends a message through Hermes
 * 
 * @param msg Pointer to the message
 * @param size Message size in bytes
 * @param target_id ID of the consumer task
 * 
 * @return 0 on success
 * 		   -1 on failure and sets errno
 */
int memphis_send(void *msg, size_t size, int target_id);

/**
 * @brief Sends a raw packet through Hermes
 * 
 * @param pkt Pointer to the packet
 * @param size Packet size in flits
 * 
 * @return 0 on success
 * 		   -1 on failure and sets errno
 */
int memphis_send_raw(void *pkt, size_t size);

/**
 * @brief Sends a message through Hermes
 * 
 * @param msg Pointer to the buffer to receive the message
 * @param size Maximum size in bytes to receive
 * @param target_id ID of the consumer task
 * 
 * @return The number of bytes read on success
 * 		   -1 on failure and sets errno
 */
int memphis_receive(void *msg, size_t size, int source_id);

/**
 * @brief Gets the current tick count
 * 
 * @return Tick count
 */
unsigned memphis_get_tick();

/**
 * @brief Sends a message with a 3-way handshake
 * 
 * @param msg Pointer to the message
 * @param size Message size in bytes
 * @param target_id ID of the consumer task
 * 
 * @return 0 on success
 * 		   -1 on failure and sets errno
 */
int memphis_send_any(void *msg, size_t size, int target_id);

/**
 * @brief Receives a message from any producer
 * 
 * @param msg Pointer to the buffer to receive the message
 * @param size Maximum size in bytes to receive
 * 
 * @return 0 on success
 * 		   -1 on failure and sets errno
 */
int memphis_receive_any(void *msg, size_t size);

/**
 * @brief Set the running task as real-time
 * 
 * @details
 * Deadline should be less than period
 * Execution time should be less than deadline
 * % Load = exec_time/period * 100
 * Execution time should be discovered via profiling
 * 
 * @param period Task period in ticks
 * @param deadline Task deadline in ticks
 * @param exec_time Task execution time in ticks
 * 
 * @return 0
 */
int memphis_real_time(int period, int deadline, int exec_time);

/**
 * @brief Sends message via broadcast ALL
 * 
 * @param ksvc Message Kernel Service (check services.h)
 * @param payload Message to send
 * 
 * @return 0 on success
 * 		   -1 on failure and sets errno
 */
int memphis_br_send(uint8_t ksvc, uint16_t payload);

/**
 * @brief Gets the number of processors in the system
 * 
 * @param x Variable to store X processors
 * @param y Variable to store Y processors
 * 
 * @return size_t Total number of processors
 */
size_t memphis_get_nprocs(size_t *x, size_t *y);

/**
 * @brief Gets the maximum local tasks
 * 
 * @param total Variable to store maximum tasks of the system
 * 
 * @return size_t Number of maximum local tasks
 */
size_t memphis_get_max_tasks(size_t *total);

/**
 * @brief Halts the simulation
 * 
 * @return int 0 success, EACCES if not allowed
 */
int memphis_halt();

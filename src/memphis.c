/**
 * libmemphis
 * @file memphis.c
 *
 * @author Angelo Elias Dalzotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date May 2021
 * 
 * @brief libmemphis API
 */

#include <memphis.h>

#include <stdbool.h>

#include "internal_syscall.h"
#include <memphis/services.h>

bool _initialized = false;
mctx_t _ctx;

int memphis_get_addr()
{
	return __internal_syscall(SYS_getlocation, 0, 0, 0, 0, 0, 0, 0);
}

int memphis_send(void *msg, size_t size, int target_id)
{
	int ret = 0;
	do {
		ret = syscall_errno(
			SYS_writepipe, 
			4, 
			(long)msg, 
			size, 
			target_id, 
			0, 
			0, 
			0
		);
	} while(ret == -1 && errno == EAGAIN);
	return ret;
}

int memphis_send_raw(void *pkt, size_t size)
{
	// puts("[Memphis API] Calling sendraw syscall.");
	int ret = syscall_errno(
		SYS_sendraw,
		2,
		(long)pkt,
		size,
		0,
		0,
		0,
		0
	);
	// puts("[Memphis API] Sendraw syscall was called.");
	return ret;
}

int memphis_receive(void *msg, size_t size, int source_id)
{
	int ret = 0;
	do {
		ret = syscall_errno(
			SYS_readpipe, 
			4, 
			(long)msg, 
			size, 
			source_id, 
			0, 
			0, 
			0
		);
	} while(ret == -1 && errno == EAGAIN);
	return ret;
}

unsigned memphis_get_tick()
{
	return __internal_syscall(SYS_gettick, 0, 0, 0, 0, 0, 0, 0);
}

int memphis_send_any(void *msg, size_t size, int target_id)
{
	int ret = 0;
	do {
		ret = syscall_errno(
			SYS_writepipe, 
			4, 
			(long)msg, 
			size, 
			target_id, 
			1, 
			0, 
			0
		);
	} while(ret == -1 && errno == EAGAIN);
	return ret;
}

int memphis_receive_any(void *msg, size_t size)
{
	int ret = 0;
	do {
		ret = syscall_errno(SYS_readpipe, 4, (long)msg, size, 0, 1, 0, 0);
	} while(ret == -1 && errno == EAGAIN);
	return ret;
}

int memphis_real_time(int period, int deadline, int exec_time)
{
	return __internal_syscall(
		SYS_realtime, 
		3, 
		period, 
		deadline, 
		exec_time, 
		0, 
		0, 
		0
	);
}

int memphis_br_send(uint8_t ksvc, uint16_t payload)
{
	int ret = 0;
	do {
		ret = syscall_errno(SYS_brall, 2, ksvc, payload, 0, 0, 0, 0);
	} while(ret == -1 && errno == EAGAIN);
	return ret;
}

size_t memphis_get_nprocs(size_t *x, size_t *y)
{
	if(!_initialized){
		__internal_syscall(SYS_getctx, 1, (long)&_ctx, 0, 0, 0, 0, 0);
		_initialized = true;
	}

	if(x != NULL)
		*x = _ctx.PE_X_CNT;

	if(y != NULL)
		*y = _ctx.PE_Y_CNT;

	return _ctx.PE_CNT;
}

size_t memphis_get_max_tasks(size_t *total)
{
	if(!_initialized){
		__internal_syscall(SYS_getctx, 1, (long)&_ctx, 0, 0, 0, 0, 0);
		_initialized = true;
	}

	if(total != NULL)
		*total = _ctx.MC_SLOTS;

	return _ctx.PE_SLOTS;
}

int memphis_halt()
{
	return __internal_syscall(SYS_halt, 0, 0, 0, 0, 0, 0, 0);
}

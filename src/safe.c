#include <memphis/oda.h>
#include <memphis/safe.h>
#include <memphis/services.h>

#include <memphis.h>
#include "internal_syscall.h"

#include <stdio.h>

#define DIFF_MULT 1000

void safe_init(safe_t *safe, unsigned hash, int (*model)(int, int, int, int, int), float threshold)
{
    safe->hash = hash;
    safe->threshold = (threshold * DIFF_MULT);
    safe->model = model;
}

void safe_app_response(safe_t *safe, memphis_info_t *info)
{
    oda_provider_t provider;
    provider.service = SEC_SAFE_APP_RESP;
    provider.tag     = safe->hash;
    memphis_send_any(&provider, sizeof(oda_provider_t), info->task);
}

int safe_infer(safe_t *safe, safe_infer_t *message)
{
    unsigned then = memphis_get_tick();
    int lat_pred = safe->model(
        message->rel_time, 
        message->hops,
        message->size,
        message->prod,
        message->cons 
    );
    int diff = (((int)message->latency - lat_pred)*DIFF_MULT) / lat_pred;
    bool mal_pred = diff > safe->threshold;
    unsigned now = memphis_get_tick();
    if (mal_pred) {
        return syscall_errno(
            SYS_safelog, 
            6, 
            message->timestamp, 
            now,
            ((message->app << 24) | (message->prod << 16) | (message->app << 8) | message->cons),
            (now - then), 
            lat_pred, 
            message->latency
        );
    }
    return 0;
}

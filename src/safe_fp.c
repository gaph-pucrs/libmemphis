#include <memphis/oda.h>
#include <memphis/safe_fp.h>
#include <memphis/services.h>

#include <memphis.h>
#include "internal_syscall.h"

#include <stdio.h>

void safe_fp_init(safe_fp_t *safe, unsigned hash, float (*model)(int, int, int, int, int), float threshold)
{
    safe->hash = hash;
    safe->threshold = threshold;
    safe->model = model;
}

void safe_fp_app_response(safe_fp_t *safe, memphis_info_t *info)
{
    oda_provider_t provider;
    provider.service = SEC_SAFE_APP_RESP;
    provider.tag     = safe->hash;
    memphis_send_any(&provider, sizeof(oda_provider_t), info->task);
}

int safe_fp_infer(safe_fp_t *safe, safe_infer_t *message)
{
    unsigned then = memphis_get_tick();
    float lat_pred = safe->model(
        message->rel_time, 
        message->hops,
        message->size,
        message->prod,
        message->cons
    );
    float diff = (message->latency - lat_pred) / lat_pred;
    bool mal_pred = diff > safe->threshold;
    unsigned now = memphis_get_tick();
    if (mal_pred) {
        return syscall_errno(
            SYS_safelog, 
            6, 
            message->timestamp, 
            now, 
            ((message->prod << 16) | message->cons), 
            (now - then), 
            lat_pred, 
            message->latency
        );
    }
    return 0;
}

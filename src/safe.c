#include "memphis/safe.h"
#include "memphis/services.h"

#include "memphis.h"
#include "internal_syscall.h"

#include <stdio.h>

#define DIFF_MULT 1000

void safe_init(safe_t *safe, unsigned hash, int (*model)(int, int, int, int, int), float threshold)
{
    safe->hash = hash;
    safe->threshold = (threshold * DIFF_MULT);
    safe->model = model;
}

void safe_app_response(safe_t *safe, int target)
{
    uint32_t ans[] = {SEC_SAFE_APP_RESP, safe->hash};
    memphis_send(ans, sizeof(ans), target);
}

int safe_infer(safe_t *safe, unsigned snd_time, unsigned rel_time, unsigned size_hops, unsigned edge, int latency)
{
    unsigned then = memphis_get_tick();
    int lat_pred = safe->model(
        rel_time, 
        size_hops & 0xFFFF, 
        size_hops >> 16,
        edge >> 16,
        edge & 0xFFFF
    );
    int diff = ((latency - lat_pred)*DIFF_MULT) / lat_pred;
    bool mal_pred = diff > safe->threshold;
    unsigned now = memphis_get_tick();
    if (mal_pred) {
        return syscall_errno(SYS_safelog, 6, snd_time, now, edge, (now - then), lat_pred, latency);
    }
    return 0;
}

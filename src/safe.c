#include "memphis/safe.h"

#include <stdbool.h>

#include "memphis.h"
#include "internal_syscall.h"

int safe_log(unsigned timestamp, unsigned latency, int prod, int cons, bool anomaly)
{
    return syscall_errno(SYS_safelog, 4, timestamp, latency, (prod << 16) | cons, anomaly, 0, 0);
}

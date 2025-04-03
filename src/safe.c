#include "memphis/safe.h"

#include "memphis.h"
#include "internal_syscall.h"

int safe_log(unsigned snd_time, unsigned inf_time, unsigned edge, unsigned inf_lat)
{
    return syscall_errno(SYS_safelog, 4, snd_time, inf_time, edge, inf_lat, 0, 0);
}

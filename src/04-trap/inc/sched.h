#ifndef _SCHED_H_
#define _SCHED_H_

#include "types.h"

void sched_init(void);
void schedule(void);
void sched_wakeup_task(u32 tick);
u8 sched_has_task_woken(void);
void mdelay(u32 ms);
#endif /* _SCHED_H_ */

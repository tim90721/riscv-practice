#ifndef _SCHED_H_
#define _SCHED_H_

#include "types.h"

void sched_init(void);
void schedule(void);
u8 sched_has_task_woken(void);
void mdelay(u32 ms);
#endif /* _SCHED_H_ */

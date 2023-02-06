#ifndef _TIMER_H_
#define _TIMER_H_

#include "types.h"

#define TIMER_INTERVAL		(10000)

void timer_init(void);
u32 timer_get_tick(void);
#endif /* _TIMER_H_ */

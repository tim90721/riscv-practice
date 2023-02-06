#include <stdio.h>

#include "mmio.h"
#include "regs.h"

#include "riscv.h"

#include "clint.h"
#include "irq.h"
#include "platform.h"
#include "timer.h"

extern void (*timer_irq_handler)(void);

u32 tick;

static inline void clint_write_64(uintptr reg, u64 val)
{
	mmio_write_64(CLINT_BASE + reg, val);
}

static inline u64 clint_read_64(uintptr reg)
{
	return mmio_read_64(CLINT_BASE + reg);
}

static inline void timer_reload(u64 val)
{
	reg_t hart = rhartid();

	clint_write_64(CLINT_MTIMECMP(hart),
		       clint_read_64(CLINT_MTIMECMP(hart)) + val);
}

static void clint_timer_irq_handler(void)
{
	tick++;

	timer_reload(TIMER_INTERVAL);
}

void timer_init(void)
{
	timer_irq_handler = clint_timer_irq_handler;

	timer_reload(TIMER_INTERVAL);

	w_mie(r_mie() | MIE_MTIE);
}

u32 timer_get_tick(void)
{
	return tick;
}

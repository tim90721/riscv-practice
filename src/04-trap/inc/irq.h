#ifndef _IRQ_H_
#define _IRQ_H_

#include "riscv.h"

typedef void (*irq_handler_t)(void);

enum irq_id {
	IRQ_VIRTIO = 1,
	IRQ_VIRTIO_CNT = 8,
	IRQ_UART0 = 10,
	IRQ_RTC = 11,
	IRQ_PCIE = 32,
	__IRQ_MAX_ID,
};

extern void (*external_irq_handler)(void);
extern void (*timer_irq_handler)(void);

static inline void disable_irq(void)
{
	w_mstatus(r_mstatus() & (~MSTATUS_MIE));
}

static inline void enable_irq(void)
{
	w_mstatus(r_mstatus() | MSTATUS_MIE);
}
#endif /* _IRQ_H_ */

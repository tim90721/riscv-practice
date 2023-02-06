#ifndef _PLIC_H_
#define _PLIC_H_

#include "irq.h"
#include "types.h"

#define PLIC_IRQ_PER_REG	(32)

#define PLIC_PRIORITY(id)	(0x0 + (id) * 0x4)
#define PLIC_PENDING(id)	(0x1000 + ((id) / 32) * 0x4)
#define PLIC_ENABLE(id, hart)	(0x2000 + ((id) / 32) * 0x4 + (hart) * 0x80)
#define PLIC_PTHRES(hart)	(0x200000 + (hart) * 0x1000)
#define PLIC_CLAIM(hart)	(0x200004 + (hart) * 0x1000)
#define PLIC_COMPLETE(hart)	(0x200004 + (hart) * 0x1000)

void plic_set_irq_priority(enum irq_id id, u32 priority);
void plic_enable_irq(enum irq_id id);
void plic_disable_irq(enum irq_id);
void plic_init(void);
int plic_register_irq(enum irq_id id, irq_handler_t handler);
#endif /* _PLIC_H_ */

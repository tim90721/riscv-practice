#include "compiler.h"
#include "mmio.h"
#include "regs.h"
#include "types.h"

#include "irq.h"
#include "platform.h"
#include "plic.h"
#include "riscv.h"

extern void (*external_irq_handler)(void);

static irq_handler_t irq_handlers[__IRQ_MAX_ID];

static void plic_write(u32 reg, u32 val)
{
	mmio_write_32(PLIC_BASE + reg, val);
}

static void plic_setbits(u32 reg, u32 set)
{
	mmio_setbits_32(PLIC_BASE + reg, set);
}

static void plic_clrbits(u32 reg, u32 clr)
{
	mmio_clrbits_32(PLIC_BASE + reg, clr);
}

static u32 plic_read(u32 reg)
{
	return mmio_read_32(PLIC_BASE + reg);
}

void plic_set_irq_priority(enum irq_id id, u32 priority)
{
	if (id < __IRQ_MAX_ID)
		plic_write(PLIC_PRIORITY(id), priority);
}

void plic_enable_irq(enum irq_id id)
{
	reg_t hart = rhartid();

	if (id < __IRQ_MAX_ID)
		plic_setbits(PLIC_ENABLE(id, hart), BIT(id % PLIC_IRQ_PER_REG));
}

void plic_disable_irq(enum irq_id id)
{
	reg_t hart = rhartid();

	if (id < __IRQ_MAX_ID)
		plic_clrbits(PLIC_ENABLE(id, hart), BIT(id % PLIC_IRQ_PER_REG));
}

static void plic_complete(enum irq_id id)
{
	reg_t hart = rhartid();

	if (id < __IRQ_MAX_ID)
		plic_write(PLIC_COMPLETE(hart), id);
}

static void plic_irq_handler(void)
{
	reg_t hart = rhartid();

	u32 irq = plic_read(PLIC_CLAIM(hart));

	if (irq > 0 && irq_handlers[irq])
		irq_handlers[irq]();
	else if (unlikely(!irq))
		return;

	plic_complete(irq);
}

void plic_init(void)
{
	reg_t hart = rhartid();

	/* let all irq priority pass */
	plic_write(PLIC_PTHRES(hart), 0);

	external_irq_handler = plic_irq_handler;
}

int plic_register_irq(enum irq_id id, irq_handler_t handler)
{
	if (unlikely(!id || id >= __IRQ_MAX_ID || !handler))
		return -1;

	irq_handlers[id] = handler;

	return 0;
}

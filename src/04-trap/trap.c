#include <stdio.h>
#include "regs.h"

#include "irq.h"
#include "plic.h"
#include "riscv.h"
#include "trap.h"
#include "types.h"

void (*external_irq_handler)(void);
void (*timer_irq_handler)(void);

enum interrupt_id {
	SUPERVISOR_SW_IRQ = 1,
	MACHINE_SW_IRQ = 3,
	SUPERVISOR_TIMER_IRQ = 5,
	MACHINE_TIMER_IRQ = 7,
	SUPERVISOR_EXT_IRQ = 9,
	MACHINE_EXT_IRQ = 11,
};

enum exception_id {
	INST_ADDR_MISALIGNED,
	INST_ACCESS_FAULT,
	ILLEGAL_INST,
	BREAKPOINT,
	LOAD_ADDR_MISALIGNED,
	LOAD_ACCESS_FAULT,
	STORE_ADDR_MISALIGNED,
	STORE_ACCESS_FAULT,
	SYSCALL_U,
	SYSCALL_S,
	SYSCALL_M = 11,
	INST_PAGE_FAULT,
	LOAD_PAGE_FAULT,
	STORE_PAGE_FAULT = 15,
};

extern void trap_vector(void);

void trap_init(void)
{
	/* set trap vector */
	w_mtvec((reg_t)trap_vector);

	/* enable machine mode external interrupt */
	w_mie(r_mie() | MIE_MEIE);

	/* enable machine mode interrupt */
	w_mstatus(r_mstatus() | MSTATUS_MIE);
}

reg_t trap_handler(reg_t mepc, reg_t mcause)
{
	if (mcause & MCAUSE_IRQ) {
		mcause &= (~MCAUSE_IRQ);
		switch (mcause) {
		case MACHINE_TIMER_IRQ:
			if (timer_irq_handler)
				timer_irq_handler();

			break;
		case MACHINE_EXT_IRQ:
			if (external_irq_handler)
				external_irq_handler();

			break;
		default:
			printf("irq not implement, mcause: 0x%x\n",
				mcause | MCAUSE_IRQ);
		}
	} else {
		//printf("TRAP Exception: pc:%p cuase: %x\n", mepc, mcause);
		if (mcause == STORE_ACCESS_FAULT)
			mepc += 4;
	}

	return mepc;
}

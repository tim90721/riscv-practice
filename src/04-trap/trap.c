#include <stdio.h>
#include "regs.h"

#include "riscv.h"
#include "trap.h"
#include "types.h"

#define MCAUSE_IRQ		BIT(31)

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
}

reg_t trap_handler(reg_t mepc, reg_t mcause)
{
	if (mcause & MCAUSE_IRQ) {
		printf("TRAP IRQ\n");
	} else {
		printf("TRAP Exception: %x\n", mcause);
		if (mcause == STORE_ACCESS_FAULT)
			mepc += 4;
	}

	return mepc;
}

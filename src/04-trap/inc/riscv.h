#ifndef _RISCV_H_
#define _RISCV_H_

#include "regs.h"
#include "types.h"

/* MIE */
#define MIE_SSIE		BIT(1)
#define MIE_MSIE		BIT(3)
#define MIE_STIE		BIT(5)
#define MIE_MTIE		BIT(7)
#define MIE_SEIE		BIT(9)
#define MIE_MEIE		BIT(11)

/* MSTATUS */
#define MSTATUS_MIE		BIT(3)

/* MCAUSE */
#define MCAUSE_IRQ		BIT(31)

static inline reg_t rhartid(void)
{
	reg_t x;

	__asm__ __volatile__("csrr %0, mhartid" : "=r" (x));

	return x;
}

static inline void w_mtvec(reg_t vector)
{
	__asm__ __volatile__("csrw mtvec, %0" : : "r" (vector));
}

static inline void w_mie(reg_t mie)
{
	__asm__ __volatile__("csrw mie, %0" : : "r" (mie));
}

static inline reg_t r_mie(void)
{
	reg_t mie;

	__asm__ __volatile__("csrr %0, mie" : "=r" (mie));

	return mie;
}

static inline void w_mstatus(reg_t mstatus)
{
	__asm__ __volatile__("csrw mstatus, %0" : : "r" (mstatus));
}

static inline reg_t r_mstatus(void)
{
	reg_t mstatus;

	__asm__ __volatile__("csrr %0, mstatus" : "=r" (mstatus));

	return mstatus;
}
#endif /* _RISCV_H_ */

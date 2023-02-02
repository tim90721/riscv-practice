#ifndef _RISCV_H_
#define _RISCV_H_

#include "types.h"

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

#ifndef _MMIO_H_
#define _MMIO_H_

#include "types.h"

static inline void mmio_write_8(uintptr addr, u8 val)
{
	*(volatile u8 *)addr = val;
}

static inline u8 mmio_read_8(uintptr addr)
{
	return *(volatile u8 *)addr;
}

static inline void mmio_write_16(uintptr addr, u16 val)
{
	*(volatile u16 *)addr = val;
}

static inline u16 mmio_read_16(uintptr addr)
{
	return *(volatile u16 *)addr;
}

static inline void mmio_setbits_32(uintptr addr, u32 set)
{
	*(volatile u32 *)addr |= set;
}

static inline void mmio_clrbits_32(uintptr addr, u32 clr)
{
	*(volatile u32 *)addr &= (~clr);
}

static inline void mmio_clrsetbits_32(uintptr addr, u32 clr, u32 set)
{
	*(volatile u32 *)addr &= (~clr);
	*(volatile u32 *)addr |= set;
}

static inline void mmio_write_32(uintptr addr, u32 val)
{
	*(volatile u32 *)addr = val;
}

static inline u32 mmio_read_32(uintptr addr)
{
	return *(volatile u32 *)addr;
}
#endif /* _MMIO_H_ */

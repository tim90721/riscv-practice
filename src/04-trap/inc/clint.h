#ifndef _CLINT_H_
#define _CLINT_H_

#define CLINT_MISP(hart)		(0x0 + (hart) * 0x4)
#define CLINT_MTIMECMP(hart)		(0x4000 + (hart) * 0x8)
#define CLINT_MTIME			(0xBFF8)
#endif /* _CLINT_H_ */

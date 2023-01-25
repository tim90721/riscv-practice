#ifndef _UART_H_
#define _UART_H_

#include "regs.h"

#include "platform.h"

#define RHR			(0)
#define THR			(0)
#define DLL			(0)
#define IER			(1)
#define DLM			(1)
#define FCR			(2)
#define ISR			(2)
#define LCR			(3)
#define MCR			(4)
#define LSR			(5)
#define MSR			(6)
#define SPR			(7)

/* IER */
#define RX_RDY_IRQ_EN		(BIT(0))
#define TX_RDY_IRQ_EN		(BIT(1))
#define RX_LINE_STA_IRQ_EN	(BIT(2))
#define TX_LINE_STA_IRQ_EN	(BIT(3))

/* LCR */
#define DLEN_MASK		(0x3)
#define DLEN_SHFT		(0)
#define STOP_LEN_MASK		(0x1)
#define STOP_LEN_SHFT		(2)
#define PARITY_EN		(BIT(3))
#define PARITY_EVEN_EN		(BIT(4))
#define PARITY_AO		(BIT(5))
#define BREAK_EN		(BIT(6))
#define BAUD_CTRL_EN		(BIT(7))

/* LSR */
#define RX_RDY			(BIT(0))
#define TX_IDLE			(BIT(5))

int uart_init(void);
int uart_puts(char *s);
#endif /* _UART_H_ */

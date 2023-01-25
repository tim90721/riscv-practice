#include "mmio.h"
#include "uart.h"
#include "types.h"

static inline void uart_write(u8 addr, u8 val)
{
	mmio_write_8(UART_BASE + addr, val);
}

static inline u8 uart_read(u8 addr)
{
	return mmio_read_8(UART_BASE + addr);
}

void uart_putc(char c)
{
	while (!(uart_read(LSR) & TX_IDLE))
		;

	uart_write(THR, c);
}

int uart_puts(char *s)
{
	int cnt;

	while (*s) {
		uart_putc(*s++);
		cnt++;
	}

	return cnt;
}

int uart_init(void)
{
	u8 lcr;

	/* disable all irq */
	uart_write(IER, 0);

	/* setup baud rate */
	lcr = uart_read(LCR);
	uart_write(LCR, lcr | BAUD_CTRL_EN);
	uart_write(DLL, 0x3);
	uart_write(DLM, 0);

	/* setup data configuration */
	/*
	 * data length = 8,
	 * stop bit length = 1,
	 * no parity,
	 * no break
	 */
	uart_write(LCR, (0x3 & DLEN_MASK) << DLEN_SHFT);

	return 0;
}

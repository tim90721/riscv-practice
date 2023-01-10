#include "uart.h"

int start_kernel(void)
{
	uart_init();

	uart_puts("hello\n");

	while (1)
		;

	return 0;
}

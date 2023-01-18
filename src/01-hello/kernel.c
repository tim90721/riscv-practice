#include <stdio.h>

#include "uart.h"

int start_kernel(void)
{
	int i = 10;

	uart_init();

	printf("hello world: %s\n", "test");
	printf("hello world: %c\n", 'o');
	printf("hello world: %d\n", i);
	printf("hello world: %p\n", &i);
	printf("hello world: %%\n");

	while (1)
		;

	return 0;
}

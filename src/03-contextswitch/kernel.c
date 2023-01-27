#include <stdio.h>

#include "sched.h"
#include "task.h"
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

	sched_init();

	while (1)
		;

	/* should never reach here */
	return 0;
}

#include <stdio.h>

#include "sched.h"
#include "task.h"
#include "uart.h"

struct task_struct test_task[2];

void test_task_func(void *param)
{
	u32 idx = (u32)param;

	printf("test task %d created!\n", idx);

	while (1) {
		u32 i = 5000000;

		printf("test task %d executing\n", idx);
		while (i--)
			;

		schedule();
	}

	printf("test task %d unexpected\n", idx);
}

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

	task_create(&test_task[0], test_task_func, (void *)1);
	task_create(&test_task[1], test_task_func, (void *)2);

	schedule();

	printf("unexpected\n");

	while (1)
		;

	/* should never reach here */
	return 0;
}

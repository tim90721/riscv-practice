#include <stdio.h>

#include "riscv.h"

#include "plic.h"
#include "sched.h"
#include "task.h"
#include "timer.h"
#include "trap.h"
#include "uart.h"

struct task_struct test_task;
struct task_struct init_task;

void init_task_func(void *param)
{
	trap_init();

	plic_init();

	timer_init();

	uart_init();

	while (1) {
		mdelay(2000);

		printf("init task run\n");
	}
}

void test_task_func(void *param)
{
	printf("test task created!\n");

	/* intentional generate an exception */
	*(int *)0x00000000 = 0x1;

	while (1) {
		printf("test task executing\n");

		mdelay(5000);
	}

	printf("test task unexpected\n");
}

int start_kernel(void)
{
	int i = 10;

	/* simple printf test... */
	printf("hello world: %s\n", "test");
	printf("hello world: %c\n", 'o');
	printf("hello world: %d\n", i);
	printf("hello world: %p\n", &i);
	printf("hello world: %%\n");

	sched_init();

	task_create(&init_task, init_task_func, NULL);
	task_create(&test_task, test_task_func, NULL);

	schedule();

	while (1) {
		wfi();

		if (sched_has_task_woken()) {
			printf("idle task run\n");

			schedule();
		}
	}

	/* should never reach here */
	return 0;
}

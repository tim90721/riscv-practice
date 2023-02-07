#include "irq.h"
#include "list.h"
#include "riscv.h"
#include "sched.h"
#include "task.h"
#include "timer.h"
#include "types.h"

extern void context_switch(struct context *c);

static struct context idle_context;
static struct task_struct *current;
static LIST_NODE(task_head);
static LIST_NODE(idle_head);
static u8 task_has_woken;

void task_create(struct task_struct *task, void (*func)(void *param), void *param)
{
	task->c.ra = (reg_t)func;
	task->c.sp = (reg_t)&task->stack[STACK_SIZE - 1];
	task->c.a0 = (reg_t)param;
	list_node_init(&task->node);

	list_add_tail(&task->node, &task_head);
}

void sched_init(void)
{
	__asm__ __volatile__("csrw mscratch, %0" : : "r" (&idle_context));
}

void schedule(void)
{
	if (current) {
		list_del(&current->node);
		list_add_tail(&current->node, &task_head);
	}

	if (!list_empty(&task_head)) {
		current = list_first_entry(&task_head, struct task_struct, node);

		disable_irq();
		task_has_woken = 0;
		enable_irq();

		context_switch(&current->c);
	} else {
		current = NULL;

		/* switch to idle task if there is no running task */
		context_switch(&idle_context);
	}
}

void sched_wakeup_task(u32 tick)
{
	struct task_struct *task, *tmp;

	list_for_each_entry_safe(task, tmp, &idle_head, node) {
		if (tick >= task->wakeup_tick) {
			list_del(&task->node);
			list_add_tail(&task->node, &task_head);
			task_has_woken = 1;
		}
	}
}

u8 sched_has_task_woken(void)
{
	return task_has_woken;
}

void mdelay(u32 ms)
{
	current->wakeup_tick = timer_get_tick() + ms;

	disable_irq();

	list_del(&current->node);

	list_add_tail(&current->node, &idle_head);

	enable_irq();

	current = NULL;

	schedule();
}

#include "list.h"
#include "sched.h"
#include "task.h"
#include "types.h"

extern void context_switch(struct context *c);

static struct task_struct *current;
static LIST_NODE(task_head);

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
	__asm__ __volatile__("csrw mscratch, 0");
}

void schedule(void)
{
	if (current) {
		list_del(&current->node);
		list_add_tail(&current->node, &task_head);
	}

	current = list_first_entry(&task_head, struct task_struct, node);

	context_switch(&current->c);
}

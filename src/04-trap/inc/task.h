#ifndef _TASK_H_
#define _TASK_H_

#include "list.h"
#include "types.h"

#define STACK_SIZE		1024

struct context {
	reg_t ra;
	reg_t sp;
	reg_t gp;
	reg_t tp;
	reg_t t0;
	reg_t t1;
	reg_t t2;
	reg_t s0;
	reg_t s1;
	reg_t a0;
	reg_t a1;
	reg_t a2;
	reg_t a3;
	reg_t a4;
	reg_t a5;
	reg_t a6;
	reg_t a7;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
	reg_t t3;
	reg_t t4;
	reg_t t5;
	reg_t t6;
};

struct task_struct {
	struct context c;
	struct list node;
	u32 wakeup_tick;
	/* should add memory management function to dynamically allocate */
	u8 stack[STACK_SIZE];
};

void task_create(struct task_struct *task, void (*func)(void *param), void *param);
#endif /* _TASK_H_ */

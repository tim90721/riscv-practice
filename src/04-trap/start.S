#include "platform.h"

	.equ	STACK_SIZE, 1024

	.text
	.section	.init, "ax"
	.global		_start

_start:
	csrr	t0, mhartid		# read hart id to t0
	bnez	t0, _park		# if not hart 0, go to wfi

bss_init:
	la	t1, __bss_start
	la	t2, __bss_end

	/* clear 1 byte */
	andi	t3, t2, 0x1
	beqz	t3, 1f

	addi	t2, t2, -1
	sb	zero, (t2)

1:
	/* clear half word */
	andi	t3, t2, 0x2
	beqz	t3, 1f

	addi	t2, t2, -2
	sh	zero, (t2)

1:
	/* nothing to do if start == end */
	beq	t1, t2, 2f

1:
	/* continously clear 1 word until start == end */
	sw	zero, (t1)
	addi	t1, t1, 4
	bne	t1, t2, 1b

2:
	slli	t0, t0, 10		# t0 = t0 * 1024 (STACK_SIZE)
	la	sp, stacks + STACK_SIZE	# setup initial stack pointer
	add	sp, sp, t0		# load current hart's sp to its own space

	j	start_kernel		# jump to start kernel

	j _stop

_park:
	wfi
	j _park

_stop:
	j _stop

stacks:
	.skip	STACK_SIZE * 8

	.end

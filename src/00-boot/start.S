#include "platform.h"

	.equ	STACK_SIZE, 1024

	.text
	.global	_start

_start:
	csrr	t0, mhartid		# read hart id to t0
	bnez	t0, _park		# if not hart 0, go to wfi

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

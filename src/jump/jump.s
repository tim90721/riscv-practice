
	.text
	.global _start

_start:
	la sp, _stack_end
	addi sp, sp, -4
	li a0, 3
	li a1, 4
	li s0, 5
	li s1, 6
	li t0, 7

	sw t0, 0(sp)

	call add

	lw t0, 0(sp)

	call _func1
	jal _func2
	call _func3
	j _stop

add:
	addi sp, sp, -8
	sw s0, 0(sp)
	sw s1, 4(sp)

	li t0, 10
	add a0, a0, a1
	add a0, a0, t0

	lw s1, 4(sp)
	lw s0, 0(sp)
	addi sp, sp, 8
	ret

_func1:
	li t0, 1
	ret

_func2:
	li t0, 2
	ret

_func3:
	li t0, 3
	ret

_stop:
	j _stop

_stack_start:
	.rept 12
	.word 0
	.endr
_stack_end:

	.end

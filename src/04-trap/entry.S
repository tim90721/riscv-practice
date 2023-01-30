# when saving context, we save all the cpu registers except t6
# since at this time, t6 is holding previous context saving address
# t6 needs to handle individually
.macro reg_save base
	sw		ra, 0(\base)
	sw		sp, 4(\base)
	sw		gp, 8(\base)
	sw		tp, 12(\base)
	sw		t0, 16(\base)
	sw		t1, 20(\base)
	sw		t2, 24(\base)
	sw		s0, 28(\base)
	sw		s1, 32(\base)
	sw		a0, 36(\base)
	sw		a1, 40(\base)
	sw		a2, 44(\base)
	sw		a3, 48(\base)
	sw		a4, 52(\base)
	sw		a5, 56(\base)
	sw		a6, 60(\base)
	sw		a7, 64(\base)
	sw		s2, 68(\base)
	sw		s3, 72(\base)
	sw		s4, 76(\base)
	sw		s5, 80(\base)
	sw		s6, 84(\base)
	sw		s7, 88(\base)
	sw		s8, 92(\base)
	sw		s9, 96(\base)
	sw		s10, 100(\base)
	sw		s11, 104(\base)
	sw		t3, 108(\base)
	sw		t4, 112(\base)
	sw		t5, 116(\base)
.endm

# when restoring the context, we can simply restore all the cpu register directly
# since t6 is the last cpu register and we are going to jump back to next task
.macro reg_restore base
	lw		ra, 0(\base)
	lw		sp, 4(\base)
	lw		gp, 8(\base)
	lw		tp, 12(\base)
	lw		t0, 16(\base)
	lw		t1, 20(\base)
	lw		t2, 24(\base)
	lw		s0, 28(\base)
	lw		s1, 32(\base)
	lw		a0, 36(\base)
	lw		a1, 40(\base)
	lw		a2, 44(\base)
	lw		a3, 48(\base)
	lw		a4, 52(\base)
	lw		a5, 56(\base)
	lw		a6, 60(\base)
	lw		a7, 64(\base)
	lw		s2, 68(\base)
	lw		s3, 72(\base)
	lw		s4, 76(\base)
	lw		s5, 80(\base)
	lw		s6, 84(\base)
	lw		s7, 88(\base)
	lw		s8, 92(\base)
	lw		s9, 96(\base)
	lw		s10, 100(\base)
	lw		s11, 104(\base)
	lw		t3, 108(\base)
	lw		t4, 112(\base)
	lw		t5, 116(\base)
	lw		t6, 120(\base)
.endm

	.text
	.global trap_vector
	.align 4

trap_vector:
	# retrieve and save interrupted task's context
	csrrw		t6, mscratch, t6
	reg_save	t6

	# save interrupted task's t6
	mv		t5, t6
	csrr		t6, mscratch
	sw		t6, 120(t5)

	# save interrupted context back for restore later
	csrw		mscratch, t5

	# get the cause and of trap
	csrr		a0, mepc
	csrr		a1, mcause

	# call C environment trap handler
	call		trap_handler

	# update return address if needed
	csrw		mepc, a0

	# restore interrupted task
	csrr		t6, mscratch
	reg_restore	t6

	mret

	.text
	.global context_switch
	.align 4

context_switch:
	# retrieve previous context saving address to t6
	# save t6 to mscratch temporarily
	csrrw		t6, mscratch, t6
	# when t6 is NULL, it means that this is the first time to do context switch
	# for this circumstance, we do not need to save the previous context
	# since there is no previous context
	beqz		t6, 1f
	# save all cpu registers except t6 since t6 is holding previous context's
	# saving address
	reg_save	t6

	# right now, t5 is previous context's saving address
	mv		t5, t6
	# retrieve previous context's t6
	csrr		t6, mscratch
	# save t6
	sw		t6, 120(t5)

1:
	# a0 must hold next context saving address
	# we write a0 to mscratch to give a hint for the next context switch
	# that where is previous context's saving address
	csrw		mscratch, a0

	mv		t6, a0
	reg_restore	t6

	ret

	.end

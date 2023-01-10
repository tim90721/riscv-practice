
	.text
	.global _start

_start:
	li x1, 0x11
	li x2, 0x1F
	and x1, x1, x2

_stop:
	j _stop

	.end

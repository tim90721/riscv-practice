
	.text
	.global _start

_start:
	la x1, _stop
	auipc x1, 0x10

_stop:
	j _stop

	.end

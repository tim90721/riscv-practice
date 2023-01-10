
	.text
	.global _start

_start:
	# normal load immediate value
	li x1, 0x100
	# load large value (>2048)
	li x1, 0x12345001
	# load large value with lsb 12 bits' msb equals to 1
	li x1, 0x12345fff

stop:
	j stop

	.end

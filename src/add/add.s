
	.text
	.global _start

_start:
add_postive:
	li x1, 5
	li x2, 6
	add x3, x2, x1

add_negative:
	li x1, -1
	li x2, -2
	add x3, x2, x1

_addi:
	li x1, 10
	addi x1, x1, 0x666

neg:
	li x1, 10
	neg x1, x1	# sub x1, 0, x1

mv:
	li x5, 11
	mv x6, x5

stop:
	j stop

	.end

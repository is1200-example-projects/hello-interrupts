.macro movi reg, val
	lui \reg, %hi(\val)
	ori \reg, \reg, %lo(\val)
.endm



.align 4
.global _isr_test
_isr_test:
	lw $k0, _isr_test
	jr $k0
	nop
	eret
	nop

.global _make_syscall
_make_syscall:
	movi $v0, PORTE
	addi $v1, $0, 4
	sw $v1, ($v0)
	syscall
	nop
	movi $v0, PORTE
	addi $v1, $0, 2
	sw $v1, ($v0)
	jr $ra
	nop


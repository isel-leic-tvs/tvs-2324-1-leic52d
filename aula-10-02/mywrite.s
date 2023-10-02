.text

.global my_write


my_write:

	movq $1, %rax
	syscall
	ret

.end

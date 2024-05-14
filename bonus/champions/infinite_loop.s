	.name "Infinite loop"
	.comment "This champion does an infinite loop !"

	sti r1, %:hi, %1

hi:	live %234
	ld %1, r3
	zjmp %:hi

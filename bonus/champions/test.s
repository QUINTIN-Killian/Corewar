	.name "Test"
	.comment "This is a test file."

		add r1, r2, r3
		add r1, r2, r3
		add r1, r2, r3
		add r1, r2, r3
		add r1, r2, r3

		fork %:test
		zjmp %:test2

test:	add r1, r2, r3
		zjmp %:test

test2:	add r1, r2, r3
		zjmp %:test2

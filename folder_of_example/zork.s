.name "zork"
.comment "I'M ALIIIIVE"

	live %:label
	ldi 1, r2, r3
label:
	and 1, %:live, r13
live:
	live %1
l1:
	sti r1, %:live, %1

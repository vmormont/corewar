# this is a comment
; this is another comment

.name "zork" ;another one

# yes it's comment
.comment"I'M ALIIIIVE"	#another two

	live %1
l1:
	sti r11, %:live, %1
label:
	and r1, %0, r13
live:
	live %1
	zjmp %:live

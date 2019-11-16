# this is a comment
; this is another comment

.name "zork" ;another one

# yes it's comment
.comment"I'M ALIIIIVE"	#another two

l2:
	sti r1, %:live, %1
label:
	and r1, %0, r1
live:
	live %1
	zjmp %:live

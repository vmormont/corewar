.name "zork"
.comment "I'M ALLLIIIVE"

l2:		sti r1,r99,%1
		and r1,%0,r1

live:   live %1
		zjmp %:live

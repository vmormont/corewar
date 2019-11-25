.name "zork"
.comment "I'M ALLLIIIVE"

		ld %-15, r2
l2:		sti r2,%:live,%1
		and r1,%0,r1

live:   live %1
		zjmp %:live

.name "crashman"
.comment "champ for experiments"

life:	live %0
		ld %-1, r5
		st r5, 200
		ld %0, r5
		zjmp %:life

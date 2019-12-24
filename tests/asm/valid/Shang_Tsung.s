.name "Shang Tsung"
.comment "Let the battle begin"

begin: st r1, 14
	ld 0, r5 
	fork %511
	live %1
	zjmp %-5

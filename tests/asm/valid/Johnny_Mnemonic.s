
# https://www.kinopoisk.ru/film/3800/

.name "Johnny Mnemonic"

.comment "The hottest data on earth. In the coolest head in town"

live:
	live %1
	zjmp %:live

add2r3:
	add r1, r2, r3
	ldi r1, %:live, r5

live:
	fork %:add2r3
	aff r3

	fork%:live
	or :add2r3, :live, r1

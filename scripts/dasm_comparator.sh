#!/bin/bash

MY_DASM="./dasm"
MY_ASM="./asm"

if [ -z "$1" ] ; then
	echo "Usage: dasm_comparator.sh dirname"
	exit 1
fi

if [ ! -f "$MY_DASM" ]; then
	echo "File $MY_DASM does not exist"
	exit 1
fi

if [ ! -f "$MY_ASM" ]; then
	echo "File $MY_ASM does not exist"
	exit 1
fi

GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[1;33m"
EOC="\e[0m"

for S_FILE in $( find ${1} -type f -name "*.s" ); do

	COR_1="${S_FILE%".s"}.cor"

	${MY_ASM} ${S_FILE} &>/dev/null
	if [[ -e ${COR_1} ]]; then
		cp ${COR_1} my_champ_1.cor
	fi

	S_FILE_2="${COR_1%".cor"}.s"
	${MY_DASM} my_champ_1.cor &>/dev/null
	if [[ -e ${S_FILE_2} ]]; then
		cp ${S_FILE_2} my_champ_2.s
	fi
	COR_2="my_champ_2.cor"
	${MY_ASM} my_champ_2.s &>/dev/null
	if [[ -e ${COR_2} ]]; then
		cp ${COR_2} champ_2.cor
	fi
	if [[ -e my_champ_1.cor ]] && [[ -e my_champ_2.cor ]]; then
		if diff my_champ_1.cor my_champ_2.cor &>/dev/null;
			then printf "${GREEN}OK${EOC}\t${COR}\n"
			else printf "${RED}KO${EOC}\t${COR}\n"
		fi
		rm my_champ_1.cor
		rm my_champ_2.cor
		rm my_champ_1.s
		rm my_champ_2.s

	elif [[ -e my_champ_1.cor ]]; then
		printf "${YELLOW}ERROR${EOC}\t(my_champ_1.cor was not created, but my_champ.s was) ${S_FILE}\n"
		rm my_champ_1.cor ;
	elif [[ -e my_champ_2.cor ]]; then
		printf "${YELLOW}ERROR${EOC}\t(my_champ_2.cor was not created, but my_champ.s was) ${S_FILE_2}\n"
		rm my_champ_2.cor
	else
		printf "${YELLOW}ERROR${EOC}\t(incorrect file) ${S_FILE}\n"
	fi
done

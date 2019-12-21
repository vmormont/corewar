#!/bin/bash

MY_ASM="./asm"
OG_ASM="folder_of_example/asm"

if [ -z "$1" ] ; then
	echo "Usage: asm_comparator.sh dirname"
	exit 1
fi

if [ ! -f "$MY_ASM" ]; then
	echo "File $MY_ASM does not exist"
	exit 1
fi

if [ ! -f "$OG_ASM" ]; then
	echo "File $OG_ASM does not exist"
	exit 1
fi

GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[1;33m"
EOC="\e[0m"

for S_FILE in $( find ${1} -type f -name "*.s" ) ; do
	${MY_ASM} -a ${S_FILE} &> my_out
	${OG_ASM} -a ${S_FILE} &> og_out
	if [[ -e my_out ]] && [[ -e og_out ]] ; then
		if diff my_out og_out &>/dev/null ;
			then printf "${GREEN}OK${EOC}\t${S_FILE}\n"
			else printf "${RED}KO${EOC}\t${S_FILE}\n"
		fi
		rm my_out
		rm og_out
	elif [[ -e my_out ]] ; then
		printf "${YELLOW}ERROR${EOC}\t(og_champ was not created, but my_champ was) ${S_FILE}\n"
		rm my_out ;
	elif [[ -e og_out ]] ; then
		printf "${YELLOW}ERROR${EOC}\t(my_champ was not created, but og_champ was) ${S_FILE}\n"
		rm og_out
	else
		printf "${YELLOW}ERROR${EOC}\t(incorrect file) ${S_FILE}\n"
	fi
done

#! /usr/bin/bash

#****COLORS****
LRED="\e[91m"
RED="\e[31m"
LGREEN="\e[92m"
LYELLOW="\e[93"
LMAGENTA="\e[95m"
LCYAN="\e[96m"
DEF_COLOR="\e[0;39m"
NC="\e[0;39m"

#*****INTRO*****
printf " \
			${RED}             XXXXXXX\n \
			${RED}        XXXXXXXXXXXXXXXXX\n \
			${RED}     XXXXXX    XXX    XXXXXX\n \
			${RED}   XXXX        XXX        XXXX\n \
			${RED}  XXX          XXX          XXX     \n \
			${RED} XXX  ${NC}ooo${RED}      XXX      ${NC}ooo${RED}  XXX\n \
			${RED}XXX  ${NC}oooooo  ${RED}  XXX  ${NC}  oooooo${RED}  XXX\n \
			${RED}XXX  ${NC}ooooooo  ${RED} XXX ${NC}  ooooooo${RED}  XXX\n \
			${RED}XXX    ${NC}oooooo${RED}  XXX  ${NC}oooooo${RED}    XXX\n \
			${RED} XXX     ${NC} ooo${RED}  XXX  ${NC}ooo ${RED}     XXX\n \
			${RED}  XXX          XXX          XXX\n \
			${RED}   XXXX        XXX        XXXX\n \
			${RED}     XXXXXX    XXX    XXXXXX\n \
			${RED}        XXXXXXXXXXXXXXXXXX\n \
			${RED}             XXXXXXX${NC}\n${NC}"
printf " \
			${LMAGENTA}  OOO    OO   O   O  O   O   OOO \n\
			${LMAGENTA}  O  O  O  O  OO  O  O   O  O    \n\
			${LMAGENTA}  OOO   O  O  O O O  O   O   OO  \n\
			${LMAGENTA}  O  O  O  O  O  OO  O   O     O \n\
			${LMAGENTA}  OOO    OO   O   O   OOO   OOO  \n\
			${NC}_________________________________\n"
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:14:49 by pcredibl          #+#    #+#              #
#    Updated: 2019/11/07 17:48:25 by pcredibl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM			:= asm
NAME_CORE			:= corewar

CC 					:= gcc
CFALGS				:= -g -Wall -Wextra -Werror

#LIBFT_DIRS
LIB_DIR			:= ./libft
LIBFT			:= libft.a

#PROJECT_DIRS
INC_DIR			:= ./include
OBJ_DIR			:= ./obj
SRC_DIR			:= ./src

LIBS			:= -L $(LIB_DIR) -libft
LFLAGS			:= -I $(LIB_DIR)/inc -I $(INC_DIR)

#HEADERS

SRC				:= asm.c

OBJ_DIR			:= $(SRC:.c=.o)

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)
vpath %.a $(LIB_DIR)

all: lib $(NAME_ASM)

$(NAME_ASM): lib $(OBJ)
#Добавить флаги CFLAGS
	$(CC) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ))$(LIBS) -o $@
	echo "DONE ✅"

$(OBJ):	%.o:%c
	$(CC) $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$@ was created"

lib:
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)
	echo "obj files was deleted"

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	rm 
	echo "libs was deleted"

re: fclean all 


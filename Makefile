# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:14:49 by pcredibl          #+#    #+#              #
#    Updated: 2019/11/13 16:54:14 by pcredibl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN 				:= \033[0;32m
RED 				:= \033[0;31m
RESET				:= \033[0m

NAME_ASM			:= asm
NAME_CORE			:= corewar

#HEADERS
ASM_HEADERS			:= asm.h op.h corewar_structs.h

#COMPILER
CC 					:= gcc

#LIBFT
LIB_DIR				:= ./libft
LIBFT				:= libft.a

#PROJECT_DIRS
INC_DIR				:= ./inc
OBJ_DIR				:= ./obj
SRC_DIR				:= ./src

#COMPILER FLAGS
CFALGS				:= -Wall -Wextra -Werror
LFLAGS				:= -I $(LIB_DIR)/inc -I $(INC_DIR)
LIBS				:= -L $(LIB_DIR) -lft

SRC					= asm.c ft_exit.c op_tab_func.c champion.c instructions.c\
					arguments.c labels.c lexical.c commands.c

OBJ					:= $(SRC:.c=.o)

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)
vpath %.a $(LIB_DIR)

all: lib $(NAME_ASM)

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(NAME_ASM): $(LIBFT) $(OBJ) $(ASM_HEADERS)
	$(CC) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ)) $(LIBS) -o $@
	echo "$(GREEN)DONE ✅$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(OBJ):%.o:%.c $(ASM_HEADERS) | $(OBJ_DIR)
	$(CC) -g $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

lib:
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)
	echo "$(RED)objs files was deleted$(RESET)"

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(NAME_ASM)
	echo "$(RED)$(LIBFT) was deleted$(RESET)"

re: fclean all

.SILENT: all clean fclean re $(NAME_ASM) $(OBJ) $(OBJ_DIR) lib

.PHONY: clean fclean re all

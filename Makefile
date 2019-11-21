# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:14:49 by pcredibl          #+#    #+#              #
#    Updated: 2019/11/21 16:24:58 by pcredibl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN 				:= \033[0;32m
RED 				:= \033[0;31m
RESET				:= \033[0m

NAME_ASM			:= asm
NAME_CORE			:= corewar

#HEADERS
ASM_HEADERS			:= asm.h op.h corewar_structs.h
CORE_HEADERS		:= core.h op.h corewar_structs.h

#COMPILER
CC 					:= gcc

#LIBFT
LIB_DIR				:= ./libft
LIBFT				:= libft.a

#PROJECT_DIRS
INC_DIR				:= ./inc
OBJ_DIR				:= ./obj
SRC_ASM_DIR			:= ./src/asm
SRC_CORE_DIR		:= ./src/vm

#COMPILER FLAGS
CFALGS				:= -Wall -Wextra -Werror
LFLAGS				:= -I $(LIB_DIR)/inc -I $(INC_DIR)
LIBS				:= -L $(LIB_DIR) -lft

SRC_ASM				:= asm.c ft_exit.c champion.c utility.c instructions_utility.c\
					label_utility.c parse_name_comment.c parse_label.c\
					asm_file_parser.c parse_arguments.c validation.c\
					error_manager.c assign_values.c assembly.c dump_to_stdo.c\
					options.c

SRC_CORE			:= vm.c utillity_core.c #read_cor_file.c

OBJ_ASM				:= $(SRC_ASM:.c=.o)
OBJ_CORE			:= $(SRC_CORE:.c=.o)

vpath %.c $(SRC_ASM_DIR) $(SRC_CORE_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)
vpath %.a $(LIB_DIR)

all: lib $(NAME_ASM) $(NAME_CORE)

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(NAME_ASM): $(LIBFT) $(OBJ_ASM) $(ASM_HEADERS)
	$(CC) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_ASM)) $(LIBS) -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(NAME_CORE): $(LIBFT) $(OBJ_CORE) $(CORE_HEADERS)
	$(CC) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_CORE)) $(LIBS) -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(OBJ_ASM):%.o:%.c $(ASM_HEADERS) | $(OBJ_DIR)
	$(CC) -g $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(OBJ_CORE):%.o:%.c $(CORE_HEADERS) | $(OBJ_DIR)
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

.SILENT: all clean fclean re $(NAME_ASM) $(OBJ_ASM) $(NAME_CORE) $(OBJ_CORE) $(OBJ_DIR) lib

.PHONY: clean fclean re all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astripeb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:14:49 by pcredibl          #+#    #+#              #
#    Updated: 2019/11/27 19:25:49 by astripeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN 				:= \033[0;32m
RED 				:= \033[0;31m
RESET				:= \033[0m

NAME_ASM			:= asm
NAME_CORE			:= corewar

#HEADERS
OP_HEADERS			:= op_struct.h op.h
ASM_HEADERS			:= asm_structs.h asm.h
CORE_HEADERS		:= corewar_structs.h corewar.h

#COMPILER
CC 					:= gcc

#LIBFT
LIB_DIR				:= ./libft
LIBFT				:= libft.a

#PROJECT_DIRS
INC_DIR				:= ./inc
OBJ_DIR				:= ./obj
SRC_OP_DIR			:= ./src/op
SRC_ASM_DIR			:= ./src/asm
SRC_CORE_DIR		:= ./src/vm

#COMPILER FLAGS
CFALGS				:= -Wall -Wextra -Werror
LFLAGS				:= -I $(LIB_DIR)/inc -I $(INC_DIR)
LIBS				:= -L $(LIB_DIR) -lft

SRC_OP				:= op_tab.c

SRC_ASM				:= asm.c ft_exit_asm.c champion.c utility.c instructions_utility.c\
					label_utility.c parse_name_comment.c parse_label.c\
					asm_file_parser.c parse_arguments.c validation.c\
					error_manager.c assign_values.c assembly.c dump_to_stdo.c\
					options.c

SRC_CORE			:= corewar.c ft_exit_corewar.c utility_core.c options_core.c\
					champion_read.c champion_utility.c champion_funcs.c\
					vm_utillity.c cursor.c cycles.c op1.c copy_read.c op_utility.c\
					live_zjmp_aff.c add_sub.c and_or_xor.c st_sti.c fork_lfork.c

OBJ_OP				:= $(SRC_OP:.c=.o)
OBJ_ASM				:= $(SRC_ASM:.c=.o)
OBJ_CORE			:= $(SRC_CORE:.c=.o)

vpath %.c $(SRC_ASM_DIR) $(SRC_CORE_DIR) $(SRC_OP_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)
vpath %.a $(LIB_DIR)

all: lib $(NAME_ASM) $(NAME_CORE)

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(NAME_ASM): $(LIBFT) $(OBJ_ASM) $(OBJ_OP) $(ASM_HEADERS) $(OP_HEADERS)
	$(CC) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_ASM) $(OBJ_OP)) $(LIBS) -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(NAME_CORE): $(LIBFT) $(OBJ_CORE) $(OBJ_OP) $(CORE_HEADERS) $(OP_HEADERS)
	$(CC) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_CORE) $(OBJ_OP)) $(LIBS) -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(OBJ_ASM):%.o:%.c $(ASM_HEADERS) $(OP_HEADERS) | $(OBJ_DIR)
	$(CC) -g $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(OBJ_CORE):%.o:%.c $(CORE_HEADERS) $(OP_HEADERS) | $(OBJ_DIR)
	$(CC) -g $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

#BEFORE COMPLETE PROJECT ADD $(CFLAGS)
$(OBJ_OP):%.o:%.c $(OP_HEADERS) | $(OBJ_DIR)
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
	echo "$(RED)$(LIBFT) was deleted$(RESET)"
	rm -rf $(NAME_ASM) $(NAME_CORE)
	echo "$(RED)$(NAME_ASM) was deleted$(RESET)"
	rm -rf $(NAME_CORE)
	echo "$(RED)$(NAME_CORE) was deleted$(RESET)"

re: fclean all

.SILENT: all clean fclean re $(NAME_ASM) $(OBJ_ASM) $(NAME_CORE) \
		$(OBJ_CORE) $(OBJ_DIR) $(OBJ_OP) lib

.PHONY: clean fclean re all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:14:49 by pcredibl          #+#    #+#              #
#    Updated: 2019/12/24 18:14:18 by pcredibl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN 				:= \033[0;32m
RED 				:= \033[0;31m
RESET				:= \033[0m

NAME_ASM			:= asm
NAME_CORE			:= corewar
NAME_DASM			:= dasm

#HEADERS
OP_HEADERS			:= op_struct.h op.h
ASM_HEADERS			:= asm_structs.h asm.h
DASM_HEADERS		:= dasm.h
CORE_HEADERS		:= corewar_structs.h corewar.h visual.h

#COMPILER
CC 					:= gcc

#LIBFT
LIB_DIR				:= ./libft
LIBFT				:= libft.a

#PROJECT_DIRS
INC_DIR				:= ./inc
OBJ_DIR				:= ./obj
SRC_OP_INFO_DIR		:= ./src/op_info
SRC_ASM_DIR			:= ./src/asm
SRC_CORE_DIR		:= ./src/vm
SRC_OP_FUNC_DIR		:= ./src/vm/op_funcs
SRC_VIS_DIR			:= ./src/vm/visual
SRC_DASM_DIR		:= ./src/dasm

#COMPILER FLAGS
CFALGS				:= -Wall -Wextra -Werror -g -O3
LFLAGS				:= -I $(LIB_DIR)/inc -I $(INC_DIR)
LIBS				:= -L $(LIB_DIR) -lft

SRC_OP_INFO			:= op_tab.c

################################################################################
#									ASSEMBLY FILES					 		   #
################################################################################

SRC_ASM				:= asm.c ft_exit_asm.c champion.c utility.c\
					instructions_utility.c label_utility.c parse_name_comment.c\
					parse_label.c asm_file_parser.c parse_arguments.c\
					validation.c error_manager.c assign_values.c assembly.c\
					dump_to_stdout.c options.c

################################################################################
#									COREWAR FILES					 		   #
################################################################################

SRC_CORE			:= corewar.c ft_exit_corewar.c utility_core.c options_core.c\
					champion_read.c champion_utility.c champion_funcs.c\
					vm_utillity.c cursor.c cycles.c check_args.c check_cursors.c

SRC_OP_FUNC			:= ld_lld.c ldi_lldi.c live_zjmp_aff.c add_sub.c\
					and_or_xor.c st_sti.c fork_lfork.c op_utility.c

SRC_VIS				:= vis_init.c vis_utility.c vis_champs.c vis_cursor.c\
					vis_cycle.c vis_attributes.c vis_sound.c easter_egg.c

################################################################################
#									DISASSEMBLY FILES				 		   #
################################################################################

SRC_DASM			:= main.c dasm.c utilits.c utilits_second.c\
					print.c

OBJ_OP				:= $(SRC_OP_INFO:.c=.o)
OBJ_ASM				:= $(SRC_ASM:.c=.o)
OBJ_CORE			:= $(SRC_CORE:.c=.o) $(SRC_OP_FUNC:.c=.o) $(SRC_VIS:.c=.o)
OBJ_DASM			:= $(SRC_DASM:.c=.o)

vpath %.c $(SRC_OP_INFO_DIR)\
		$(SRC_ASM_DIR)\
		$(SRC_CORE_DIR) $(SRC_OP_FUNC_DIR) $(SRC_VIS_DIR)\
		$(SRC_DASM_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)
vpath %.a $(LIB_DIR)

all: lib $(NAME_ASM) $(NAME_CORE) $(NAME_DASM)

$(NAME_ASM): $(LIBFT) $(OBJ_ASM) $(OBJ_OP) $(ASM_HEADERS) $(OP_HEADERS)
	$(CC) $(CFALGS) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_ASM) $(OBJ_OP)) $(LIBS) -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

$(NAME_CORE): $(LIBFT) $(OBJ_CORE) $(OBJ_OP) $(CORE_HEADERS) $(OP_HEADERS)
	$(CC) $(CFALGS) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_CORE) $(OBJ_OP)) $(LIBS) -lncurses -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

$(NAME_DASM): $(LIBFT) $(OBJ_DASM) $(OBJ_OP) $(DASM_HEADERS) $(OP_HEADERS)
	$(CC) $(CFALGS) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_DASM) $(OBJ_OP)) $(LIBS) -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

$(OBJ_ASM):%.o:%.c $(ASM_HEADERS) $(OP_HEADERS) | $(OBJ_DIR)
	$(CC) $(CFALGS) $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

$(OBJ_CORE):%.o:%.c $(CORE_HEADERS) $(OP_HEADERS) | $(OBJ_DIR)
	$(CC) $(CFALGS) $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

$(OBJ_OP):%.o:%.c $(OP_HEADERS) | $(OBJ_DIR)
	$(CC) $(CFALGS) $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

$(OBJ_DASM):%.o:%.c $(DASM_HEADERS) | $(OBJ_DIR)
	$(CC) $(CFALGS) $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
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
	rm -rf $(NAME_DASM)
	echo "$(RED)$(NAME_DASM) was deleted$(RESET)"

re: fclean all

.SILENT: all clean fclean re $(NAME_ASM) $(OBJ_ASM) $(NAME_CORE) \
		$(OBJ_CORE) $(NAME_DASM) $(OBJ_DASM) $(OBJ_DIR) $(OBJ_OP) lib

.PHONY: clean fclean re all

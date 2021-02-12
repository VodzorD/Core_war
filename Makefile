# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wscallop <wscallop@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 17:29:26 by wscallop          #+#    #+#              #
#    Updated: 2021/02/12 21:07:02 by wscallop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
ASM_COMPIL = asm

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBRARIES = -lft -L $(LIBFT_DIRECTORY)
INCLUDES = -I $(HEADERS_DIRECTORY) -I $(LIBFT_HEADERS) -I ./libft/core/includes -I ./libft/collections/includes -I ./libft/string/includes -I ./libft/getopt/includes -I ./libft/printf/includes -I ./includes/asm/

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes

HEADERS_LIST = corewar.h op.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = 	champ_validation.c \
				crw_dying_process.c \
				crw_execute.c \
				crw_init_game.c \
				crw_utils.c \
				cursor.c \
				cursor_utils.c \
				main.c \
				op_add.c \
				op_aff.c \
				op_and.c \
				op_arg_handlers.c \
				op_args_validation.c \
				op_fork.c \
				op_ld.c \
				op_ldi.c \
				op_lfork.c \
				op_live.c \
				op_lld.c \
				op_lldi.c \
				op_or.c \
				op_st.c \
				op_sti.c \
				op_sub.c \
				op_xor.c \
				op_zjmp.c \
				parse_args.c \
				player.c \
				print.c \
				utils.c

SOURCES_DIRECTORY_ASM = ./sources/asm/
SOURCES_ASM_LIST = 	count_bytes_for_command.c \
					count_bytes_for_command2.c \
					ft_find_command.c \
					ft_init_label.c \
					ft_parse.c \
					ft_print_command.c \
					ft_read.c \
					ft_second_read.c \
					main.c \
					utilits.c

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

OBJECTS_ASM_DIRECTORY = objects/asm/
OBJECTS_ASM_LIST = $(patsubst %.c, %.o, $(SOURCES_ASM_LIST))
OBJECTS_ASM	= $(addprefix $(OBJECTS_ASM_DIRECTORY), $(OBJECTS_ASM_LIST))
DPN         = $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.d))

.PHONY: all clean fclean re

all: $(NAME)

-include $(DPN)

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS) $(ASM_COMPIL)
	@$(CC) -o $(NAME) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS)

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@echo "\033[32m [OK] \033[0m\033[32mCompiling:\033[36m " $@

$(ASM_COMPIL) : $(LIBFT) $(OBJECTS_ASM_DIRECTORY) $(OBJECTS_ASM)
	@$(CC) -o $(ASM_COMPIL) $(FLAGS) $(LIBRARIES) -I ./includes/asm $(OBJECTS_ASM)

$(OBJECTS_ASM_DIRECTORY):
	@mkdir -p $(OBJECTS_ASM_DIRECTORY)

$(OBJECTS_ASM_DIRECTORY)%.o : $(SOURCES_DIRECTORY_ASM)%.c includes/asm/asm.h
	@$(CC) $(FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@echo "\033[32m [OK] \033[0m\033[32mCompiling:\033[36m " $@

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(ASM_COMPIL)
	rm -f $(NAME)

re: fclean all

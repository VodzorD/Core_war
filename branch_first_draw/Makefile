NAME		= corewar
LIBNAME		= libft.a

GCC			= /usr/bin/clang
WOPT		= -Wall -Wextra -Werror
OOPT		= -g
IOPT		= -I $(INCDIR)

AR			= /usr/bin/ar -rc
MAKE		= /usr/bin/make -C
RANLIB		= /usr/bin/ranlib
MKDIR		= /bin/mkdir -p
RM			= /bin/rm -rf
ZSH			= /bin/zsh

LIBDIR		= libft
SRCDIR		= sources
OBJDIR		= objects
INCDIR		= includes
DPNDIR		= depends

SRCNAME		= crw_dying_process.c \
                             crw_execute.c \
                             crw_init_game.c \
                             cursor.c \
                             cursor_utils.c \
                             champ_validation.c \
                             main.c \
                             op_args_validation.c \
                             player.c \
                             op/op_add.c \
                             op/op_aff.c \
                             op/op_and.c \
                             op/op_fork.c \
                             op/op_ld.c \
                             op/op_ldi.c \
                             op/op_lfork.c \
                             op/op_live.c \
                             op/op_lld.c \
                             op/op_lldi.c \
                             op/op_or.c \
                             op/op_st.c \
                             op/op_sti.c \
                             op/op_sub.c \
                             op/op_xor.c \
                             op/op_zjmp.c \
                             op/utils.c

SRC			= $(addprefix $(SRCDIR)/, $(SRCNAME))
OBJ			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.o))
DPN			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.d))
LFT			= $(addprefix $(LIBDIR)/, $(LIBNAME))
LFTOBJ		= $(LIBDIR)/objects/*.o


CLEAR       = "\033[K"
EOC			= "\033[0;0m"
GREEN		= "\033[32m"
TURQUOISE   = "\033[36m"
CR			= "\r"$(CLEAR)

all: $(LFT) $(NAME)

-include $(DPN)

$(NAME): $(LFT) $(OBJ)
	@$(GCC) $(WOPT) $(OOPT) $(IOPT) $(OBJ) -o $(NAME) -L $(LIBDIR) -lft
	@echo "\n"
	@echo "\033[32m [OK] \033[0m\033[32mExecution file:\033[36m" $(NAME)
	@echo $(EOC)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	@$(MKDIR) $(OBJDIR)/op
	echo $(SRC)
	@$(GCC) $(WOPT) $(OOPT) -MMD -MP -c $< -o $@
	@echo "\033[32m [OK] \033[0m\033[32mCompiling:\033[36m " $@

$(LFT):
	@$(MAKE) $(LIBDIR)

clean:
	@$(RM) $(OBJ) $(OBJDIR)
	@$(MAKE) $(LIBDIR) clean
	@echo "\033[31m [OK] \033[0m\033[31mDeleting catalog and binaries:\033[33m " $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) $(LIBDIR) fclean
	@echo "\033[31m [OK] \033[0m\033[31mDeleting execution file:\033[33m " $(NAME)
	@echo $(EOC)

re: fclean all

.PHONY: all clean fclean re norm

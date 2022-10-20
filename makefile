#****VARIABLES****
NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -rf
LIBFT = libft.a
D_LIBFT = includes/libft/
D_SRC = src/
D_SRC_BONUS = src_bonus/
D_OBJ = obj/
D_OBJ_BONUS = obj_bonus/
OBJS = $(patsubst $(D_SRC)%.c,$(D_OBJ)%.o,$(SRCS))
OBJS_BONUS = $(patsubst $(D_SRC_BONUS)%.c,$(D_OBJ_BONUS)%.o,$(SRCS_BONUS))

OK_STRING = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING = "[WARNING]"
COMP_STRING = "Compiling"


#****COLORS****
LRED = \033[91m
LGREEN = \033[92m
LYELLOW = \033[93
LMAGENTA = \033[95m
LCYAN = \033[96m
DEF_COLOR = \033[0;39m

#****MAKEUP RULE****
define run_and_test
printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $@" "$(LRED)$(ERROR_STRING)$(DEF_COLOR)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $@" "$(LYELLOW)$(WARN_STRING)$(DEF_COLOR)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)" "$(LGREEN)$(OK_STRING)$(DEF_COLOR)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

#****SOURCES****
SRCS = src/pipex.c \
		src/pipex_utils.c \
		src/pipex_prog.c \
		src/pipex_io.c \
		src/pipex_init.c

#HEADER = pipex.h

SRCS_BONUS = src_bonus/pipex_bonus.c \
			src_bonus/pipex_utils_bonus.c \
			src_bonus/pipex_prog_bonus.c \
			src_bonus/pipex_io_bonus.c \
			src_bonus/pipex_hd_bonus.c

#.c.o :
#	@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

#$(V).SILENT:

all:	$(D_LIBFT)/$(LIBFT) $(NAME)

$(NAME):	$(OBJS) $(D_LIBFT)/$(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(D_LIBFT)$(LIBFT)
	@printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"
	@echo "$(LGREEN)Software Compilation completed !$(DEF_COLOR)"

$(OBJS): $(D_OBJ)%.o : $(D_SRC)%.c
		@mkdir -p $(D_OBJ)
		@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

$(D_LIBFT)/$(LIBFT):
	@$(MAKE) -C $(D_LIBFT)

$(NAME_BONUS): $(OBJS_BONUS) $(D_LIBFT)/$(LIBFT)
	@$(CC) $(CFLAGS) -o $(OBJS_BONUS) $(D_LIBFT)$(LIBFT)
	@printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"
	@echo "$(LGREEN)Software Compilation completed !$(DEF_COLOR)"

$(OBJ_BONUS): $(D_OBJ_BONUS)%.o : $(D_SRC_BONUS)%.c
		@mkdir -p $(D_OBJ_BONUS)
		@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

bonus: $(D_LIBFT)/$(LIBFT) $(NAME_BONUS)

#tests:	

#btests : bonus
	
clean:
	$(RM) $(D_OBJ)
	$(RM) $(D_OBJ_BONUS)
	$(MAKE) -C $(D_LIBFT) clean
	@echo "$(LCYAN)Objects files cleaned !$(DEF_COLOR)"

fclean:	clean
	$(MAKE) -C $(D_LIBFT) fclean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	@echo "$(LCYAN)Executables files cleaned !$(DEF_COLOR)"

re:	fclean all

.PHONY: all clean fclean re
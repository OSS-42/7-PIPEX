#****VARIABLES****
NAME = pipex
NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -rf
LIBFT = libft.a
HEADER = includes/pipex.h
D_LIBFT = libft/
D_SRC = src/
D_OBJ = obj/
OBJS = $(patsubst $(D_SRC)%.c,$(D_OBJ)%.o,$(SRCS))
D_INTRO = pretty/
HEADER_BONUS = includes/pipex_bonus.h
D_SRC_BONUS = src_bonus/
D_OBJ_BONUS = obj_bonus/
OBJS_BONUS = $(patsubst $(D_SRC_BONUS)%.c,$(D_OBJ_BONUS)%.o,$(SRCS_BONUS))

OK_STRING = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING = "[WARNING]"
COMP_STRING = "Generating"
CLEAN_STRING = "Cleaning"

NO_OF_FILES := $(words $(wildcard $(D_SRC)*.c))

#****COLORS****
LRED = \033[91m
LGREEN = \033[92m
LYELLOW = \033[93
LMAGENTA = \033[95m
LCYAN = \033[96m
DEF_COLOR = \033[0;39m

#*****INTRO*****
define intro_mandatory
@bash $(D_INTRO)intro.sh
endef

define intro_bonus
@bash $(D_INTRO)intro_bonus.sh
endef

#****MAKEUP RULE****
#****before emoji :
#printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)" "$(LGREEN)$(OK_STRING)$(DEF_COLOR)\n";
define run_and_test
printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $@" "💥$(DEF_COLOR)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $@" "⚠️$(DEF_COLOR)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)" "✅$(DEF_COLOR)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define cleaning
printf "%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Files$(DEF_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Files" "💥$(DEF_COLOR)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Files" "⚠️$(DEF_COLOR)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Files" "✅$(DEF_COLOR)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define fcleaning
printf "%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Files$(DEF_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Files" "💥$(DEF_COLOR)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Filess" "⚠️$(DEF_COLOR)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) PROJECT Executable Files" "✅$(DEF_COLOR)\n"; \
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

SRCS_BONUS = src_bonus/pipex_bonus.c \
			src_bonus/pipex_utils_bonus.c \
			src_bonus/pipex_prog_bonus.c \
			src_bonus/pipex_io_bonus.c \
			src_bonus/pipex_hd_bonus.c \
			src_bonus/get_next_line.c \
			src_bonus/get_next_line_utils.c

#$(V).SILENT:

all:	deadpool do_libft $(NAME)

deadpool:
	@$(call intro_mandatory)

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(D_LIBFT)$(LIBFT)
	@printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"
	@echo "$(LGREEN)Software Compilation completed ...$(NO_OF_FILES) files done !$(DEF_COLOR)"

$(OBJS): $(D_OBJ)%.o : $(D_SRC)%.c $(HEADER)
		@mkdir -p $(D_OBJ)
		@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

do_libft:
	@$(MAKE) -C $(D_LIBFT)

deadpool_bonus:
	@$(call intro_bonus)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) $(D_LIBFT)$(LIBFT)
	@printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"
	@echo "$(LGREEN)Software Compilation completed !$(DEF_COLOR)"

$(OBJS_BONUS): $(D_OBJ_BONUS)%.o : $(D_SRC_BONUS)%.c $(HEADER_BONUS)
		@mkdir -p $(D_OBJ_BONUS)
		@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

bonus: deadpool_bonus do_libft $(NAME_BONUS)
	
clean:
	@$(call cleaning, $(RM) $(D_OBJ))
	@$(RM) $(D_OBJ_BONUS)
	@$(MAKE) --no-print-directory -C $(D_LIBFT) clean

fclean:	clean
	@$(call fcleaning, $(RM) $(NAME))
	@$(RM) $(NAME_BONUS)
	@$(MAKE) --no-print-directory -C $(D_LIBFT) fclean

re:	fclean all

.PHONY: all clean fclean re
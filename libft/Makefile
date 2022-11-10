#****VARIABLES****
NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra #-I -nostartfiles
RM = rm -rf
AR = ar rcs
D_OBJ = obj/
D_SRC = src/
HEADER = includes/libft.h
OBJS = $(patsubst $(D_SRC)%.c,$(D_OBJ)%.o,$(SRCS))

OK_STRING = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING = "[WARNING]"
COMP_STRING = "Generating"
CLEAN_STRING = "Cleaning"
ARCH_STRING = "Archiving"

FCLEAN = 0

#****COLORS****
LRED = \033[91m
LGREEN = \033[92m
LYELLOW = \033[93
LMAGENTA = \033[95m
LCYAN = \033[96m
DEF_COLOR = \033[0;39m

NO_OF_FILES := $(words $(wildcard $(D_SRC)*.c))

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
printf "%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Objects Files & Directories$(DEF_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Objects Files & Directories" "💥$(DEF_COLOR)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Objects Files & Directories" "⚠️$(DEF_COLOR)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Objects Files & Directories" "✅$(DEF_COLOR)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define fcleaning
printf "%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Executable Files$(DEF_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Executable Files" "💥$(DEF_COLOR)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Executable Filess" "⚠️$(DEF_COLOR)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(CLEAN_STRING)$(LMAGENTA) LIBFT Executable Files" "✅$(DEF_COLOR)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

define archiving
printf "%b" "$(LCYAN)$(ARCH_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(LCYAN)$(ARCH_STRING)$(LMAGENTA) $@" "💥$(DEF_COLOR)\n"; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(LCYAN)$(ARCH_STRING)$(LMAGENTA) $@" "⚠️$(DEF_COLOR)\n"; \
	else \
		printf "%-60b%b" "$(LCYAN)$(ARCH_STRING)$(LMAGENTA) $(@F)" "✅$(DEF_COLOR)\n"; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

#****SOURCES****
SRCS = \
		src/ft_isalpha.c \
		src/ft_isdigit.c \
		src/ft_isalnum.c \
		src/ft_isascii.c \
		src/ft_isprint.c \
		src/ft_strlen.c \
		src/ft_memset.c \
		src/ft_bzero.c \
		src/ft_memcpy.c \
		src/ft_memmove.c \
		src/ft_strlcpy.c \
		src/ft_strlcat.c \
		src/ft_tolower.c \
		src/ft_toupper.c \
		src/ft_strchr.c \
		src/ft_strrchr.c \
		src/ft_strncmp.c \
		src/ft_memchr.c \
		src/ft_memcmp.c \
		src/ft_strnstr.c \
		src/ft_atoi.c \
		src/ft_calloc.c \
		src/ft_strdup.c \
		src/ft_substr.c \
		src/ft_strjoin.c \
		src/ft_strtrim.c \
		src/ft_split.c \
		src/ft_itoa.c \
		src/ft_strmapi.c \
		src/ft_striteri.c \
		src/ft_putchar_fd.c \
		src/ft_putstr_fd.c \
		src/ft_putendl_fd.c \
		src/ft_putnbr_fd.c \
		src/ft_lstnew.c \
		src/ft_lstadd_front.c \
		src/ft_lstsize.c \
		src/ft_lstlast.c \
		src/ft_lstadd_back.c \
		src/ft_lstdelone.c \
		src/ft_lstclear.c \
		src/ft_lstiter.c \
		src/ft_lstmap.c \
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/free_dbl_ptr.c \
		src/ft_atolong.c

all:	$(NAME)

$(NAME): $(OBJS)
	@$(call archiving, $(AR) $@ $(OBJS))
	@echo "$(LGREEN)LIBFT completed... $(NO_OF_FILES) files done !$(DEF_COLOR)"

$(OBJS) : $(D_OBJ)%.o : $(D_SRC)%.c $(HEADER)
	@mkdir -p $(D_OBJ)
	@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

clean:
	@$(call cleaning, $(RM) $(D_OBJ));

fclean: clean
	@$(call fcleaning, $(RM) $(NAME))

re: fclean all

.PHONY: all clean fclean re

#=================== DONE BUT NOT ASKED FOR ==================#
# ft_strmap.c ft_strstr.c ft_strcat.c  ft_strcmp.c ft_strcpy.c
# ft_strncat.c  ft_strncpy.c 
# ft_putchar.c ft_putnbr.c ft_putstr.c
#======================== NOT ASK FOR ========================#
# ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c
# ft_striter.c ft_strequ.c ft_strnequ.c ft_putendl.c 
#=============================================================#
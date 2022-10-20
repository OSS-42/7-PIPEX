#****VARIABLES****
NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -c #-I -nostartfiles
RM = rm -f
AR = ar rcs

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

NO_OF_FILES := $(words $(wildcard *.c))

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
LIBCFUN = \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_toupper.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c  ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c  ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		get_next_line.c get_next_line_utils.c free_dbl_ptr.c ft_atolong.c



OBJFUN = $(LIBCFUN:.c=.o)

.c.o :
	@$(call run_and_test, $(CC) $(CFLAGS) -c $< -o $@)

all:	$(NAME)

$(NAME): $(OBJFUN)
	@$(CC) $(CFLAGS) $(LIBCFUN)
	@$(AR) $(NAME) $(OBJFUN)
	@printf "%b" "$(LCYAN)$(COMP_STRING)$(LMAGENTA) $(@F)$(DEF_COLOR)\r"
	@echo "$(LGREEN)LIBFT completed... $(NO_OF_FILES) files done !$(DEF_COLOR)"

clean:
	@$(RM) $(OBJFUN)

fclean: clean
	@$(RM) $(NAME)

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
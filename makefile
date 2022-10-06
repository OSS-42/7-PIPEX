#****VARIABLES****
NAME = pipex
#NAME_BONUS = push_swap_bonus

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -f
LIBFT = libft.a
DIR_LIBFT = includes/libft/
DIR_BONUS = bonus/

#****COLORS****
LRED = \033[91m
LGREEN = \033[92m
LYELLOW = \033[93
LMAGENTA = \033[95m
LCYAN = \033[96m
DEF_COLOR = \033[0;39m

NO_OF_FILES := $(words $(wildcard *.c))

#****SOURCES****
SRC = pipex.c\

#HEADER = push_swap.h

#SRC_BONUS = \

OBJ = $(SRC:.c=.o) 
#OBJ_BONUS = $(SRC_BONUS:.c=.o)

#.o: .c
.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

#$(V).SILENT:

all:	$(NAME)

$(NAME):	$(DIR_LIBFT)/$(LIBFT) $(OBJ) $(SRC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(DIR_LIBFT)$(LIBFT)
	@echo "$(LGREEN)Software Compilation completed : $(NO_OF_FILES) files done !$(DEF_COLOR)"

$(DIR_LIBFT)/$(LIBFT):
	make -C $(DIR_LIBFT)

#$(NAME_BONUS): $(DIR_LIBFT)/$(LIBFT) $(OBJ_BONUS) $(SRC_BONUS)
#	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(DIR_LIBFT)$(LIBFT)
#	@echo "$(LGREEN)Compilation complete !$(DEF_COLOR)"

#bonus: $(DIR_LIBFT)/$(LIBFT) $(NAME_BONUS)

#tests:	

#btests : bonus
	
clean:
	$(RM) $(OBJ)
#	$(RM) $(OBJ_BONUS)
	make -C $(DIR_LIBFT) clean
	@echo "$(LCYAN)Objects files cleaned !$(DEF_COLOR)"

fclean:	clean
	$(RM) $(DIR_LIBFT)$(LIBFT)
	$(RM) $(NAME)
#	$(RM) $(NAME_BONUS)
	@echo "$(LCYAN)Executables files cleaned !$(DEF_COLOR)"

re:	fclean all
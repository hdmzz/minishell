O = objs/
S = srcs/
P = parser/
X = exec/

NAME =	minishell

HEADER = include/minishell.h

SRC = $Smain.c \
		$Sparser/parser.c \
		$Sexec/exec.c

OBJ = $(SRC:$S%=$O%.o)

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
LIBFLAGS =  libft/libft.a

.PHONY: all libft fclean re

all: libft $(NAME)

$O:
	@mkdir -p $@
	@mkdir -p $@parser
	@mkdir -p $@exec

$(OBJ): | $O

$(OBJ): $O%.o: $S% Makefile $(HEADER) libft/libft.a
	$(CC) $(CFLAGS) -g3 -lreadline -c $< -o $@

libft:
	git submodule init
	git submodule update
	@make -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -g3 $^ -lreadline $(LIBFLAGS) -o $@

clean:
	rm -rf $(SRC:$S%=$O%.o)
	rm -rf $(SRC:$S%=$D%.d)
	@make clean -C libft

fclean:	clean
	rm -rf $(NAME)
	@make fclean -C libft

re:	fclean all 

NAME = pipex

SRC_DIR=srcs/

SRC = main.c ft_printf.c check_error.c ft_split.c ft_strjoin.c parsing.c utils.c utils2.c get_next_line.c get_next_line_utils.c

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
RM = rm -f

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all: $(NAME)

bonus: all

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re

.SILENT:

NAME = pipex

NAME_BONUS=

SRC_DIR=srcs/
BONUS_DIR=bonus/

SRC = main.c ft_split.c ft_strjoin.c parsing.c utils.c utils2.c

BONUS =

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

BONUS_OBJ = $(addprefix $(BONUS_DIR), $(BONUS:.c=.o))

CC = gcc
CFLAGS = -I./includes
RM = rm -f

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(NAME_BONUS): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $@

all: $(NAME)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re

.SILENT:

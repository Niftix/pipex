NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I header -I gnl
LIBFT = libft/libft.a
SRC = src/parsing.c src/utils.c src/pipex.c
SRC_BONUS = src/parsing_bonus.c src/utils_bonus.c src/pipex_bonus.c \
		src/exec_bonus.c src/init_bonus.c
SRC_GNL = gnl/get_next_line.c gnl/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ_GNL = $(SRC_GNL:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)

bonus: .bonus

.bonus: $(OBJ_BONUS) $(OBJ_GNL)
	make -C libft
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_BONUS) $(OBJ_GNL) $(LIBFT) -o $(NAME)
	@touch .bonus

clean:
	rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_GNL) .bonus
	make -C libft clean

fclean: clean
	rm -f $(NAME) .bonus
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re

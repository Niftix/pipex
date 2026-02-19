NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I header -I gnl
LIBFT = libft/libft.a
SRC = src/parsing.c src/utils.c src/pipex.c
SRC_BONUS = src_bonus/parsing_bonus.c src_bonus/utils_bonus.c \
		src_bonus/pipex_bonus.c src_bonus/exec_bonus.c src_bonus/init_bonus.c
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
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_BONUS) $(OBJ_GNL) $(LIBFT) -o $(NAME_BONUS)
	@touch .bonus

clean:
	rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_GNL) .bonus
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS) .bonus
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re

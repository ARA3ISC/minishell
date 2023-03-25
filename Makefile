NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = @cc
FT_SRC = src/minishell.c src/parsing/parsing.c src/ls_utils.c src/error.c libft/ft_split.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strjoin.c \
libft/ft_strtrim.c libft/ft_strdup.c libft/ft_strlen.c


# FT_SRC_bonus =


OBJ = $(FT_SRC:.c=.o)

# OBJ_bonus = $(FT_SRC_bonus:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C costumizing/
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I ~/Users/eej-jama/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/eej-jama/goinfre/homebrew/Cellar/readline/8.2.1/lib -lreadline

# bonus: $(OBJ_bonus)
#     cc $(CFLAGS) $(OBJ_bonus) -o

clean:
	@rm -f $(OBJ)

fclean: clean
	@make -C costumizing mse7
	@rm -f $(NAME)

re: fclean all
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
#-fsanitize=address
CC = @cc
FT_SRC = src/minishell.c src/parsing/parsing.c src/parsing/ls_utils.c src/parsing/error.c src/parsing/banner.c src/parsing/helper.c \
src/parsing/signals.c src/parsing/syntax_error.c libft/ft_split.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strjoin.c \
libft/ft_strtrim.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_isalnum.c libft/ft_isdigit.c libft/ft_isalpha.c


# FT_SRC_bonus =


OBJ = $(FT_SRC:.c=.o)

# OBJ_bonus = $(FT_SRC_bonus:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C costumizing/
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

# bonus: $(OBJ_bonus)
#     cc $(CFLAGS) $(OBJ_bonus) -o

clean:
	@rm -f $(OBJ)

fclean: clean
	@make -C costumizing mse7
	@rm -f $(NAME)

re: fclean all

# -I ~/Users/eej-jama/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/eej-jama/goinfre/homebrew/Cellar/readline/8.2.1/lib
#  -I ~/Users/maneddam/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/maneddam/goinfre/homebrew/Cellar/readline/8.2.1/lib

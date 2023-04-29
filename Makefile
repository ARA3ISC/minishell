NAME = minishell
CFLAGS = -Wall -Wextra -Werror
#-fsanitize=address
CC = @cc #-fsanitize=address -g
FT_SRC = src/minishell.c src/parsing/parsing.c src/parsing/ls_utils.c src/parsing/error.c src/parsing/banner.c src/parsing/helper.c \
src/parsing/signals.c src/parsing/syntax_error.c libft/ft_split.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strjoin.c \
libft/ft_strtrim.c libft/ft_strdup.c libft/ft_strncmp.c libft/ft_strlen.c libft/ft_isalnum.c libft/ft_isdigit.c libft/ft_isalpha.c libft/ft_strcmp.c \
src/execution/execution.c src/execution/utils.c src/execution/execute_list_cmds.c src/execution/builtins.c src/execution/builtins/ft_echo.c \
src/execution/builtins/ft_cd.c src/execution/builtins/ft_pwd.c src/execution/builtins/ft_exit.c src/execution/builtins/ft_export.c \
src/execution/builtins/ft_env.c src/execution/builtins/ft_unset.c



OBJ = $(FT_SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	@make -C costumizing/
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJ)

fclean: clean
	@make -C costumizing mse7
	@rm -f $(NAME)

re: fclean all

#
#  -I ~/Users/maneddam/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/maneddam/goinfre/homebrew/Cellar/readline/8.2.1/lib

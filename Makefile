NAME = minishell
CFLAGS = -Wall -Wextra -Werror

FT_SRC = src/minishell.c
	

# FT_SRC_bonus = 


OBJ = $(FT_SRC:.c=.o)

# OBJ_bonus = $(FT_SRC_bonus:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	make -C ft_printf/
	cc $(CFLAGS) $(OBJ) -o $(NAME) libft/libft.a ft_printf/libftprintf.a

# bonus: $(OBJ_bonus)
# 	cc $(CFLAGS) $(OBJ_bonus) -o 

clean:
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	make -C ft_printf/ fclean 
	rm -f $(NAME)

re: fclean all
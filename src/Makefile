.PHONY: all $(NAME) bonus clean fclean re

NAME := pipex

CC := cc

AR := ar rcs

CFLAGS := -Wall -Wextra -Werror -g

LIBFT := libft

SRCS := pipex.c pipex_utils.c ft_parser.c \

SRCS_BONUS := bonus/pipex_bonus.c bonus/pipex_utils_bonus.c \
			bonus/ft_parser_bonus.c bonus/ft_heredoc_bonus.c \

all:	$(NAME)

# $(OBJS): $(SRCS)
# 	$(CC) $(CFLAGS) -c $*.c -o $@

# $(OBJS_BONUS): $(SRCS_BONUS)
# 	$(CC) $(CFLAGS) -c $*.c -o $@

$(NAME):
	make all -C $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBFT)/$(LIBFT).a

bonus:
	make all -C $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME) $(LIBFT)/$(LIBFT).a

clean:
	make clean -C $(LIBFT)

fclean:	clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -f ./bonus/$(NAME)

re:	fclean all

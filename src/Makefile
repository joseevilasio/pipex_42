.PHONY: all $(NAME) bonus clean fclean re

NAME := pipex

CC := cc

AR := ar rcs

CFLAGS := -Wall -Wextra -Werror -g

LIBFT := libft

SRCS := pipex_utils.c ft_parser.c \

OBJS := pipex_utils.o  ft_parser.o \

SRCS_BONUS := bonus/pipex_utils_bonus.c bonus/ft_parser_bonus.c \

OBJS_BONUS :=  bonus/pipex_utils_bonus.o  bonus/ft_parser_bonus.o \

all:	$(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $*.c -o $@

$(OBJS_BONUS): $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c $*.c -o $@

$(NAME): $(OBJS)
	make all -C $(LIBFT)
	ar rcs $(NAME).a ./*.o
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME) $(NAME).a $(LIBFT)/$(LIBFT).a

bonus: fclean $(OBJS_BONUS)
	make all -C $(LIBFT)
	ar rcs bonus/$(NAME).a bonus/*.o
	$(CC) $(CFLAGS) bonus/$(NAME)_bonus.c -o $(NAME) bonus/$(NAME).a $(LIBFT)/$(LIBFT).a

clean:
	make clean -C $(LIBFT)
	rm -f ./*.o
	rm -f ./bonus/*.o

fclean:	clean
	make fclean -C $(LIBFT)
	rm -f ./*.a
	rm -f ./bonus/*.a
	rm -f $(NAME)
	rm -f ./bonus/$(NAME)

re:	fclean all

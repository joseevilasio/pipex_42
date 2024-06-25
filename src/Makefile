.PHONY: all $(NAME) bonus clean fclean re

NAME := pipex

CC := cc

AR := ar rcs

CFLAGS := -Wall -Wextra -Werror -g

LIBFT := libft

SRCS := pipex_utils.c \

OBJS := pipex_utils.o \

# SRCS_BONUS := bonus/ft_printf_bonus.c bonus/ft_uitoa_hex_bonus.c \
# 	bonus/ft_ptoa_bonus.c bonus/ft_uitoa_bonus.c  bonus/ft_printf_utils_bonus.c \
# 	bonus/ft_parserflags_bonus.c bonus/ft_fmtspecifiers_bonus.c \
# 	bonus/ft_add_precision_bonus.c bonus/ft_format_utils_bonus.c\

# OBJS_BONUS := $(SRCS_BONUS:.c=.o)

all:	$(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $*.c -o $@

# $(OBJS_BONUS): $(SRCS_BONUS)
# 	$(CC) $(CFLAGS) -c $*.c -o $@

$(NAME): $(OBJS)
	make all -C $(LIBFT)
	cp $(LIBFT)/*.o .
	ar rcs $(NAME).a ./*.o
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME) $(NAME).a

# bonus: fclean $(OBJS_BONUS)
# 	make all -C $(LIBFT)
# 	cp $(LIBFT)/*.o .
# 	cp bonus/*.o .
# 	ar rcs $(NAME) ./*.o

clean:
	make clean -C $(LIBFT)
	rm -f ./*.o
	rm -f ./bonus/*.o

fclean:	clean
	make fclean -C $(LIBFT)
	rm -f ./*.a
	rm -f $(NAME)

re:	fclean all

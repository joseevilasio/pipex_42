.PHONY: all $(NAME) clean fclean re bonus

NAME := libft.a

CC := cc

CFLAGS := -Wall -Wextra -Werror -g

SRCS := ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcat.c ft_substr.c \
	ft_bzero.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c ft_calloc.c \
	ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c ft_isalnum.c \
	ft_memcmp.c ft_split.c ft_strmapi.c ft_isalpha.c ft_memcpy.c \
	ft_strchr.c ft_strncmp.c ft_isascii.c ft_memmove.c ft_strdup.c \
	ft_strnstr.c ft_isdigit.c ft_memset.c ft_striteri.c ft_strrchr.c \
	ft_isprint.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c \
	ft_printf.c ft_uitoa_hex.c ft_ptoa.c ft_uitoa.c  ft_printf_utils.c \
	get_next_line.c \

OBJS := $(SRCS:.c=.o)

SRCS_B := ft_lstnew.c ft_lstadd_back.c ft_lstsize.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstiter.c ft_lstdelone.c ft_lstlast.c ft_lstmap.c \

OBJS_B := $(SRCS_B:.c=.o) $(OBJS)

all:	$(NAME)

$(OBJS):	$(SRCS)

$(OBJS_B):	$(SRCS_B)

$(NAME): $(OBJS)
	ar rcs ./$(NAME) ./*.o

bonus: $(OBJS_B)
	make OBJS="$(OBJS_B)" all

clean:
	rm -f ./*.o

fclean:	clean
	rm -f ./$(NAME)

re:	fclean all


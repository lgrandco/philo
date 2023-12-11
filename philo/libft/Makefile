NAME = libft.a

CC = clang

CFLAGS = -Wall -Werror -Wextra -I.

CPATH = ..

RM = rm -f

SRC_PATH = srcs

SRC =	ft_atoi.c \
	ft_isalnum.c \
	ft_isdigit.c \
	ft_memchr.c \
	ft_memset.c \
	ft_putnbr_fd.c \
	ft_strchr.c \
	ft_strjoin.c \
	ft_strncmp.c \
	ft_substr.c \
	ft_bzero.c \
	ft_isalpha.c \
	ft_isprint.c \
	ft_memcmp.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strnstr.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_isascii.c \
	ft_itoa.c \
	ft_memcpy.c \
	ft_putendl_fd.c \
	ft_split.c \
	ft_striteri.c \
	ft_strtrim.c \
	ft_strmapi.c \
	ft_strrchr.c \
	ft_toupper.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_itoa_base.c \
	ft_abs.c \
	ft_min.c \
	ft_max.c \
	get_next_line.c \
	handler.c \
	pad.c \
	printf_utils.c \
	ft_printf.c

BONUS_SRC =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		exit_error.c

SRC := $(addprefix $(SRC_PATH)/,$(SRC))

BONUS_SRC := $(addprefix $(SRC_PATH)/,$(BONUS_SRC))

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: ${NAME}

$(NAME): ${OBJ} $(BONUS_OBJ) Makefile libft.h
	ar rc ${NAME} ${OBJ} $(BONUS_OBJ)

bonus: ${NAME}

clean:
	@ ${RM} ${OBJ} ${BONUS_OBJ}


fclean: clean
	@ ${RM} ${NAME}


re: fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	$(CC) -nostartfiles -shared -o libft.so $(OBJ)

.PHONY: all bonus clean fclean re so

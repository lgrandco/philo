NAME = philo

HEADER = $(NAME).h

NAME_BONUS = $(NAME)_bonus

SRC_PATH = srcs

SRC = main.c ft_atoi.c init.c actions.c checks.c utils.c

SRC := $(addprefix $(SRC_PATH)/,$(SRC))

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -Wall -Werror -Wextra -pthread -g3 -I. -Ilibft

RM = rm -f

LIBFT_PATH = ./libft

LIBFT =

all : $(NAME)

$(LIBFT) :
	make bonus -C $(LIBFT_PATH)

$(NAME) : $(LIBFT) ${OBJ} $(HEADER) Makefile
	$(CC) $(CFLAGS) -D BONUS=0 -o $(NAME) -g3 -Ilibft $(SRC) $(LIBFT)

fsan: $(LIBFT) ${OBJ} $(HEADER) Makefile
	$(CC) $(CFLAGS) -fsanitize=thread -D BONUS=0 -o $(NAME) -g3 -Ilibft $(SRC) $(LIBFT)

$(NAME_BONUS) : $(LIBFT) ${OBJ} pipex.h Makefile
	$(CC) $(CFLAGS) -D BONUS=1 -o $(NAME_BONUS) -g3 -Ilibft $(SRC) $(LIBFT)

bonus: $(NAME_BONUS)

clean :
	@ $(RM) $(NAME) $(OBJ)

fclean : clean
	@ $(RM) $(NAME) $(NAME_BONUS)

c :
	${CC} -g3 -Ilibft $(SRC)

re : fclean all

.PHONY : all clean fclean re

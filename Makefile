NAME = test
FLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=42 -g -fsanitize=leak
SRCS = get_next_line.c get_next_line_utils.c main.c
OBJ = $(SRCS:%.c=%.o)
RM = rm -rf

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
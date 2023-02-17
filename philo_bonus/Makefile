NAME = philo_bonus
CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread
all: $(NAME)

$(NAME): *.o
	$(CC) $(FLAGS) -o $(NAME) *.o

*.o: *.c
	$(CC) $(FLAGS) -c *.c

clean:
	rm -f *.o

fclean: clean
	rm -f philo

re: fclean all
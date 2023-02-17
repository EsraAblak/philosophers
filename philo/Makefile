NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread
FLAGS_DATARACE = -fsanitize=thread -g

all: $(NAME)

$(NAME): *.o
	$(CC) $(FLAGS) -o $(NAME) *.o

*.o: *.c
	$(CC) $(FLAGS) -c *.c

data_race: *.o
	@$(CC) $(FLAGS_DATARACE) -o $(NAME) *.o 

clean:
	rm -f *.o

fclean: clean
	rm -f philo

re: fclean all
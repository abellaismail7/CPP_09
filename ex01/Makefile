CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g

FILES = main.o RPN.o
NAME = rpn


all: $(NAME)

$(NAME): $(FILES)
	$(CC) $(FILES) -o $(NAME)


%.o: %.c RPN.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

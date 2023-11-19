CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98

FILES = main.o BitcoinExchange.o
NAME = btc


all: $(NAME)

$(NAME): $(FILES)
	$(CC) $(FILES) -o $(NAME)


%.o: %.c BitcoinExchange.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

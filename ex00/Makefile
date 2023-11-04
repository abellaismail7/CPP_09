CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g

FILES = main.o BitcoinExchange.o
NAME = btc


all: $(NAME)

$(NAME): $(FILES)
	$(CC) $(FILES) -o $(NAME)


%.o: %.c BitcoinExchange.h
	$(CC) $(CFLAGS) -c $< -o $@

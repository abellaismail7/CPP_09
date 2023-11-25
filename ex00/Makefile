CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

BUILD_DIR = build

FILES = main BitcoinExchange

OBJ = $(addprefix $(BUILD_DIR)/, $(FILES:=.o))

BIN = btc

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp BitcoinExchange.hpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(BIN)

re: fclean all

.PHONY: all clean fclean re

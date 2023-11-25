CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g

BUILD_DIR = build

FILES = main PmergeMe

OBJ = $(addprefix $(BUILD_DIR)/, $(FILES:=.o))

BIN = PmergeMe

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -fsanitize=address -o $@

$(BUILD_DIR)/%.o: %.cpp PmergeMe.hpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(BIN)

re: fclean all

.PHONY: all clean fclean re

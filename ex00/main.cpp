#include <iostream>
#include "BitcoinExchange.hpp"

int main (int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string line;

	char *filename = argv[1];
	BitcoinExchange be(filename);
	if (!be.feed())
		return 1;
	if (!be.validate_header(std::cin, "date | value"))
		return 1;


	while (getline(std::cin, line)) {
		double value;
		double rate;
		std::string date;
		if(!be.validate_line(line, " | ", value, date)){
			continue;
		}
		if (!be.lookup(date, rate)) {
			std::cout << "Error: date not found " << date  << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << rate * value  << std::endl;
	}

	return 0;
}

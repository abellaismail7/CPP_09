#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main (int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string line;

	BitcoinExchange be("data.csv");
	if (!be.feed())
		return 1;

	
	std::ifstream file;
	file.open(argv[1]);
	if (!file.is_open()) {
		std::cout << "Error: could not open file." << std::endl;
		return 0;
	}

	if (!be.validate_header(file, "date | value"))
		return 1;
	while (getline(file, line)) {
		double value;
		double rate;
		std::string date;
		if(!be.validate_line(line, value, date)){
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

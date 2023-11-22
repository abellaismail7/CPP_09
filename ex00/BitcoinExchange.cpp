#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <climits>


BitcoinExchange::BitcoinExchange(const std::string &filename) {
	this->filename = filename;
}

int BitcoinExchange::feed() {
	std::string line;
	std::ifstream file;
	file.open(this->filename);
	if (!file.is_open()) {
		std::cout << "Error: could not open file." << std::endl;
		return 0;
	}
	if (!validate_header(file, "date,exchange_rate")) {
		return 0;
	}
	while (getline(file, line)) {
		if(!_validate_line(line, ",")){
			std::cout << "Error: bad input => " << line << std::endl;
			return 0;
		}
		double value = strtod(line.substr(11).c_str(), NULL);
		if(value < 0){
			std::cout << "Error: not a positive number." << std::endl;
			return 0;
		}
		std::string date = line.substr(0, 10);
		data[date] = value;
	}
	return 1;
}

int BitcoinExchange::validate_date(const std::string &line) {
	long year;
	long month; 
	long day;
	for(int i = 0; i < 10;i++) {
		if (i == 7 || i == 4)
		{
			if (line[i] != '-')
				goto Error;
		}
		else if (line[i] < '0' || line[i] > '9')
			goto Error;
	}
	year = std::strtol(line.substr(0, 4).c_str(), NULL, 10);
	month = std::strtol(line.substr(5, 2).c_str(), NULL, 10);
	day = std::strtol(line.substr(8, 2).c_str(), NULL, 10);
	if (!isValidDay(year, month, day))
		goto Error;
	return 1;
	Error:
		//std::cout << "Error: bad input => " << line << std::endl;
		return 0;
}


int BitcoinExchange::isValidDay(int year, int month, int day) {
	if (day > 31 || month > 12)
		return 0;
	if (month == 2 && year % 4 == 0 && day > 29)
		return 0;
	if (month == 2 && year % 4 != 0 && day > 28)
		return 0;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return 0;
	return 1;
}

bool contain_digit(const std::string &line) {
	
	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] >= '0' && line[i] <= '9')
			return true;
	}
	return false;
}

int BitcoinExchange::validate_value(const std::string &line, int offset) {
	char *endptr;
	std::string value = line.substr(offset);
	strtod(value.c_str(), &endptr);
	if (*endptr != '\0' || !contain_digit(value)) {
		return 0;
	}
	return 1;
}

int BitcoinExchange::_validate_line(const std::string &line, const std::string &sep) {
	size_t pos = line.find(sep);
	if (pos == std::string::npos) {
		return 0;
	}
	if (!validate_date(line.substr(0, pos))) {
		return 0;
	}
	if (!validate_value(line, pos+ sep.length())) {
		return 0;
	}
	return 1;
}

int BitcoinExchange::validate_header(std::istream &file, const std::string &header) {
	std::string line;
	if (!getline(file, line) || line != header) {
		std::cout << "Error: invalid file format" << std::endl;
		return 0;
	}
	return 1;
}

int BitcoinExchange::validate_line(const std::string &line, double &value, std::string &date) {
	if (!_validate_line(line, " | "))
	{
		std::cout << "Error: bad input => " <<  line << std::endl;
		return 0;
	}
	date = line.substr(0, 10);
	if (!validate_date(date)) {
		//std::cout << "Error: invalid date" << std::endl;
		return 0;
	}
	std::string svalue = line.substr(13);
	value = strtod(svalue.c_str(), NULL);
	if (value > 1000) {
		std::cout << "Error: too large a number." << std::endl;
		return 0;
	}
	if (value < 0) {
		std::cout << "Error: not a positive number." << std::endl;
		return 0;
	}

	return 1;
}

int BitcoinExchange::lookup(const std::string &date, double &rate) {
	std::map<std::string, double>::iterator it;
	it = data.lower_bound(date);
	if (it == data.end()) {
		return 0;
	}
	rate = it->second;
	return 1;
}


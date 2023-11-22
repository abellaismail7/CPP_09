#include <string>
#include <map>


class BitcoinExchange {
private:
	std::string filename;
	std::map<std::string, double, std::greater<std::string> > data;

	int validate_date(const std::string &date);
	int validate_value(const std::string &line, int offset);
	int isValidDay(int year, int month, int day);
	int _validate_line(const std::string &line, const std::string &sep);

public:

	BitcoinExchange(const std::string &filename);
	int validate_line(const std::string &line, double &value, std::string &date);
	int validate_header(std::istream &file, const std::string &header);
	int feed();
	int lookup(const std::string &date, double &rate);
};

#include <string>

class RPN {
	private:
	std::string expression;
	public:
	RPN(const std::string & s);
	int calculate(int &res);
};

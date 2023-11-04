#include <iostream>
#include "RPN.hpp"


int main (int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " formula" << std::endl;
		return 1;
	}

	int result = 0;
	std::string formula = argv[1];
	RPN rpn(formula);

	if (!rpn.calculate(result)) {
		std::cout << "Error" << std::endl;
		return 1;
	}
	std::cout << result << std::endl;
	return 0;
}

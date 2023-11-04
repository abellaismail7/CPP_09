#include "RPN.hpp"
#include <stack>
#include <iostream>
#include <sstream>


RPN::RPN(const std::string & s) {
	this->expression = s;
}

int RPN::calculate(int &res) {
	std::stack<std::string> v;
	std::string s;
	std::stringstream st(this->expression);

	while (getline(st, s, ' ')) {
		if (s.length() > 0 && s[0] >= '0' && s[0] <= '9') {
			if (s.length() > 1)
				goto Error;
			v.push(s);
			continue;
		}
		if (v.size() < 2)
			goto Error;
		int b = std::strtol(v.top().c_str(), NULL, 10);
		v.pop();
		int a = std::strtol(v.top().c_str(), NULL, 10);
		v.pop();
		if (s == "+") {
			v.push(std::to_string(a + b));
		}
		else if (s == "-") {
			v.push(std::to_string(a - b));
		}
		else if (s == "*") {
			v.push(std::to_string(a * b));
		}
		else if (s == "/") {
			if (b == 0)
				goto Error;
			v.push(std::to_string(a / b));
		}
		else 
			goto Error;
	}
	if (v.size() != 1)
		goto Error;
	
	res = std::strtol(v.top().c_str(), NULL, 10);
	return 1;

Error:
	return 0;
}


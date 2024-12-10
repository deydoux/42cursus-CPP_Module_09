#ifndef RPN_HPP
#define RPN_HPP

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

class RPN {
private:
	std::stack<int>	_stack;
	std::string		_input;

	void 	calculate();
public:
	RPN();
	RPN(const char *input);
	RPN(const RPN &other);
	~RPN();

	RPN &operator=(const RPN &rhs);
};

#endif

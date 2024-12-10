#ifndef RPN_HPP
#define RPN_HPP

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

class RPN {
private:
	typedef std::stack<int>	stack_t;

	stack_t		_stack;
	std::string	_input;

	void	calculate();

	static void reverseStack(stack_t &stack);
public:
	RPN();
	RPN(const char *input);
	RPN(const RPN &other);
	~RPN();

	RPN &operator=(const RPN &rhs);
};

#endif

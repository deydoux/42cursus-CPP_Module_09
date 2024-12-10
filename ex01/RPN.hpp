#ifndef RPN_HPP
#define RPN_HPP

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

class RPN {
private:
	typedef std::stack<int>	stack_t;

	stack_t	_operands;

	void	calculate(std::string input);
	void	operate(const char &op);

	static bool		isOperand(const std::string &str);
	static bool		isOperator(const char &c);
	static size_t	operandSize(const std::string &str);
	static size_t	spaceSize(const std::string &str);
public:
	RPN();
	RPN(const char *input);
	RPN(const RPN &other);
	~RPN();

	RPN &operator=(const RPN &rhs);
};

#endif

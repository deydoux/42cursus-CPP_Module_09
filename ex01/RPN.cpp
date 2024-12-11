#include "RPN.hpp"

void RPN::calculate(std::string input) {
	while (!input.empty()) {
		size_t size = operandSize(input);

		if (size) {
			std::istringstream iss(input.substr(0, size));
			int n;
			iss >> n;
			_operands.push(n);
		} else if (isOperator(input[0])) {
			operate(input[0]);
			size = 1;
		} else
			size = spaceSize(input);

		if (size == 0)
			throw (std::logic_error("Invalid character"));

		input.erase(0, size);
	}

	if (_operands.size() != 1)
		throw (std::logic_error("Invalid expression"));

	std::cout << _operands.top() << std::endl;
}

void RPN::operate(const char &op) {
	if (_operands.size() < 2)
		throw (std::logic_error("Not enough operands"));

	int b = _operands.top();
	_operands.pop();

	switch (op) {
	case '+':
		_operands.top() += b;
		break ;
	case '-':
		_operands.top() -= b;
		break ;
	case '*':
		_operands.top() *= b;
		break ;
	case '/':
		if (b == 0)
			throw (std::logic_error("Division by zero"));
		_operands.top() /= b;
		break ;
	default:
		throw (std::logic_error("Invalid operator"));
	}
}

bool RPN::isOperand(const std::string &str) {
	for (size_t i = 0; str[i]; i++)
		if (!std::isdigit(str[i]))
			return (false);
	return (true);
}

bool RPN::isOperator(const char &c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

size_t RPN::operandSize(const std::string &str) {
	size_t size = 0;
	while (std::isdigit(str[size]) || (size == 0 && str[0] == '-'))
		size++;
	return (size == 1 && str[0] == '-' ? 0 : size);
}

size_t RPN::spaceSize(const std::string &str) {
	size_t size = 0;
	while (std::isspace(str[size]))
		size++;
	return (size);
}

RPN::RPN(): _operands() {}

RPN::RPN(const char *input): _operands() {
	if (!input) {
		std::cerr << "Error: No input provided" << std::endl;
		return ;
	}

	try {
		calculate(input);
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

RPN::RPN(const RPN &other): _operands(other._operands) {}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &rhs) {
	_operands = rhs._operands;
	return (*this);
}

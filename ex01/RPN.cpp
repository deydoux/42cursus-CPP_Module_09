#include "RPN.hpp"

void RPN::calculate(std::string expression) {
	while (!expression.empty()) {
		size_t size = operandSize(expression);

		if (size) {
			std::istringstream iss(expression.substr(0, size));
			double n;
			iss >> n;
			_operands.push(n);
		} else if (isOperator(expression[0])) {
			operate(expression[0]);
			size = 1;
		} else
			size = spaceSize(expression);

		if (size == 0)
			throw (std::logic_error("Invalid character"));

		expression.erase(0, size);
	}

	if (_operands.size() != 1)
		throw (std::logic_error("Invalid expression"));

	std::cout << _operands.top() << std::endl;
}

void RPN::operate(const char &op) {
	if (_operands.size() < 2)
		throw (std::logic_error("Not enough operands"));

	double b = _operands.top();
	_operands.pop();
	double a = _operands.top();
	_operands.pop();

	double result;
	switch (op) {
	case '+':
		result = a + b;
		break ;
	case '-':
		result = a - b;
		break ;
	case '*':
		result = a * b;
		break ;
	case '/':
		if (b == 0)
			throw (std::logic_error("Division by zero"));
		result = a / b;
		break ;
	default:
		throw (std::logic_error("Invalid operator"));
	}

	_operands.push(result);
#ifdef DEBUG
	std::cout << a << " " << op << " " << b << " = " << result << std::endl;
#endif
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
	bool dot = false;

	while (std::isdigit(str[size]) || (size == 0 && str[0] == '-') || (str[size] == '.' && !dot))
		if (str[size++] == '.')
			dot = true;

	return ((size == 1 && (str[0] == '-' || str[0] == '.')) ? 0 : size);
}

size_t RPN::spaceSize(const std::string &str) {
	size_t size = 0;
	while (std::isspace(str[size]))
		size++;
	return (size);
}

RPN::RPN(): _operands() {}

RPN::RPN(const char *expression): _operands() {
	if (!expression) {
		std::cerr << "Error: No expression provided" << std::endl;
		return ;
	}

	try {
		calculate(expression);
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

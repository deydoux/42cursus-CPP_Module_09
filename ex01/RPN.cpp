#include "RPN.hpp"

void RPN::calculate() {
}

RPN::RPN() : _stack(), _input() {}

RPN::RPN(const char *input): _stack() {
	if (!input)
		std::cerr << "Error: No input provided" << std::endl;
	else
		_input = input;
}

RPN::RPN(const RPN &other): _stack(other._stack), _input(other._input) {}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &rhs) {
	_stack = rhs._stack;
	_input = rhs._input;
	return (*this);
}

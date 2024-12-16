#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

class PmergeMe {
private:
	static size_t	jacobsthal(size_t n);
public:
	PmergeMe();
	PmergeMe(char **input, size_t size);
	PmergeMe(const PmergeMe &other);
	~PmergeMe();

	PmergeMe	&operator=(const PmergeMe &rhs);

	template <typename C>
	C	algorithm(C container);
};

#include "PmergeMe.tpp"

#endif

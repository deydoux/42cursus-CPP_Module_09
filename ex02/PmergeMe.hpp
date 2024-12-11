#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

class PmergeMe {
public:
	PmergeMe();
	PmergeMe(const char *input);
	PmergeMe(const PmergeMe &other);
	~PmergeMe();

	PmergeMe &operator=(const PmergeMe &rhs);

	template <typename T>
	void	fjAlgorithm(T container);
};

#include "PmergeMe.tpp"

#endif

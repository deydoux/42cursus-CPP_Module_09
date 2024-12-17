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

	template <typename C>
	C		algorithm(C container, size_t pairSize = 1);
	template <typename C>
	C		popOdd(C &container, size_t pairsSize);
	template <typename C>
	void	sortPairs(C &container, size_t pairSize);
public:
	PmergeMe();
	PmergeMe(char **input, size_t size);
	PmergeMe(const PmergeMe &other);
	~PmergeMe();

	PmergeMe	&operator=(const PmergeMe &rhs);
};

#include "PmergeMe.tpp"

#endif

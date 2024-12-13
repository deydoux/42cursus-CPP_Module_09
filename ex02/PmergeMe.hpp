#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

class PmergeMe {
private:
	typedef std::pair<int, int>	pair_t;
public:
	PmergeMe();
	PmergeMe(const char *input);
	PmergeMe(const PmergeMe &other);
	~PmergeMe();

	PmergeMe	&operator=(const PmergeMe &rhs);

	template <template <typename T, typename Alloc = std::allocator<T> > class C>
	void		algorithm(C<int> container);
	template <template <typename T, typename Alloc = std::allocator<T> > class C>
	C<pair_t>	initPairs(C<int> container, size_t size);
	template <template <typename T, typename Alloc = std::allocator<T> > class C>
	void	sortPairs(C<pair_t> pairs, size_t size);
};

#include "PmergeMe.tpp"

#endif

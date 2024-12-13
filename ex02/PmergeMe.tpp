#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <template <typename T, typename Alloc = std::allocator<T> > class C>
void PmergeMe::algorithm(C<int> container) {
	C<pair_t> pairs = initPairs(container);
}

template <template <typename T, typename Alloc = std::allocator<T> > class C>
C<PmergeMe::pair_t> PmergeMe::initPairs(C<int> container) {
	C<pair_t> pairs;

	for (typename C<int>::iterator it = container.begin(); it != container.end(); ++it) {
		typename C<int>::iterator it2 = it + 1;
		if (it2 != container.end())
			pairs.push_back(pair_t(*it++, *it2));
		else
			pairs.push_back(pair_t(*it, 0));
	}

	return (pairs);
}

#endif

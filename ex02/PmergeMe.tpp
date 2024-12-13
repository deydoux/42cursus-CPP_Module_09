#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <template <typename T, typename Alloc = std::allocator<T> > class C>
void PmergeMe::algorithm(C<int> container) {
	size_t size = container.size();
	C<pair_t> pairs = initPairs(container, size);
	sortPairs(pairs, size / 2);
}

template <template <typename T, typename Alloc = std::allocator<T> > class C>
C<PmergeMe::pair_t> PmergeMe::initPairs(C<int> container, size_t size) {
	C<pair_t> pairs;

	for (size_t i = 1; i < size; i += 2)
		pairs.push_back(pair_t(container[i - 1], container[i]));

	if (size % 2)
		pairs.push_back(pair_t(container[size - 1], 0));

	return (pairs);
}

template <template <typename T, typename Alloc = std::allocator<T> > class C>
void PmergeMe::sortPairs(C<pair_t> pairs, size_t size) {
	for (size_t i = 0; i < size; i++)
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
}
#endif

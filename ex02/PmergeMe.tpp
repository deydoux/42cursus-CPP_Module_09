#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <template <typename T, typename Alloc = std::allocator<T> > class C>
C<int> PmergeMe::algorithm(C<int> container) {
	size_t size = container.size();
	if (size < 2)
		return (container);

	C<pair_t> pairs = initPairs(container, size);
	sortPairs(pairs, size / 2);

	C<int> sorted = sortLower(pairs, size / 2 + size % 2);
	insertLarger(sorted, pairs, size / 2);

	return (sorted);
}

template <template <typename T, typename Alloc = std::allocator<T> > class C>
C<PmergeMe::pair_t> PmergeMe::initPairs(const C<int> &container, size_t size) {
	C<pair_t> pairs;

	for (size_t i = 1; i < size; i += 2)
		pairs.push_back(pair_t(container[i - 1], container[i]));

	if (size % 2)
		pairs.push_back(pair_t(container[size - 1], 0));

	return (pairs);
}

template <template <typename T, typename Alloc = std::allocator<T> > class C>
void PmergeMe::sortPairs(C<pair_t> &pairs, size_t size) {
	for (size_t i = 0; i < size; i++)
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
}

template <template <typename T, typename Alloc = std::allocator<T> > class C>
C<int> PmergeMe::sortLower(const C<pair_t> &pairs, size_t size) {
	C<int> lower;

	for (size_t i = 0; i < size; i++)
		lower.push_back(pairs[i].first);

	return (algorithm(lower));
}

template <template <typename T, typename Alloc = std::allocator<T> > class C>
void PmergeMe::insertLarger(C<int> &sorted, const C<pair_t> &pairs, size_t size) {
	C<bool> inserted(size, false);

	for (size_t i = 0; i < size; i++) {
		size_t j = jacobsthal(i + 1) - 1;
		if (j >= size)
			j = size - 1;
		if (!inserted[j]) {
			typename C<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), pairs[j].second);
			sorted.insert(it, pairs[j].second);
			inserted[j] = true;
		}
	}

	for (size_t k = 0; k < size; k++) {
		if (!inserted[k]) {
			typename C<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), pairs[k].second);
			sorted.insert(it, pairs[k].second);
		}
	}
}

#endif

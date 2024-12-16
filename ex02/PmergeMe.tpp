#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <typename C>
C PmergeMe::algorithm(C container, size_t pairSize) {
	size_t size = container.size();
	size_t pairs = size / pairSize;

	if (pairs < 2)
		return (container);

	sortPairs(container, size, pairSize);

	C main = algorithm(container, pairSize * 2);

	return (main);
}

template <typename C>
void PmergeMe::sortPairs(C &container, size_t size, size_t pairSize) {
	size -= pairSize;
	for (size_t i = 0; i < size; i += pairSize * 2)
		if (container[i] > container[i + pairSize])
			for (size_t j = 0; j < pairSize; j++)
				std::swap(container[i + j], container[i + j + pairSize]);
}

#endif

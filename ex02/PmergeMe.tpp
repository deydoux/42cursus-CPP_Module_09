#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <typename C>
C PmergeMe::algorithm(C container, size_t pairSize) {
	size_t size = container.size();
	if (size / pairSize < 2)
		return (container);

	sortPairs(container, size, pairSize);

	C main = algorithm(container, pairSize * 2);

	return (main);
}

template <typename C>
void PmergeMe::sortPairs(C &container, size_t size, size_t pairSize) {
	size -= size % (pairSize * 2);

	for (size_t i = 0; i < size; i += pairSize * 2)
		if (container[i + pairSize - 1] > container[i + pairSize * 2 - 1])
			for (size_t j = 0; j < pairSize; j++)
				std::swap(container[i + j], container[i + j + pairSize]);
}

#endif

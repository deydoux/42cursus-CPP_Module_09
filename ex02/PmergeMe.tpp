#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <typename C>
C PmergeMe::algorithm(C container, size_t pairSize) {
	if (container.size() / pairSize < 2)
		return (container);

	C odd = popOdd(container, pairSize * 2);
	sortPairs(container, pairSize);

	C main = algorithm(container, pairSize * 2);
	main.insert(main.end(), odd.begin(), odd.end());
	return (main);
}

template <typename C>
C PmergeMe::popOdd(C &container, size_t pairsSize) {
	C odd;

	size_t oddSize = container.size() % pairsSize;
	if (oddSize) {
		odd.insert(odd.begin(), container.end() - oddSize, container.end());
		container.erase(container.end() - oddSize, container.end());
	}

	return (odd);
}

template <typename C>
void PmergeMe::sortPairs(C &container, size_t pairSize) {
	for (size_t i = 0; i < container.size(); i += pairSize * 2)
		if (container[i + pairSize - 1] > container[i + pairSize * 2 - 1])
			for (size_t j = 0; j < pairSize; j++)
				std::swap(container[i + j], container[i + j + pairSize]);
}

#endif

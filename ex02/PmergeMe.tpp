#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <typename C>
void PmergeMe::algorithm(C &container, size_t pairSize) {
	C odd = pop(container, container.size() % (pairSize * 2));
	if (!container.size()) {
		container = odd;
		return ;
	}

	sortPairs(container, pairSize);
	algorithm(container, pairSize * 2);

	C pend = pop(container, container.size() - (pairSize * 2));
	container.insert(container.end(), pend.begin(), pend.end());
	container.insert(container.end(), odd.begin(), odd.end());
}

template <typename C>
C PmergeMe::pop(C &container, size_t size) {
	C popped;

	popped.insert(popped.begin(), container.end() - size, container.end());
	container.erase(container.end() - size, container.end());

	return (popped);
}

template <typename C>
void PmergeMe::sortPairs(C &container, size_t pairSize) {
	for (size_t i = 0; i < container.size(); i += pairSize * 2)
		if (container[i + pairSize - 1] > container[i + pairSize * 2 - 1])
			for (size_t j = 0; j < pairSize; j++)
				std::swap(container[i + j], container[i + j + pairSize]);
}

#endif

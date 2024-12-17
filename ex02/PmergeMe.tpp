#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"

template <typename C>
void PmergeMe::algorithm(C &container, size_t pairSize) {
	C odd = pop(container, container.size() % (pairSize * 2));
	if (container.empty()) {
		container = odd;
		return ;
	}

	sortPairs(container, pairSize);
	algorithm(container, pairSize * 2);

	C lower = popLower(container, pairSize);
	if (lower.empty()) {
		container.insert(container.end(), odd.begin(), odd.end());
		return ;
	}

	// std::cout << "Pair size: " << pairSize << std::endl;
	// std::cout << "Container:";
	// for (typename C::iterator it = container.begin(); it != container.end(); it++)
	// 	std::cout << " " << *it;
	// std::cout << std::endl;
	// std::cout << "Lower:";
	// for (typename C::iterator it = lower.begin(); it != lower.end(); it++)
	// 	std::cout << " " << *it;
	// std::cout << std::endl;
	// std::cout << "Odd:";
	// for (typename C::iterator it = odd.begin(); it != odd.end(); it++)
	// 	std::cout << " " << *it;
	// std::cout << std::endl;
	// std::cout << std::endl;

	// container.insert(container.end(), lower.begin(), lower.end());
	// container.insert(container.end(), odd.begin(), odd.end());
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

template <typename C>
C PmergeMe::popLower(C &container, size_t pairSize) {
	C rhs = pop(container, container.size() - pairSize * 2);
	C lower;

	for (size_t i = 0; !rhs.empty(); i++) {
		C &dst = (i % 2) ? container : lower;
		dst.insert(dst.end(), rhs.begin(), rhs.begin() + pairSize);
		rhs.erase(rhs.begin(), rhs.begin() + pairSize);
	}

	return (lower);
}

#endif

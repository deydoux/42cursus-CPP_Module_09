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
	lower.insert(lower.end(), odd.begin(), odd.end());
	insertLower(container, lower, pairSize);
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

template <typename C>
void PmergeMe::insertLower(C &container, C &lower, size_t pairSize) {
	size_t inserted = 1;

	for (size_t n = 2; !lower.empty(); n++) {
		size_t range = mersenne(n) * pairSize;
		size_t maxInsert = jacobsthal(n);

		size_t inserting = maxInsert - inserted + 1;
		while (inserting--) {
			if (inserting * pairSize >= lower.size())
				continue ;

			typename C::iterator pair = lower.begin() + inserting * pairSize;

			binaryInsert(container, range, pair, pairSize);
			lower.erase(pair, pair + pairSize);
		}

		inserted = maxInsert;
	}
}

template <typename C>
void PmergeMe::binaryInsert(C &container, size_t range, typename C::iterator pair, size_t pairSize) {
	if (range > container.size())
		range = container.size();

	typename C::iterator lhs = container.begin();
	typename C::iterator rhs = container.begin() + range;

	while (lhs < rhs) {
		typename C::iterator mid = lhs + ((rhs - lhs) / (2 * pairSize)) * pairSize;

		if (*(pair + pairSize - 1) < *(mid + pairSize - 1))
			rhs = mid;
		else
			lhs = mid + pairSize;
	}

	container.insert(lhs, pair, pair + pairSize);
}

#endif

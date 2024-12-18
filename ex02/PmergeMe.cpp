#include "PmergeMe.hpp"

size_t PmergeMe::jacobsthal(size_t n) {
	return ((std::pow(2, n + 1) - std::pow(-1, n)) / 3);
}

size_t PmergeMe::mersenne(size_t n) {
	return ((std::pow(2, n) - 1));
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char **input, size_t size) {
	if (size < 2) {
		std::cerr << "Error: invalid input" << std::endl;
		return ;
	}

	std::deque<long long> src;
	for (size_t i = 0; i < size; i++) {
		std::istringstream iss(input[i]);
		long long n;
		iss >> n;

		if (n < 0 || iss.fail() || !iss.eof()) {
			std::cerr << "Error: invalid input" << std::endl;
			return ;
		}

		src.push_back(n);
	}

	std::cout << "Before:";
	for (std::deque<long long>::iterator it = src.begin(); it != src.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;

	// std::pair<clock_t, clock_t> deqInterval;
	// deqInterval.first = clock();
	std::deque<long long> deqDst(src.begin(), src.end());
	algorithm(deqDst);
	// deqInterval.second = clock();

	// std::pair<clock_t, clock_t> vecInterval;
	// vecInterval.first = clock();
	// std::vector<long long> vecDst(src.begin(), src.end());
	// std::vector<long long> vecSorted = algorithm(std::vector<long long>(src.begin(), src.end()));
	// vecInterval.second = clock();

	std::cout << "After: ";
	for (std::deque<long long>::iterator it = deqDst.begin(); it != deqDst.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &) {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &) {
	return (*this);
}

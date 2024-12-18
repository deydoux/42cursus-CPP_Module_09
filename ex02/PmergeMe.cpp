#include "PmergeMe.hpp"

size_t PmergeMe::jacobsthal(size_t n) {
	return ((std::pow(2, n) - std::pow(-1, n)) / 3);
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

	clock_t deqStart = clock();
	std::deque<long long> deq(src.begin(), src.end());
	algorithm(deq);
	clock_t deqEnd = clock();

	clock_t vecStart = clock();
	std::vector<long long> vec(src.begin(), src.end());
	algorithm(vec);
	clock_t vecEnd = clock();

	std::cout << "After: ";
	for (std::deque<long long>::iterator it = deq.begin(); it != deq.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;

	double deqTime = static_cast<double>(deqEnd - deqStart) / CLOCKS_PER_SEC * 1000000;
	double vecTime = static_cast<double>(vecEnd - vecStart) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << src.size() << " elements with std::deque  : " << deqTime << " us" << std::endl;
	std::cout << "Time to process a range of " << src.size() << " elements with std::vector : " << vecTime << " us" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &) {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &) {
	return (*this);
}

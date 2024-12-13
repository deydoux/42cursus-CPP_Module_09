#include "PmergeMe.hpp"

size_t PmergeMe::jacobsthal(size_t n) {
	return ((std::pow(2, n) - std::pow(-1, n)) / 3);
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const char *input) {
	std::deque<int> src;

	std::istringstream iss(input);
	std::string token;
	while (std::getline(iss, token, ' ')) {
		if (token.empty())
			continue ;

		for (size_t i = 0; token[i]; i++) {
			if (!std::isdigit(token[i])) {
				std::cerr << "Error: invalid input" << std::endl;
				return ;
			}
		}

		std::istringstream iss(token);
		int n;
		iss >> n;
		src.push_back(n);
	}

	std::cout << "Before:";
	for (std::deque<int>::iterator it = src.begin(); it != src.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::pair<clock_t, clock_t> deqInterval;
	deqInterval.first = clock();
	std::deque<int> deqSorted = algorithm(std::deque<int>(src.begin(), src.end()));
	deqInterval.second = clock();

	std::pair<clock_t, clock_t> vecInterval;
	vecInterval.first = clock();
	std::vector<int> vecSorted = algorithm(std::vector<int>(src.begin(), src.end()));
	vecInterval.second = clock();

	std::cout << "After: ";
	for (std::deque<int>::iterator it = deqSorted.begin(); it != deqSorted.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &) {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &) {
	return (*this);
}

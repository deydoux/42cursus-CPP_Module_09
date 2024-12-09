#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <time.h>

class BitcoinExchange {
private:
	std::map<time_t, float>	_data;
public:
	BitcoinExchange();
	// BitcoinExchange(const std::string &inputFilename);
	BitcoinExchange(const BitcoinExchange &other);
	~BitcoinExchange();

	BitcoinExchange	&operator=(const BitcoinExchange &rhs);

	static time_t	parseDate(const std::string &str);
	static float	parseFloat(const std::string &str, const std::string &name);
	static float	parseExchangeRate(const std::string &str);
	static float	parseValue(const std::string &str);
};

#endif

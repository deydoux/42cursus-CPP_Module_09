#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <time.h>

class BitcoinExchange {
private:
	typedef std::map<time_t, float>	data_t;

	data_t	_data;

	static time_t	parseDate(const std::string &str);
	static float	parseFloat(const std::string &str, const std::string &name);
	static float	parseExchangeRate(const std::string &str);
	static float	parseValue(const std::string &str);

	static void		parseDataHeader(std::ifstream &file, bool &invert, std::string &delimiter);
	static data_t	parseData();
public:
	BitcoinExchange();
	BitcoinExchange(const char *inputFilename);
	BitcoinExchange(const BitcoinExchange &other);
	~BitcoinExchange();

	BitcoinExchange	&operator=(const BitcoinExchange &rhs);
};

#endif

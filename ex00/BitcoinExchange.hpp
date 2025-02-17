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

	data_t			_data;
	std::ifstream	_inputFile;
	std::string		_inputFilename;

	void	parseInputHeader(bool &invert, std::string &delimiter);
	void	handleInput(const char *filename);
	void 	processInput(time_t date, const std::string &dateStr, float value);

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

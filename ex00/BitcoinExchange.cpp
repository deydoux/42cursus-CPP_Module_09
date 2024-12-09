#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(): _data() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): _data(other._data) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	_data = rhs._data;
	return (*this);
}

time_t BitcoinExchange::parseDate(const std::string &str) {
	struct tm tm;

	char *end = strptime(str.c_str(), "%Y-%m-%d", &tm);
	if (!end || *end)
		throw (std::invalid_argument("Can't parse \"" + str + "\" date"));

	time_t time = mktime(&tm);
	if (time == -1)
		throw (std::invalid_argument("Invalid \"" + str + "\" date"));

	return (time);
}

float BitcoinExchange::parseFloat(const std::string &str, const std::string &name) {
	char *end;
	float f = std::strtod(str.c_str(), &end);
	if (!end || *end)
		throw (std::invalid_argument("Can't parse \"" + str + "\" " + name));

	return (f);
}

float BitcoinExchange::parseExchangeRate(const std::string &str) {
	return (parseFloat(str, "exchange rate"));
}

float BitcoinExchange::parseValue(const std::string &str) {
	float value = parseFloat(str, "value");
	if (0 > value || value > 10000)
		throw (std::invalid_argument("Invalid \"" + str + "\" value"));

	return (value);
}

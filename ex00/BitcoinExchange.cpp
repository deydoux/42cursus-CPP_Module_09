#include "BitcoinExchange.hpp"

time_t BitcoinExchange::parseDate(const std::string &str) {
	struct tm tm = {};

	char *end = strptime(str.c_str(), "%Y-%m-%d", &tm);
	if (!end || *end)
		throw (std::invalid_argument("Can't parse date: " + str));

	struct tm safeTm = tm;
	time_t time = mktime(&safeTm);
	if (time == -1 || safeTm.tm_mday != tm.tm_mday || safeTm.tm_mon != tm.tm_mon || safeTm.tm_year != tm.tm_year)
		throw (std::invalid_argument("Invalid date: " + str));

	return (time);
}

float BitcoinExchange::parseFloat(const std::string &str, const std::string &name) {
	char *end;
	float f = std::strtod(str.c_str(), &end);
	if (!end || *end)
		throw (std::invalid_argument("Can't parse " + name + ": " + str));

	return (f);
}

float BitcoinExchange::parseExchangeRate(const std::string &str) {
	return (parseFloat(str, "exchange rate"));
}

float BitcoinExchange::parseValue(const std::string &str) {
	float value = parseFloat(str, "value");
	if (0 > value || value > 10000)
		throw (std::invalid_argument("Invalid value: " + str));

	return (value);
}

void BitcoinExchange::parseDataHeader(std::ifstream &file, bool &invert, std::string &delimiter) {
	std::string line;
	std::getline(file, line);
	if (file.fail())
		throw (std::ios_base::failure("Failed to read file: data.csv"));

	size_t datePos = line.find("date");
	size_t exchangeRatePos = line.find("exchange_rate");
	if ((datePos && exchangeRatePos) || datePos == std::string::npos || exchangeRatePos == std::string::npos)
		throw (std::invalid_argument("Invalid header: data.csv"));

	if (!datePos) {
		invert = false;
		delimiter = line.substr(4, exchangeRatePos - 4);
	} else {
		invert = true;
		delimiter = line.substr(13, datePos - 13);
	}
}

BitcoinExchange::data_t BitcoinExchange::parseData() {
	std::ifstream file("data.csv");
	if (file.fail())
		throw (std::ios_base::failure("Failed to open file: data.csv"));

	bool invert;
	std::string delimiter;
	parseDataHeader(file, invert, delimiter);

	data_t data;

	size_t lineNum = 1;
	while (!file.eof()) {
		std::string line;
		std::getline(file, line);
		lineNum++;
		if (file.fail() || line.empty())
			break ;

		try {
			size_t pos = line.find(delimiter);
			if (pos == std::string::npos) {
				std::ostringstream oss;
				oss << "Invalid data: data.csv:" << lineNum << ": " << line;
				throw (std::invalid_argument(oss.str()));
			}

			std::string dateStr = line.substr(0, pos);
			std::string exchangeRateStr = line.substr(pos + delimiter.size());

			if (invert)
				std::swap(dateStr, exchangeRateStr);

			time_t date = parseDate(dateStr);
			float exchangeRate = parseExchangeRate(exchangeRateStr);

			data[date] = exchangeRate;
		} catch (std::exception &e) {
			std::cerr << "Data parsing error: " << e.what() << std::endl;
		}
	}
	return (data);
}

BitcoinExchange::BitcoinExchange(): _data(parseData()) {}

BitcoinExchange::BitcoinExchange(const char *inputFilename): _data(parseData()) {
	(void)inputFilename;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): _data(other._data) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	_data = rhs._data;
	return (*this);
}

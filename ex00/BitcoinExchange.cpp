#include "BitcoinExchange.hpp"

void BitcoinExchange::parseInputHeader(bool &invert, std::string &delimiter) {
	std::string line;
	std::getline(_inputFile, line);
	if (_inputFile.fail())
		throw (std::ios_base::failure("Failed to read file: " + _inputFilename));

	size_t datePos = line.find("date");
	size_t valuePos = line.find("value");
	if ((datePos && valuePos) || datePos == std::string::npos || valuePos == std::string::npos)
		throw (std::invalid_argument("Invalid header: " + _inputFilename));

	if (datePos == 0) {
		invert = false;
		delimiter = line.substr(4, valuePos - 4);
	} else {
		invert = true;
		delimiter = line.substr(5, datePos - 5);
	}
}

void BitcoinExchange::handleInput(const char *filename) {
	if (!filename)
		throw (std::invalid_argument("No input file specified"));

	_inputFilename = std::string(filename);
	_inputFile.open(filename);
	if (_inputFile.fail())
		throw (std::ios_base::failure("Failed to open file: " + _inputFilename));

	bool invert;
	std::string delimiter;
	parseInputHeader(invert, delimiter);

	size_t lineNum = 1;
	while (!_inputFile.eof()) {
		std::string line;
		std::getline(_inputFile, line);
		if (_inputFile.bad())
			throw (std::ios_base::failure("Failed to read file: " + _inputFilename));

		lineNum++;
		if (line.empty())
			continue ;

		try {
			size_t pos = line.find(delimiter);
			if (pos == std::string::npos) {
				std::ostringstream oss;
				oss << "Invalid input: " << _inputFilename << ":" << lineNum << ": " << line;
				throw (std::invalid_argument(oss.str()));
			}

			std::string dateStr = line.substr(0, pos);
			std::string valueStr = line.substr(pos + delimiter.size());
			if (invert)
				std::swap(dateStr, valueStr);

			time_t date = parseDate(dateStr);
			float value = parseValue(valueStr);
			processInput(date, dateStr, value);
		} catch (std::exception &e) {
			std::cerr << "Input error: " << e.what() << std::endl;
		}
	}
}

void BitcoinExchange::processInput(time_t date, const std::string &dateStr, float value) {
	data_t::iterator it = _data.upper_bound(date);
	if (it == _data.begin()) {
		std::cerr << "No exchange rate data for date: " << date << std::endl;
		return ;
	}
	it--;

	float exchangeRate = it->second;
	float bitcoin = value * exchangeRate;
	std::cout << value << "USD on " << dateStr << " is " << bitcoin << "BTC" << std::endl;
}

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

	if (datePos == 0) {
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
		if (file.bad())
			throw (std::ios_base::failure("Failed to read file: data.csv"));

		lineNum++;
		if (line.empty())
			continue ;

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

			if (data.find(date) != data.end())
				throw (std::invalid_argument("Duplicate date: " + dateStr));
			data[date] = exchangeRate;
		} catch (std::exception &e) {
			std::cerr << "Data error: " << e.what() << std::endl;
		}
	}
	return (data);
}

BitcoinExchange::BitcoinExchange(): _data(parseData()) {}

BitcoinExchange::BitcoinExchange(const char *inputFilename): _data(parseData()) {
	try {
		handleInput(inputFilename);
	} catch (std::exception &e) {
		std::cerr << "Input error: " << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): _data(other._data) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	_data = rhs._data;
	return (*this);
}

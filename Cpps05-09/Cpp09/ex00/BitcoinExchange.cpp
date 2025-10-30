/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:01:57 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/30 17:07:47 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::cout << GREEN << "BitcoinExchange Default Constructor Called" << RESET << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	std::cout << CYAN << "BitcoinExchange Copy Constructor Called" << RESET << std::endl;
	this->database = copy.database;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	std::cout << CYAN << "BitcoinExchange Copy Assignement Operator Called" << RESET << std::endl;
	if (this != &copy)	
	{
		this->database = copy.database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << PEACH << "BitcoinExchange Destructor Called" << RESET << std::endl;
}

bool	isValidValue(const std::string& str)
{
	if (str.empty())
		return false;

	int		dot = 0;
	bool	hasDigit = false;

	for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
	{
		if (*it == '.')
		{
			dot++;
			if (dot > 1)
				return false;
		}
		else if (std::isdigit(*it))
			hasDigit = true;
		else
			return false;
	}
	return hasDigit;
}

bool	isValidDate(const std::string& date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cerr << YELLOW << "Error: Invalid date format => " << TURQUOISE << date << RESET << std::endl;
		return false;
	}
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue; //Nao verifica os '-'
		if (!isdigit(date[i]))
		{
			std::cerr << YELLOW << "Error: Invalid date format (not all digits) => " << TURQUOISE << date << RESET << std::endl;
			return false;
		}
	}

	size_t	pos1 = date.find("-");
	size_t	pos2 = date.find("-", pos1 + 1);

	std::string	strYear = date.substr(0, pos1);
	std::string	strMonth = date.substr(pos1 + 1, pos2 - pos1 - 1);
	std::string	strDay = date.substr(pos2 + 1);
	
	if (strYear.empty() || strMonth.empty() || strDay.empty())
	{
		std::cerr << YELLOW << "Error: Invalid date (empty) => " << TURQUOISE << date << RESET << std::endl;
		return false;
	}

	int	year = std::atoi(strYear.c_str());
	int	month = std::atoi(strMonth.c_str());
	int	day = std::atoi(strDay.c_str());

	if (month < 1 || month > 12)
	{
		std::cerr << YELLOW << "Error: Invalid date (invalid month) => " << TURQUOISE << date << RESET << std::endl;
		return false;
	}

	if (year < 1900 || year > 2100)
	{
		std::cerr << YELLOW << "Error: Invalid date (invalid year) => " << TURQUOISE << date << RESET << std::endl;
		return false;
	}

	int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
	{
		std::cerr << YELLOW << "Error: Invalid date (invalid day) => " << TURQUOISE << date << RESET << std::endl;
		return false;
	}

	return true;
}

void	BitcoinExchange::loadDB(const std::string& filename) //no caso seria o data.csv
{
	std::ifstream	file(filename.c_str());
	
	if (file.fail())
	{
		throw std::runtime_error("An error ocurred when opening the database file!");
		return ;
	}
	
	int	i = 0;
	std::string	dataString;
	std::string	date;
	std::string	value;
	
	while (getline(file, dataString))
	{
		if (i > 0) //Passa a frente a primeira linha, o header
		{
			size_t comma = dataString.find(",");
			if (comma = std::string::npos)
			{
				std::cerr << YELLOW << "Error: Bad line => " << TURQUOISE << dataString << RESET << std::endl;
				continue;
			}
			date = dataString.substr(0, dataString.find(","));
			value = dataString.substr(dataString.find(",") + 1);
			if (!isValidDate(date))
				continue;
			if (!isValidValue(value))
			{
				std::cerr << YELLOW << "Error: Ivalid value => " << TURQUOISE << value << RESET << std::endl;
				continue;
			}
			this->database.insert(std::pair<std::string, float>(date, std::atof(value.c_str())));
		}
		i++;
	}
}

void	BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream
}
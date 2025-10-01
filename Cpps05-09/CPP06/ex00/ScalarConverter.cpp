/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:00:33 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/01 16:12:35 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConerter.hpp"

ScalarConverter::ScalarConverter() 
{
	std::cout << GREEN << "Scalar Converted Default Constructor Called" << RESET << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter& other) 
{
	std::cout << CYAN << "ScalarConverter Copy Constructor Called" << RESET << std::endl;
	(void)other;
}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& other)
{
	std::cout << CYAN << "ScalarConverter Copy Assignement Operator Called" << RESET << std::endl;
	(void)other;
	return *this; //TODO: tem de ter parenteses no return?
}

ScalarConverter::~ScalarConverter()
{
	std::cout << PEACH << "ScalarConverter Destructor Called" << RESET << std::endl;
}

bool	isInt(std::string literal)
{
	size_t	i = 0;

	if (literal[i] == '+' || literal[i] == '-')
		i++;
	
	for (; i < literal.size(); i++)
	{
		if (!std::isdigit(literal[i]))
			return false;
	}
	return true;
}

bool	isFloat(std::string literal)
{
	bool	hasDot = false;
	bool	hasDigit = false;
	size_t	i = 0;

	if (literal[i] == '+' || literal[i] == '-')
		i++;
	
	for (; i < literal.size(); i++)
	{
		if (std::isdigit(literal[i]))
			hasDigit = true;
		else if (literal[i] == '.' && !hasDot)
			hasDot = true;
		else if (literal[i] == '.' && hasDot)
			return false;
		else if (literal[i] == 'f' && i == literal.size() - 1)
			return hasDot && hasDigit;
		else
			return false;
	}
	return false;
}

bool	isDouble(std::string literal)
{
	bool	hasDot = false;
	bool	hasDigit = false;
	size_t	i = 0;

	if (literal[i] == '+' || literal[i] == '-')
		i++;

	for (; i < literal.size(); i++)
	{
		if (std::isdigit(literal[i]))
			hasDigit = true;
		else if (literal[i] == '.' && !hasDot)
			hasDot = true;
		else if (literal[i] == '.' && hasDot)
			return false;
		else
			return false;
	}
	return hasDigit && hasDot;
}

bool	isNanOrInf(std::string literal)
{
	if (literal == "-inf" || literal == "+inf" || literal == "nan")
		return true;
	return false;
}

int	ScalarConverter::checkType(std::string	literal)
{
	if (literal.size() == 1 && (!std::isdigit(literal[0])))
		return 0;
	else if (isInt(literal))
		return 1;
	else if (isFloat(literal))
		return 2;
	else if (isDouble(literal))
		return 3;
	else if (isNanOrInf(literal))
		return 4;
	return 5;
}

void	ScalarConverter::convert(std::string literal)
{
	ScalarConverter	sc; //TODO: mudar nome variavel	

	int		type = sc.checkType(literal);

	//-char - 0
	//-int - 1
	//-float - 2
	//-double - 3
	//nan or inf - 4
	switch (type)
	{
		case 0:
			sc.charConvert(literal);
			break;
		case 1:
			sc.intConvert(literal);
			break;
		case 2:
			sc.floatConvert(literal);
			break;
		case 3:
			sc.doubleConvert(literal);
			break;
		case 4:
			sc.nanOrInfConvert(literal);
		case 5:
			std::cout << RED << "Invalid Input!" << RESET << std::endl;
			break;
	}
}

void	ScalarConverter::charConvert(std::string literal)
{
	ScalarConverter	sc;
	
}
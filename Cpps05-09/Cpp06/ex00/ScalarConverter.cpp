/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:00:33 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/15 10:11:10 by jcavadas         ###   ########.fr       */
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
	ScalarConverter	scalar;

	int		type = scalar.checkType(literal);

	//-char - 0
	//-int - 1
	//-float - 2
	//-double - 3
	//nan or inf - 4
	switch (type)
	{
		case 0:
			scalar.charConvert(literal);
			break;
		case 1:
			scalar.intConvert(literal);
			break;
		case 2:
			scalar.floatConvert(literal);
			break;
		case 3:
			scalar.doubleConvert(literal);
			break;
		case 4:
			scalar.nanOrInfConvert(literal);
			break;
		case 5:
			std::cout << RED << "Invalid Input!" << RESET << std::endl;
			break;
	}
}

void	ScalarConverter::charConvert(std::string literal)
{	
	char	tmpC = static_cast<char>(literal[0]);

	std::cout << "char: '" << tmpC << "'" << std::endl;

	int		tmpI = static_cast<int>(literal[0]);
	std::cout << "int: " << tmpI << std::endl;
	
	float	tmpF = static_cast<float>(tmpI);
	std::cout << std::fixed << std::setprecision(1) << "float: " << tmpF << "f" << std::endl;
	
	double	tmpD = static_cast<double>(tmpI);
	std::cout << std::fixed << std::setprecision(1) << "double: " << tmpD << std::endl;
}

void	ScalarConverter::intConvert(std::string literal)
{
	int		tmpI = std::atoi(literal.c_str());
	float	tmpF = static_cast<float>(tmpI);
	double	tmpD = static_cast<double>(tmpI);
	
	/* float	tmpF = std::atof(literal.c_str());
	double	tmpD = std::strtod(literal.c_str(), NULL); */

	//str(int) to char
	if (tmpD < 32)
		std::cout  << "char: Non displayable" << std::endl;
	else if (tmpD > 127)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(tmpI) << "'" << std::endl;

	//str(int) to int
	if (tmpD > 2147483647 || tmpD < -2147483648)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(tmpI) << std::endl; //TODO nao precisa de static cast? 
	
	//str(int) to float
	std::cout << std::fixed << std::setprecision(1) << "float: " << tmpF << "f" << std::endl; //TODO fazer igual ao anterior, se deixar com o static cast meter nos outros tambem, ou entao tirar no de cima
	
	//str(int) to double
	std::cout << std::fixed << std::setprecision(1) << "double: " << tmpD << std::endl;
}

void	ScalarConverter::floatConvert(std::string literal)
{
	float	tmpF = std::atof(literal.c_str());
	int		tmpI = static_cast<int>(tmpF);
	double	tmpD = static_cast<double>(tmpF);

	//str(float) to char
	if (tmpD < 32)
		std::cout  << "char: Non displayable" << std::endl;
	else if (tmpD > 127)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(tmpI) << "'" << std::endl;

	//str(float) to int
	if (tmpD > 2147483647 || tmpD < -2147483648)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(tmpI) << std::endl; //TODO nao precisa de static cast? 
	
	//str(float) to float
	std::cout << std::fixed << std::setprecision(1) << "float: " << tmpF << "f" << std::endl; //TODO fazer igual ao anterior, se deixar com o static cast meter nos outros tambem, ou entao tirar no de cima
	
	//str(float) to double
	std::cout << std::fixed << std::setprecision(1) << "double: " << tmpD << std::endl;
}

void	ScalarConverter::doubleConvert(std::string literal)
{
	double	tmpD = std::strtod(literal.c_str(), NULL);
	int		tmpI = static_cast<int>(tmpD);
	float	tmpF = static_cast<float>(tmpD);

	//str(double) to char
	if (tmpD < 32)
		std::cout  << "char: Non displayable" << std::endl;
	else if (tmpD > 127)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(tmpI) << "'" << std::endl;

	//str(double) to int
	if (tmpD > 2147483647 || tmpD < -2147483648)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(tmpI) << std::endl; //TODO nao precisa de static cast? 
	
	//str(double) to float
	std::cout << std::fixed << std::setprecision(1) << "float: " << tmpF << "f" << std::endl; //TODO fazer igual ao anterior, se deixar com o static cast meter nos outros tambem, ou entao tirar no de cima
	
	//str(double) to double
	std::cout << std::fixed << std::setprecision(1) << "double: " << tmpD << std::endl;
}

void	ScalarConverter::nanOrInfConvert(std::string literal)
{
	double	tmpD = std::strtod(literal.c_str(), NULL);
	float	tmpF = std::atof(literal.c_str());

	//str(nanOrInf) to char
	std::cout << "char: impossible" << std::endl;

	//str(nanOrInf) to int
	std::cout << "int: impossible" << std::endl;
	
	//str(nanOrInf) to float
	std::cout << std::fixed << std::setprecision(1) << "float: " << tmpF << "f" << std::endl; //TODO fazer igual ao anterior, se deixar com o static cast meter nos outros tambem, ou entao tirar no de cima
	
	//str(nanOrInf) to double
	std::cout << std::fixed << std::setprecision(1) << "double: " << tmpD << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:00:33 by jcavadas          #+#    #+#             */
/*   Updated: 2025/09/26 19:33:03 by jcavadas         ###   ########.fr       */
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

void	ScalarConverter::convert(const std::string&	literal)
{
	ScalarConverter	sc; //TODO: mudar nome variavel	
	//TODO: CHECK TYPE
		//-char
		//-int
		//-float
		//-double
		

	//TODO: CONVERTER DEPENDENDO DO TIPO

	
}
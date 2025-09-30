/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConerter.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:00:31 by jcavadas          #+#    #+#             */
/*   Updated: 2025/09/26 19:30:23 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/// COLOURS ///
#define RESET		"\033[0m"
#define RED			"\033[38;5;160m"
#define GREEN		"\033[38;5;76m"
#define BLUE		"\033[38;5;111m"
#define YELLOW		"\033[38;5;220m"
#define MAGENTA		"\033[38;5;183m"
#define CYAN    	"\033[38;5;87m"
#define ORANGE 		"\033[38;5;208m"
#define TURQUOISE	"\033[38;5;45m"
#define PEACH		"\033[38;5;217m"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter&);
		ScalarConverter&	operator=(const ScalarConverter&); //TODO: tem de ter o nome da variavel? ex:other
		~ScalarConverter();
	public:
		static	void	convert(const	std::string	&literal);
};

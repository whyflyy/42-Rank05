/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:19:47 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/21 16:34:45 by jcavadas         ###   ########.fr       */
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

template <typename T>
class Array
{
	private:
		T	*_array;
		unsigned int	_size;
	public:
		Array();
		Array(unsigned int n);
		Array(const Array& copy);
		Array &operator=(const Array& copy);
		~Array();
		
		T&	operator[](unsigned int n);
		unsigned int size(void) const;

		class OutOfBounds : public std::exception
		{
			const char* what() const throw();
		};
};

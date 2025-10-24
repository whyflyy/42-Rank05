/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:37:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/23 15:53:51 by jcavadas         ###   ########.fr       */
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
#include <vector>
#include <algorithm>

class NoMatch : public std::exception
{
	const char* what() const throw();
};

const char* NoMatch::what() const throw()
{
	return "Error: No match found!";
}

template <typename T>
typename T::iterator easyfind(T& container, int nb)
{
	typename	T::iterator	i;
	
	i = std::find(container.begin(), container.end(), nb);

	if (i == container.end())
		throw NoMatch();
	else
		return std::find(container.begin(), container.end(), nb);
}

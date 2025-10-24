/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:05:43 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/24 15:21:23 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() : _N(0)
{
	std::cout << GREEN << "Span Default Constructor Called" << RESET << std::endl;
}

Span::Span(unsigned int n) : _N(n)
{
	std::cout << GREEN << "Span Numbered Constructor Called" << RESET << std::endl;
}

Span::Span(const Span &copy)
{
	std::cout << CYAN << "Span Copy Constructor Called" << RESET << std::endl;
	_N = copy._N;
	_vec = copy._vec;
}

Span&	Span::operator=(const Span &copy)
{
	std::cout << CYAN << "Span Copy Assignement Operator Called" << RESET << std::endl;
	if (this != &copy)	
	{
		_N = copy._N;
		_vec = copy._vec;
	}
	return *this;
}

Span::~Span()
{
	std::cout << PEACH << "Span Destructor Called" << RESET << std::endl;
}

void	Span::addNumber(int num)
{
	if (_vec.size() == _N)
		throw AlreadyFull();
	_vec.push_back(num);
}

int		Span::shortestSpan()
{
	if (_N < 2)
		throw EmptySpan();

	std::vector<int>	orgVec = _vec;
	std::sort(orgVec.begin(), orgVec.end());

	int	minSpan = std::numeric_limits<int>::max();
	int	span;
	
	for (size_t i = 1; i < orgVec.size(); i++)
	{
		span = (orgVec[i] - orgVec[i - 1]);
		if (minSpan > span)
			minSpan = span;
	}
	return minSpan;
}

int		Span::longestSpan()
{
	if (_N < 2)
		throw EmptySpan();
	
	
}


class	AlreadyFull : public std::exception
{
	const char* what() const throw();
};

class	EmptySpan : public std::exception
{
	const char* what() const throw();	
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:26:24 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/06 16:21:53 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
	std::cout << GREEN << "RPN Default Constructor Called" << RESET << std::endl;
}

RPN::RPN(const RPN &copy)
{
	std::cout << CYAN << "RPN Copy Constructor Called" << RESET << std::endl;
	this->_stack = copy._stack;
}

RPN&	RPN::operator=(const RPN &copy)
{
	std::cout << CYAN << "RPN Copy Assignement Operator Called" << RESET << std::endl;
	if (this != &copy)	
	{
		this->_stack = copy._stack;
	}
	return *this;
}

RPN::~RPN()
{
	std::cout << PEACH << "RPN Destructor Called" << RESET << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:26:24 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/12 15:35:08 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>

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

bool	isValidNumber(std::string token)
{
	if (token.size() > 1)
		throw std::runtime_error("The number inserted can only have 1 digit!");
	if (std::isdigit(token[0]))
		return true;
	else
		return false;
}

bool	isValidOperator(std::string token)
{
	if (token.size() > 1)
		throw std::runtime_error("Operator syntax error!"); //Should never reach here since it does the same check before in isValidNumber
	if (token == "+" || token == "-" || token == "/" || token == "*")
		return true;
	else
		return false;
}

void	RPN::calculate(std::string input)
{
	std::istringstream	split(input);
	std::string	token;
	long	num;

	if (input.empty() || std::find_if(input.begin(), input.end(), std::not1(std::ptr_fun<int, int>(std::isspace))) == input.end())
		throw std::runtime_error("Empty argument!");

	while (split >> token)
	{
		if (isValidNumber(token))
		{
			num = std::atol(token.c_str());
			_stack.push(num);
		}
		else if (isValidOperator(token))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("There are not suficient numbers in the stack to use an operator");
			
			long	numB = _stack.top();
			_stack.pop();
			long	numA = _stack.top();
			_stack.pop();
			long	result = 0;

			if (token == "+")
			{
				result = numA + numB;
				if (result > MAXINT || result < MININT)
					throw std::runtime_error("Result overflow!");
			}
			else if (token == "-")
			{
				result = numA - numB;
				if (result > MAXINT || result < MININT)
					throw std::runtime_error("Result overflow!");
			}
			else if (token == "/")
			{
				if (numB == 0)
					throw std::runtime_error("Can't divide by zero!");
				result = numA / numB;
				if (result > MAXINT || result < MININT)
					throw std::runtime_error("Result overflow!");
			}
			else if (token == "*")
			{
				result = numA * numB;
				if (result > MAXINT || result < MININT)
					throw std::runtime_error("Result overflow!");
			}

			_stack.push(result);
		}
		else
			throw std::runtime_error("Input must be only numbers or valid operators!");
	}
	if (_stack.size() > 1)
		throw std::runtime_error("Something went wrong!");
	std::cout << CYAN << "Result: " << MAGENTA << _stack.top() << RESET << std::endl;
}

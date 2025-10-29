/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:44:35 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/28 13:51:03 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"


template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>()
{
	std::cout << GREEN << "MutantStack Default Constructor Called" << RESET << std::endl;
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack& copy)
{
	std::cout << CYAN << "MutantStack Copy constructor called" << RESET << std::endl;
	*this = copy;
}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack& copy)
{
	std::cout << MAGENTA << "MutantStack Copy assignment operator called" << RESET << std::endl;
	if (this != &copy)
	{
		std::stack<T>::operator=(copy);
	}
	return *this;
}

template <typename T>
MutantStack<T>::~MutantStack()
{
	std::cout << RED << "MutantStack Destrutcor Called" << RESET << std::endl;
}

template <typename T>
typename	MutantStack<T>::iterator	MutantStack<T>::begin()
{
	return this->c.begin();	
}

template <typename T>
typename	MutantStack<T>::iterator	MutantStack<T>::end()
{
	return this->c.end();	
}

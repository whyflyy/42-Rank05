/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:25:43 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/21 17:10:23 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
Array<T>::Array() : _array(new T[0]), _size(0)
{
	std::cout << GREEN << "Array Default Constructor Called" << RESET << std::endl;
}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n)
{
	std::cout << GREEN << "Array numbered Constructor Called" << RESET << std::endl;
}

template <typename T>
Array<T>::Array(const Array& copy) : _array(new T[copy._size]), _size(copy._size)
{
	std::cout << CYAN << "Array Copy constructor called" << RESET << std::endl;
	for (unsigned int i = 0; i < _size; i++)
		this->_array[i] = copy._array[i];
}

template <typename T>
Array<T> &Array<T>::operator=(const Array& copy)
{
	std::cout << MAGENTA << "Array Copy assignment operator called" << RESET << std::endl;
	if (this != &copy)
	{
		delete[] this->_array;
		_size = copy._size;
		
		if (_size > 0)
		{
			_array = new T[_size];
			for (unsigned int i = 0; i < _size; i++)
				_array[i] = copy._array[i];
		}
		else
			_array = NULL;
	}
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	std::cout << RED << "Array Destrutcor Called" << RESET << std::endl;
	delete[] this->_array;
}

template <typename T>
T& Array<T>::operator[](unsigned int n)
{
	if (n >= _size)
		throw OutOfBounds();
	return _array[n];
}

template <typename T>
unsigned int Array<T>::size(void) const
{
	return _size;
}

template <typename T>
const char* Array<T>::OutOfBounds::what() const throw()
{
	return "Index out of bounds";
}
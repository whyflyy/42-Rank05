/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:47:06 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/15 13:31:57 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() 
{
	std::cout << GREEN << "Serializer Default Constructor Called" << RESET << std::endl;
}

Serializer::Serializer(const Serializer &copy) 
{
	std::cout << CYAN << "Serializer Copy Constructor Called" << RESET << std::endl;
	(void)copy;
}

Serializer&	Serializer::operator=(const Serializer &copy)
{
	std::cout << CYAN << "Serializer Copy Assignement Operator Called" << RESET << std::endl;
	(void)copy;
	return *this;
}

Serializer::~Serializer()
{
	std::cout << PEACH << "Serializer Destructor Called" << RESET << std::endl;
}

uintptr_t	Serializer::serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data*	Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

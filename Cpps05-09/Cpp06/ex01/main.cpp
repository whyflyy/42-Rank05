/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:45:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/15 13:39:47 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main()
{
	//Serializer s; -> can't be initialized
	Data	data;
	data.age = 42;
	data.name = "Joao";

	std::cout << YELLOW << "Data pointer: " << PEACH << &data << RESET << std::endl << std::endl;
	
	uintptr_t	raw = Serializer::serialize(&data);
	std::cout << YELLOW << "Serialized value: " << MAGENTA << raw << RESET <<std::endl << std::endl;

	Data*	deserialized = Serializer::deserialize(raw);
	std::cout << YELLOW << "Deserialized value: " << PEACH << deserialized << RESET << std::endl << std::endl;

	if (deserialized == &data)
		std::cout << GREEN << "Serialization worked!" << RESET << std::endl << std::endl;
	else
		std::cout << RED << "Serialization failed!" << RESET << std::endl << std::endl;
		
	std::cout << "Age: " << deserialized->age << ", Name: " << deserialized->name << std::endl;
}
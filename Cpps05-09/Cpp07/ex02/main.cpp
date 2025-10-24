/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:20:33 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/22 12:00:48 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.tpp"
#include <iostream>

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int	main(void)
{
	std::cout << SEPARATOR << "Int Array" << SEPARATOR << std::endl;
	try
	{
		Array<int>	intArray(10);
		
		for (unsigned int i = 0; i < intArray.size(); i++)
			std::cout << intArray[i] << " ";
		std::cout << std::endl;
		std::cout << "Array Size: " << intArray.size() << std::endl;
		std::cout << "Trying to go out of bounds" << std::endl;
		std::cout << intArray[10] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	
	wait_for_enter();

		std::cout << SEPARATOR << "String Array" << SEPARATOR << std::endl;
	try
	{
		Array<std::string>	strArray(50);
		
		for (unsigned int i = 0; i < strArray.size(); i++)
			std::cout << strArray[i] << " ";
		std::cout << std::endl;
		std::cout << "Array Size: " << strArray.size() << std::endl;
		//strArray[10] = "Hello!";
		//std::cout << strArray[10] << std::endl;
		std::cout << "Trying to go out of bounds" << std::endl;
		std::cout << strArray[100] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	
}
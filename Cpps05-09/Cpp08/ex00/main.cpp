/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:37:48 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/23 15:59:47 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int	main(void)
{
	std::vector<int>	vec;
	
	for (int i = 0; i <= 10; i++)
		vec.push_back(i);

	std::cout << SEPARATOR << MAGENTA << "Vector: " << SEPARATOR << RESET << std::endl;
	for (int i = 0; i <= 10; i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl << std::endl;

	try
	{
		std::vector<int>::iterator	it = easyfind(vec, 2);
		std::cout << YELLOW << "Found: " << CYAN << *it << YELLOW << "!" << RESET << std::endl;
		std::cout << std::endl << std::endl;

		std::cout << PEACH << "Trying to find a number not in vector!"<< RESET << std::endl;
		std::vector<int>::iterator	it2 = easyfind(vec, 42);
		std::cout << YELLOW << "Found: " << CYAN << *it2 << YELLOW << "!" << RESET << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	
}
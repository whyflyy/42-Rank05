/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:57:58 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/21 15:23:45 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

void	increment(int &nb)
{
	nb += 1;
}

void	print(int &n)
{
	std::cout << n << std::endl;
}

int	main(void)
{
	int		intArray[] = {1, 2, 3 ,4, 5};
	int		charArray[] = {'a', 'b', 'c', 'd', 'f'};


	std::cout << SEPARATOR << "Int Array" << SEPARATOR <<std::endl;
	
	std::cout << CYAN << "Before Increment" << RESET << std::endl;
	iter(intArray, 5, print);
	std::cout << std::endl;
	iter(intArray, 5, increment);
	std::cout << CYAN << "After Increment" << RESET << std::endl;
	iter(intArray, 5, print);

	wait_for_enter();

	std::cout << SEPARATOR << "Char Array" << SEPARATOR <<std::endl;
	
	std::cout << CYAN << "Before Increment" << RESET << std::endl;
	iter(charArray, 5, print);
	std::cout << std::endl;
	iter(charArray, 5, increment);
	std::cout << CYAN << "After Increment" << RESET << std::endl;
	iter(charArray, 5, print);
}
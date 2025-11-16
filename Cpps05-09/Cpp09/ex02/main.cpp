/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:39:42 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/15 18:16:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter()
{
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

void	checkIfNumber(std::string str)
{
	std::string::const_iterator	it = str.begin();
	for (; it != str.end(); it++)
	{
		if (!std::isdigit(*it))
			throw std::runtime_error("Error: non-numeric argument => " + str);
	}
}

void	validateArgs(int ac, char **av)
{
	int			i = 1;
	std::string	str;

	i = 1;
	while (i < ac)
	{
		str = std::string(av[i]);
		
		if (str.empty())
			throw std::runtime_error("Error: Empty Argument!");

		checkIfNumber(str);
		
		i++;
	}
}

int	main(int ac, char **av)
{
	PmergeMe	merger;
	if (ac < 2)
	{
		std::cout << YELLOW << "Incorrect usage! Must be used as ./PmergeMe <numbers>" << RESET << std::endl;
		return 1;
	}
	try
	{
		validateArgs(ac, av);
		merger.argToVec(ac, av);
		merger.argToDeq(ac, av);

		//TODO: Print do av before orgarnizar?

		//TODO: clock para contar tempo para organizar

		//-----------------Vector--------------------//
		wait_for_enter();
		std::cout << SEPARATOR << MAGENTA << "Vector: " << SEPARATOR << RESET << std::endl;
		merger.organizeVec();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}
	
	return 0;
}
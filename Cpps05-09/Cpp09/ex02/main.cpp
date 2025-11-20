/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:39:42 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/20 17:09:53 by jcavadas         ###   ########.fr       */
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

void printBefore(int ac, char **av)
{
	std::cout << YELLOW << "Before: " << RESET;
	for (int i = 1; i < ac; i++)
	{
		std::cout << av[i] << " ";
	}
	std::cout << "\n";
	
}

void printAfter(PmergeMe &merger, int option)
{
	switch (option)
	{
		case 1 :
			std::cout << GREEN << "After: " << RESET ;
			merger.printOrgVector();
			break;
		/* case 2 :
			std::cout << GREEN << "After: " << RESET ;
			merger.printDeque(merger.getOrganizedDeque());
			break; */
	}
}

void printTimer(std::clock_t start, std::clock_t end, int ac, int option)
{
	double finalTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	switch (option)
	{
	case 1:
		std::cout << "Time to process a range of " << MAGENTA << ac - 1 << RESET
			<< " elements with " << CYAN << "std::vector: " << PEACH << std::fixed << std::setprecision(5) << finalTime << RESET << " us" << "\n";
		break;
	case 2:
		std::cout << "Time to process a range of " << MAGENTA << ac - 1 << RESET
			<< " elements with " << CYAN << "std::deque: " << PEACH << std::fixed << std::setprecision(5) << finalTime << RESET << " us" << "\n";
		break;
	}
}

//TODO procurar maneira melhor de gerar random numeros?
//shuf -i 1-10000000 -n 5000 | tr '\n' ' ' | xargs ./PmergeMe

int	main(int ac, char **av)
{
	PmergeMe	merger;
	if (ac < 2)
	{
		std::cout << YELLOW << "Incorrect usage! Must be used as ./PmergeMe <merger>" << RESET << std::endl;
		return 1;
	}
	try
	{
		validateArgs(ac, av);
		merger.argToVec(ac, av);
		merger.argToDeq(ac, av);

		std::cout << std::endl;
		printBefore(ac, av);

		std::clock_t	startTime;
		std::clock_t	endTime;

		//-----------------Vector--------------------//
		//std::cout << SEPARATOR << MAGENTA << "Vector: " << SEPARATOR << RESET << std::endl;
		startTime = std::clock();
		merger.organizeVec();
		endTime = std::clock();
		
		printAfter(merger, 1);
		printTimer(startTime, endTime, ac, 1);
		
		std::cout << std::endl;

		//TODO DEQUE
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}
	
	return 0;
}
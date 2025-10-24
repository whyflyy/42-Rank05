/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:05:41 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/24 21:14:56 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int main(void)
{
	std::srand(static_cast<unsigned>(std::time(NULL)));

	try
	{
		std::cout << SEPARATOR << MAGENTA << "Test Creating/Adding to vector" << RESET << SEPARATOR << std::endl;
		Span	empty(0);		   
		Span	s(10);

		std::cout << std::endl;

		s.addNumber(1);
		s.addNumber(14);
		s.addNumber(42);
		s.addNumber(35);
		s.addNumber(68);
		s.addNumber(29);
		s.addNumber(55);
		s.addNumber(67);
		s.addNumber(76);
		s.addNumber(44);

		std::cout << YELLOW << "Shortest span: " << CYAN << s.shortestSpan() << RESET << std::endl;
		std::cout << YELLOW << "Longest span: " << CYAN << s.longestSpan() << RESET << std::endl;
		std::cout << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}
	
	wait_for_enter();

	try
	{
		std::cout << SEPARATOR << MAGENTA << "Exception tests - Adding over the vec limit" << RESET << SEPARATOR << std::endl;
		Span	sp(2);

		std::cout << std::endl;

		sp.addNumber(1);
		sp.addNumber(2);

		std::cout << "Trying to add another one: " << std::endl;
		sp.addNumber(3);
	}
	catch(const std::exception& e)
	{
		std::cout << std::endl;
		std::cerr << RED << e.what() << RESET << '\n';
	}
	
	wait_for_enter();
	
	try
	{
		std::cout << SEPARATOR << MAGENTA << "Exception tests - Empty Vector" << RESET << SEPARATOR << std::endl;
		Span	empty(2);
		std::cout << std::endl;

		empty.shortestSpan();
	}
	catch(const std::exception& e)
	{
		std::cout << std::endl;
		std::cerr << RED << e.what() << RESET << '\n';
	}

	wait_for_enter();

	try
	{
		std::cout << SEPARATOR << MAGENTA << "Exception tests - Single Element Vector" << RESET << SEPARATOR << std::endl;
		Span	single(2);
		std::cout << std::endl;

		single.addNumber(1);		
		single.shortestSpan();
	}
	catch(const std::exception& e)
	{
		std::cout << std::endl;
		std::cerr << RED << e.what() << RESET << '\n';
	}

	wait_for_enter();

	try
	{
		std::cout << SEPARATOR << MAGENTA << "Random 10,000 numbers" << RESET << SEPARATOR << std::endl;
		unsigned int	N = 10000;
		Span	big(N);
		std::cout << std::endl;

		for (unsigned int i = 0; i < N; i++)
			big.addNumber(std::rand() % 1000000); // Random numbers between 0 and 999999

		std::cout << YELLOW << "Shortest span: " << CYAN << big.shortestSpan() << RESET << std::endl;
		std::cout << YELLOW << "Longest span: " << CYAN << big.longestSpan() << RESET << std::endl;
		std::cout << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}
}

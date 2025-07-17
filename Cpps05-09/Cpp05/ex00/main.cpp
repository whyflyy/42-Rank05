/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:19:41 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/15 19:09:49 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int main(void)
{
	std::cout << SEPARATOR << "Exceptions" << SEPARATOR;
	std::cout << YELLOW << "Too Low" << RESET << std::endl;
	try
	{
		Bureaucrat Beatriz("Beatriz", 500);
		//Trying to use Beatriz values
		std::cout << Beatriz.getGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << '\n' << RESET;
	}
	
	std::cout << std::endl << YELLOW << "Too High" << RESET << std::endl;
	try
	{
		Bureaucrat Bernardo("Bernardo", 0);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << '\n' << RESET;
	}

	std::cout << std::endl << YELLOW << "Negative Grade" << RESET << std::endl;
	try
	{
		Bureaucrat Jorge("Jorge", -5);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << '\n' << RESET;
	}
	
	wait_for_enter();

	std::cout << SEPARATOR << "Increment and Decrement" << SEPARATOR;
	std::cout << YELLOW << "Increment Grade" << RESET << std::endl;
	try
	{
		Bureaucrat Barnabe("Barnabe", 2);
		std::cout << Barnabe;
		Barnabe.incrementGrade();
		std::cout << Barnabe;
		Barnabe.incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << '\n' << RESET;
	}

	std::cout << std::endl << YELLOW << "Decrement Grade" << RESET << std::endl;
	try
	{
		Bureaucrat Barnabe("Barnabe", 149);
		std::cout << Barnabe;
		Barnabe.decrementGrade();
		std::cout << Barnabe;
		Barnabe.decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << '\n' << RESET;
	}

	std::cout << std::endl << YELLOW << "Overload testing" << RESET << std::endl;
	Bureaucrat Barnabe("Barnabe",1);
	std::cout << Barnabe;
}

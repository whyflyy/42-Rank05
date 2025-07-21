/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:47:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 14:27:59 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int	main()
{
	std::cout << std::endl << SEPARATOR << "Succesefull Cases" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Boss("Boss", 1);
		ShrubberyCreationForm	Shrub("Garden");
		RobotomyRequestForm		Robot("Bender");
		PresidentialPardonForm	Pardon("Patricia");
		
		std::cout << std::endl << std::endl << std::endl;

		Boss.signForm(Shrub);
		Boss.executeForm(Shrub);
		std::cout << std::endl;
		
		Boss.signForm(Robot);
		Boss.executeForm(Robot);
		std::cout << std::endl;
		
		Boss.signForm(Pardon);
		Boss.executeForm(Pardon);
		
		std::cout << std::endl << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	wait_for_enter();
	

	std::cout << std::endl << SEPARATOR << "Execute without Signing" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Boss("Boss", 1);
		ShrubberyCreationForm	Shrub("Garden");
		RobotomyRequestForm		Robot("Bender");
		PresidentialPardonForm	Pardon("Patricia");

		std::cout << std::endl << std::endl << std::endl;

		Boss.executeForm(Shrub);
		std::cout << std::endl;
		
		Boss.executeForm(Robot);
		std::cout << std::endl;
		
		Boss.executeForm(Pardon);
		
		std::cout << std::endl << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	wait_for_enter();

	std::cout << std::endl << SEPARATOR << "Sign with low grade" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Intern("Intern", 150);
		ShrubberyCreationForm	Shrub("Garden");
		RobotomyRequestForm		Robot("Bender");
		PresidentialPardonForm	Pardon("Patricia");

		std::cout << std::endl << std::endl << std::endl;

		Intern.signForm(Shrub);
		std::cout << std::endl;
		
		Intern.signForm(Robot);
		std::cout << std::endl;
		
		Intern.signForm(Pardon);
		
		std::cout << std::endl << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	wait_for_enter();

	std::cout << std::endl << SEPARATOR << "Execute with low grade" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Peasant("Peasant", 145);
		ShrubberyCreationForm	Shrub("Garden");

		std::cout << std::endl << std::endl << std::endl;
		
		Peasant.signForm(Shrub);
		Peasant.executeForm(Shrub);
		
		std::cout << std::endl << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	wait_for_enter();

	std::cout << std::endl << SEPARATOR << "Already signed form" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Brocrat("Brocrat", 1);
		ShrubberyCreationForm	Shrub("Garden");

		std::cout << std::endl << std::endl << std::endl;
		
		Brocrat.signForm(Shrub);
		Brocrat.signForm(Shrub);
		
		std::cout << std::endl << std::endl << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	wait_for_enter();	
}

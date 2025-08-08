/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:47:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/08/05 15:40:01 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int	main(void)
{
	Intern	Inter;
	AForm*	form;
	
	std::cout << std::endl << SEPARATOR << "Valid Form Creation" << SEPARATOR << std::endl;

	form = Inter.makeForm("shrubbery request", "Backyard");
	if (form)
	{
		Bureaucrat	Bro("Bro", 137);
		Bro.signForm(*form);
		Bro.executeForm(*form);
		delete form;
	}

	wait_for_enter();

	form = Inter.makeForm("robotomy request", "Bender");
	if (form)
	{
		Bureaucrat	Bro("Bro", 45);
		Bro.signForm(*form);
		Bro.executeForm(*form);
		delete form;
	}
	
	wait_for_enter();

	form = Inter.makeForm("presidential request", "Morty");
	if (form)
	{
		Bureaucrat	Bro("Bro", 5);
		Bro.signForm(*form);
		Bro.executeForm(*form);
		delete form;
	}

	wait_for_enter();

	std::cout << std::endl << SEPARATOR << "Invalid Form Creation" << SEPARATOR << std::endl;

	form = Inter.makeForm("Ooga Booga", "Bingus Bangus");	

	return (0);
}

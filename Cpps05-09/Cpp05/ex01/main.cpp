/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:42:49 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 12:48:12 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int	main(void)
{

	std::cout << std::endl << SEPARATOR << "Invalid form creation" << SEPARATOR << std::endl;
	
	try
	{
		Form	Invalid("Invalid", 0, 10);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
		
	try
	{
		Form	InvalidToo("InvalidToo", 10, 151);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	try
	{
		Form	InvalidThree("InvalidThree", -10, -150);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}

	wait_for_enter();

	std::cout << SEPARATOR << "Successful form signing" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Bro("Bro", 50);
		Form		Taxes("Taxes", 75, 50);

		std::cout << Taxes << std::endl;
		Bro.signForm(Taxes);
		std::cout << Taxes << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
		wait_for_enter();

	std::cout << std::endl << SEPARATOR << "Increment Bureaucrat grade and sign" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Bailey("Bailey", 150);
		Form		HospitalForms("Hospital Forms", 149, 149);

		std::cout << HospitalForms << std::endl;
		Bailey.signForm(HospitalForms);
		std::cout << HospitalForms << std::endl;
		Bailey.incrementGrade();
		Bailey.signForm(HospitalForms);
		std::cout << HospitalForms << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	wait_for_enter();

	std::cout << std::endl << SEPARATOR << "Grade too low to sign" << SEPARATOR << std::endl;

	try
	{
		Bureaucrat	Bob("Bob", 100);
		Form		Secrets("Secrets", 50, 10);

		std::cout << Secrets << std::endl;
		Bob.signForm(Secrets);
		std::cout << Secrets << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	wait_for_enter();

	std::cout << std::endl << SEPARATOR << "Form already signed" << SEPARATOR << std::endl;
	
	try
	{
		Bureaucrat	Billie("Billie", 10);
		Form		NDA("NDA", 20, 10);

		std::cout << NDA << std::endl;
		Billie.signForm(NDA);
		Billie.signForm(NDA);
		std::cout << NDA << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}

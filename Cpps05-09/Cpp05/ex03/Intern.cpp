/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:19:28 by jcavadas          #+#    #+#             */
/*   Updated: 2025/08/05 15:31:59 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

//Orthodox Canonical Intern
//Default Constructor
Intern::Intern()
{
	std::cout << GREEN << "Intern Default Constructor Called" << RESET << std::endl;
}

//Copy Constructor
Intern::Intern(const Intern &copy) 
{
	(void)copy;
	std::cout << CYAN << "Intern Copy constructor called" << RESET << std::endl;
}
//Copy assignement operator overload
Intern &Intern::operator=(const Intern &copy)
{
	std::cout << MAGENTA << "Intern Copy assignment operator called" << RESET << std::endl;
	(void)copy;
	return (*this);
}
//Destructor
Intern::~Intern()
{
	std::cout << RED << "Intern Destrutcor Called" << RESET << std::endl;
}

//Member functions
AForm	*Intern::makeShrubbery(std::string target)
{
	return	new ShrubberyCreationForm(target);
}

AForm	*Intern::makeRobotomy(std::string target)
{
	return	new RobotomyRequestForm(target);
}

AForm	*Intern::makePresidential(std::string target)
{
	return	new PresidentialPardonForm(target);
}

AForm	*Intern::makeForm(const std::string formName, const std::string target)
{
	const std::string	formTypes[3] = {"shrubbery request", \
										"robotomy request", \
										"presidential request"};
	AForm	*(Intern::*forms[])(const std::string) = {
		&Intern::makeShrubbery,
		&Intern::makeRobotomy,
		&Intern::makePresidential};

	for (int i = 0; i < 3; i++)
	{
		if (formTypes[i] == formName)
		{
			AForm	*tempForm = (this->*forms[i])(target);
			std::cout << GREEN << "Intern Created " \
				<< MAGENTA << tempForm->getName() << RESET << std::endl;
			return (tempForm);
		}
	}
	std::cout << RED << "No matching form name was found!" << RESET << std::endl;
	return (NULL);
}


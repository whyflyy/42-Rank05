/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:07:27 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 12:22:27 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

//Constructor
RobotomyRequestForm::RobotomyRequestForm() : AForm("Robotomy", 72, 45, "Default")
{
	std::cout << GREEN << "RobotomyRequestForm Default Constructor Called" << RESET << std::endl;
}
//Named Constructor
RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("Robotomy", 72, 45, target)
{
	std::cout << GREEN << "RobotomyRequestForm Target Constructor Called" << RESET << std::endl;
}

//Copy Constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &copy) : AForm(copy)
{
	std::cout << CYAN << "RobotomyRequestForm Copy constructor called" << RESET << std::endl;
	*this = copy;
}
//Copy assignement operator overload
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &copy)
{
	std::cout << MAGENTA << "RobotomyRequestForm Copy assignment operator called" << RESET << std::endl;
	(void)copy;
	return (*this);
}

//Destructor
RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << RED << "RobotomyRequestForm Destrutcor Called" << RESET << std::endl;
}

//Member functions
void	RobotomyRequestForm::executor() const
{
	std::srand((unsigned) time(NULL));
	int random = std::rand() % 2;

	std::cout << std::endl << YELLOW << "*VVRRRRRRRRRRR*" << RESET << std::endl;
	if (random == 1)
		std::cout << PEACH << this->getTarget() << BLUE << " has been robotomized!" << RESET << std::endl;
	else
		std::cout << PEACH << this->getTarget() << RED << "'s robotomization has failed!" << RESET << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:52:54 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 12:27:41 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

//Constructor
PresidentialPardonForm::PresidentialPardonForm() : AForm("Presidential", 25, 5, "Default")
{
	std::cout << GREEN << "PresidentialPardonForm Default Constructor Called" << RESET << std::endl;
}
//Named Constructor
PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("Presidential", 25, 5, target)
{
	std::cout << GREEN << "PresidentialPardonForm Target Constructor Called" << RESET << std::endl;
}

//Copy Constructor
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &copy) : AForm(copy)
{
	std::cout << CYAN << "PresidentialPardonForm Copy constructor called" << RESET << std::endl;
	*this = copy;
}
//Copy assignement operator overload
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &copy)
{
	std::cout << MAGENTA << "PresidentialPardonForm Copy assignment operator called" << RESET << std::endl;
	(void)copy;
	return (*this);
}

//Destructor
PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << RED << "PresidentialPardonForm Destrutcor Called" << RESET << std::endl;
}

//Member functions
void	PresidentialPardonForm::executor() const
{
	std::cout << PEACH << this->getTarget() << BLUE << " has been pardoned by Zaphod Beeblebrox." << RESET << std::endl;
}

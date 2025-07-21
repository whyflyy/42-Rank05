/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:23:11 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 12:36:10 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

//Constructor
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Shrubbery", 145, 137, "Default")
{
	std::cout << GREEN << "ShrubberyCreationForm Default Constructor Called" << RESET << std::endl;
}
//Named Constructor
ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("Shrubbery", 145, 137, target)
{
	std::cout << GREEN << "ShrubberyCreationForm Target Constructor Called" << RESET << std::endl;
}

//Copy Constructor
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &copy) : AForm(copy)
{
	std::cout << CYAN << "ShrubberyCreationForm Copy constructor called" << RESET << std::endl;
	*this = copy;
}
//Copy assignement operator overload
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &copy)
{
	std::cout << MAGENTA << "ShrubberyCreationForm Copy assignment operator called" << RESET << std::endl;
	(void)copy;
	return (*this);
}

//Destructor
ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << RED << "ShrubberyCreationForm Destrutcor Called" << RESET << std::endl;
}

//Member functions
void	ShrubberyCreationForm::executor() const
{
	std::string	fileName = (this->getTarget() + "_shrubbery");
	std::ofstream	outFile(fileName.c_str());
	
	if (outFile.fail())
	{
		std::cout << RED << "Error creating shrubbery file!" << RESET << std::endl;
		return ;
	}
	else
	{
		outFile << "    /\\    \n";
		outFile << "   /**\\   \n";
		outFile << "  /****\\  \n";
		outFile << " /******\\ \n";
		outFile << "/********\\\n";
		outFile << "   |||    \n";
		outFile << "   |||    \n";
		outFile << "\n";
		outFile << "    /\\    \n";
		outFile << "   /**\\   \n";
		outFile << "  /****\\  \n";
		outFile << " /******\\ \n";
		outFile << "/********\\\n";
		outFile << "   |||    \n";
		outFile << "   |||    \n";
		outFile.close();
		std::cout << PEACH << fileName << GREEN << " has been created!" << RESET << std::endl;
	}
}

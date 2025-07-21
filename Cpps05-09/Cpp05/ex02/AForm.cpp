/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:07 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 10:53:54 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

//Orthodox Canonical AForm
//Default Constructor
AForm::AForm() : _name("Default"), _signGrade(150), _execGrade(150), _target("default")
{
	std::cout << GREEN << "AForm Default Constructor Called" << RESET << std::endl;
	this->_signed = false;
}
//Named Constructor
AForm::AForm(std::string name, int gradeToSign, int gradeToExec, std::string target) 
	: _name(name), _signGrade(gradeToSign), _execGrade(gradeToExec), _target(target)
{
	std::cout << GREEN << "AForm Named Constructor Called" << RESET << std::endl;
	if (gradeToSign == 0 || gradeToExec == 0)
		throw GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExec > 150)
		throw GradeTooLowException();
	else if (gradeToSign < 0 || gradeToExec < 0)
		throw GradeIsNegative();
	else
		this->_signed = false;
}
//Copy Constructor
AForm::AForm(const AForm &copy) 
	: _name(copy._name), _signGrade(copy._signGrade), _execGrade(copy._execGrade), _target(copy._target)
{
	std::cout << CYAN << "AForm Copy constructor called" << RESET << std::endl;
	this->_signed = copy._signed;
}
//Copy assignement operator overload
AForm &AForm::operator=(const AForm &copy)
{
	std::cout << MAGENTA << "AForm Copy assignment operator called" << RESET << std::endl;
	if (this != &copy)
	{
		this->_signed = copy._signed;
	}
	return (*this);
}
//Destructor
AForm::~AForm()
{
	std::cout << RED << "AForm Destrutcor Called" << RESET << std::endl;
}

//Member functions
void		AForm::beSigned(Bureaucrat &Signer)
{
	std::cout << CYAN << Signer.getName() << RESET << " is trying to sign AForm " \
		<< PEACH << this->getName() << RESET << std::endl;
	if (this->_signGrade < Signer.getGrade())
		throw (GradeTooLowException());
	else if (this->_signed == true)
	{
		std::cout << PEACH << this->getName() << RED << " is already signed!" << RESET << std::endl;
		return ;
	}
	else
	{
		std::cout << CYAN << Signer.getName() << GREEN << " signed " \
			<< PEACH << this->getName() << RESET << std::endl;
		this->_signed = true;
	}
}

void		AForm::execute(Bureaucrat const &bureaucrat) const
{
	if (bureaucrat.getGrade() > this->getExecGrade())
		throw (GradeTooLowException());
	else
	{
		if (this->getIsSigned() == true)
			this->executor();
		else
			std::cout << PEACH << this->getName() << RED << " is not signed!" << RESET << std::endl;
	}
	
}

//Getters
std::string	AForm::getName() const
{
	return (this->_name);
}

bool		AForm::getIsSigned() const
{
	return (this->_signed);
}

std::string	AForm::getSignedString() const
{
	if (this->getIsSigned() == true)
		return ("True");
	else
		return ("False");
}

int			AForm::getSignGrade() const
{
	return (this->_signGrade);
}

int			AForm::getExecGrade() const
{
	return (this->_execGrade);
}

std::string	AForm::getTarget() const
{
	return (this->_target);
}

//Exceptions
const char* AForm::GradeTooHighException::what() const throw()
{
	return "Error: Grade too High!";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Error: Grade too Low!";
}

const char* AForm::GradeIsNegative::what() const throw()
{
	return "Error: Grade is negative!";
}

std::ostream &operator<<(std::ostream &out, const AForm &AForm)
{
	out << "Is "<< PEACH << AForm.getName() << CYAN << " AForm signed?: " << MAGENTA << AForm.getSignedString() << std::endl << RESET \
	<< BLUE << "Grade to Sign: " << ORANGE << AForm.getSignGrade() << RESET << std::endl \
	<< BLUE << "Grade to execute: " << ORANGE << AForm.getExecGrade() << RESET << std::endl \
	<< BLUE << "Target is: " << ORANGE << AForm.getTarget() << RESET << std::endl;
	return out;
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:07 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/17 17:50:53 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

//Orthodox Canonical form
//Default Constructor
Form::Form() : _name("Default"), _signGrade(150), _execGrade(150)
{
	std::cout << GREEN << "Form Default Constructor Called" << RESET << std::endl;
	this->_signed = false;
}
//Named Constructor
Form::Form(std::string name, int gradeToSign, int gradeToExec) 
	: _name(name), _signGrade(gradeToSign), _execGrade(gradeToExec)
{
	std::cout << GREEN << "Form Named Constructor Called" << RESET << std::endl;
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
Form::Form(const Form &copy) 
	: _name(copy._name), _signGrade(copy._signGrade), _execGrade(copy._execGrade)
{
	std::cout << CYAN << "Form Copy constructor called" << RESET << std::endl;
	this->_signed = copy._signed;
}
//Copy assignement operator overload
Form &Form::operator=(const Form &copy)
{
	std::cout << MAGENTA << "Form Copy assignment operator called" << RESET << std::endl;
	if (this != &copy)
	{
		this->_signed = copy._signed;
	}
	return (*this);
}
//Destructor
Form::~Form()
{
	std::cout << RED << "Form Destrutcor Called" << RESET << std::endl;
}

//Member functions
void		Form::beSigned(Bureaucrat &Signer)
{
	std::cout << CYAN << Signer.getName() << RESET << " is trying to sign form " \
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

//Getters
std::string	Form::getName() const
{
	return (this->_name);
}

bool		Form::getIsSigned() const
{
	return (this->_signed);
}

std::string	Form::getSignedString() const
{
	if (this->getIsSigned() == true)
		return ("True");
	else
		return ("False");
}

int			Form::getSignGrade() const
{
	return (this->_signGrade);
}

int			Form::getExecGrade() const
{
	return (this->_execGrade);
}

//Exceptions
const char* Form::GradeTooHighException::what() const throw()
{
	return "Error: Grade too High!";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Error: Grade too Low!";
}

const char* Form::GradeIsNegative::what() const throw()
{
	return "Error: New Grade is negative!";
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
	out << "Is "<< PEACH << form.getName() << CYAN << " form signed?: " << MAGENTA << form.getSignedString() << std::endl << RESET \
	<< BLUE << "Grade to Sign: " << ORANGE << form.getSignGrade() << RESET << std::endl \
	<< BLUE << "Grade to execute: " << ORANGE << form.getExecGrade() << RESET << std::endl;
	return out;
}



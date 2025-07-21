/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:08:03 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 11:04:09 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

//Constructor
Bureaucrat::Bureaucrat() : _name("Default")
{
	std::cout << GREEN << "Bureaucrat Default Constructor Called" << RESET << std::endl;
	this->_grade = 150;
}
//Named Constructor
Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	std::cout << GREEN << "Bureaucrat Named Constructor Called" << RESET << std::endl;
	this->_grade = verifyGrade(grade);
}

//Copy Constructor
Bureaucrat::Bureaucrat(const Bureaucrat &copy)
{
	std::cout << CYAN << "Bureaucrat Copy constructor called" << RESET << std::endl;
	this->_grade = copy._grade;
}
//Copy assignement operator overload
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &copy)
{
	std::cout << MAGENTA << "Bureaucrat Copy assignment operator called" << RESET << std::endl;
	if (this != &copy)
	{
		this->_grade = copy._grade;
	}
	return (*this);
}

//Destructor
Bureaucrat::~Bureaucrat()
{
	std::cout << RED << "Bureaucrat Destrutcor Called" << RESET << std::endl;
}

const std::string Bureaucrat::getName() const
{
	return (this->_name);
}

int	Bureaucrat::getGrade() const
{
	return (this->_grade);
}

void	Bureaucrat::decrementGrade()
{
	int	tempGrade = getGrade();
	tempGrade += 1;

	this->_grade = verifyGrade(tempGrade);

	std::cout << BLUE << "Grade incremented!" << RESET << std::endl;
}

void	Bureaucrat::incrementGrade()
{
	int	tempGrade = getGrade();
	tempGrade -= 1;

	this->_grade = verifyGrade(tempGrade);

	std::cout << BLUE << "Grade incremented!" << RESET << std::endl;
}

void	Bureaucrat::setGrade(int newGrade)
{
	int tempGrade = newGrade;
	this->_grade = verifyGrade(tempGrade);
	std::cout << YELLOW << this->getName() << \
	" grade set to: " << BLUE << this->_grade << "\n" << RESET;
}

int	Bureaucrat::verifyGrade(int newgrade)
{
	if (newgrade == 0)
		throw Bureaucrat::GradeTooHighException();
	else if (newgrade > 150)
		throw Bureaucrat::GradeTooLowException();
	else if (newgrade < 0)
		throw Bureaucrat::GradeIsNegative();
	else
		return (newgrade);
}

void	Bureaucrat::signForm(Form &toSign)
{
	try
	{
		toSign.beSigned(*this);
	}
	catch (Form::GradeTooLowException &e)
	{
		std::cout << MAGENTA << this->getName() << ORANGE << " couldn't sign " \
		<< YELLOW << toSign.getName() << CYAN << " beacuse grade is too low!" << RESET << std::endl;
	}
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Error: Grade too High!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Error: Grade too Low!";
}

const char* Bureaucrat::GradeIsNegative::what() const throw()
{
	return "Error: Grade is negative!";
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
	out << MAGENTA << bureaucrat.getName() << RESET << ", bureaucrat grade: " \
		<< BLUE << bureaucrat.getGrade() << RESET << std::endl;
	return out;
}

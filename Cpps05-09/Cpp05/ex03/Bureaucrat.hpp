/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:07:52 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 12:06:33 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

/// COLOURS ///
#define RESET		"\033[0m"
#define RED			"\033[38;5;160m"
#define GREEN		"\033[38;5;76m"
#define BLUE		"\033[38;5;111m"
#define YELLOW		"\033[38;5;220m"
#define MAGENTA		"\033[38;5;183m"
#define CYAN    	"\033[38;5;87m"
#define ORANGE 		"\033[38;5;208m"
#define TURQUOISE	"\033[38;5;45m"
#define PEACH		"\033[38;5;217m"

#include <iostream>
#include <string>
#include <stdexcept>

#include "AForm.hpp"

class AForm;

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade; //1 - Highest; 150 - Lowest
	public:
		//Orthodox Canonical form
		//Default Constructor
		Bureaucrat();
		//Named Constructor
		Bureaucrat(std::string name, int grade);
		//Copy Constructor
		Bureaucrat(const Bureaucrat &copy);
		//Copy assignement operator overload
		Bureaucrat &operator=(const Bureaucrat &copy);
		//Destructor
		~Bureaucrat();

		//Member Functions
		//Getters
		const std::string	getName() const;
		int					getGrade() const;
		//Increment/Decrement
		void				incrementGrade();
		void				decrementGrade();
		
		void				setGrade(int newGrade);
		int					verifyGrade(int newGrade);
		void				signForm(AForm &toSign);
		void				executeForm(AForm const &toExecute);

		//Exceptions
		class GradeTooHighException : public std::exception
		{
			const char* what() const throw();
		};
		
		class GradeTooLowException : public std::exception
		{
			const char* what() const throw();
		};

		class GradeIsNegative : public std::exception
		{
			const char* what() const throw();
		};
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);

#endif
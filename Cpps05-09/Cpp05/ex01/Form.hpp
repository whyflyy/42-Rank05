/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:04 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/16 19:48:24 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

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

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		const std::string	_name;
		bool				_signed;
		const int			_signGrade;
		const int			_execGrade;
	public:
		//Orthodox Canonical form
		//Default Constructor
		Form();
		//Named Constructor
		Form(std::string name, int gradeToSign, int gradeToExec);
		//Copy Constructor
		Form(const Form &copy);
		//Copy assignement operator overload
		Form &operator=(const Form &copy);
		//Destructor
		~Form();

		//Member functions
		void		beSigned(Bureaucrat &Signer);
		//Getters
		std::string	getName(void) const;
		bool		getIsSigned(void) const;
		std::string	getSignedString(void) const;
		int			getSignGrade(void) const;
		int			getExecGrade(void) const;

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

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
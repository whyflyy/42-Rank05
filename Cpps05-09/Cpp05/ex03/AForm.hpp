/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:43:04 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 11:40:35 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AAForm_HPP
#define AAForm_HPP

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

class AForm
{
	private:
		const std::string	_name;
		bool				_signed;
		const int			_signGrade;
		const int			_execGrade;
		const std::string	_target;
	public:
		//Orthodox Canonical AForm
		//Default Constructor
		AForm();
		//Named Constructor
		AForm(std::string name, int gradeToSign, int gradeToExec, std::string target);
		//Copy Constructor
		AForm(const AForm &copy);
		//Copy assignement operator overload
		AForm &operator=(const AForm &copy);
		//Destructor
		virtual ~AForm();

		//Member functions
		void		beSigned(Bureaucrat &Signer);
		void		execute(Bureaucrat const &bureaucrat) const;
		//Getters
		std::string	getName(void) const;
		bool		getIsSigned(void) const;
		std::string	getSignedString(void) const;
		int			getSignGrade(void) const;
		int			getExecGrade(void) const;
		std::string	getTarget(void) const;
		
		virtual void	executor() const = 0;

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

std::ostream &operator<<(std::ostream &out, const AForm &AForm);

#endif
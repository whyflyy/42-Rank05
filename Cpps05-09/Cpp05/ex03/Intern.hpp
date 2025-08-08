/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:19:31 by jcavadas          #+#    #+#             */
/*   Updated: 2025/08/05 15:22:26 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

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

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern
{
	private:
		/* data */
	public:
		//Orthodox Canonical AForm
		//Default Constructor
		Intern();
		//Copy Constructor
		Intern(const Intern &copy);
		//Copy assignement operator overload
		Intern &operator=(const Intern &copy);
		//Destructor
		~Intern();

		//Member functions
		AForm	*makeForm(std::string formName, std::string target);
		AForm	*makeShrubbery(std::string target);
		AForm	*makeRobotomy(std::string target);
		AForm	*makePresidential(std::string target);
};

#endif
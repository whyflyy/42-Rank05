/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:52:44 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 11:55:50 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

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
#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		/* data */
	public:
		//Orthodox Canonical form
		//Default Constructor
		PresidentialPardonForm();
		//Named Constructor
		PresidentialPardonForm(std::string target);
		//Copy Constructor
		PresidentialPardonForm(const PresidentialPardonForm &copy);
		//Copy assignement operator overload
		PresidentialPardonForm &operator=(const PresidentialPardonForm &copy);
		//Destructor
		~PresidentialPardonForm();

		//Member functions
		void	executor() const;
};

#endif
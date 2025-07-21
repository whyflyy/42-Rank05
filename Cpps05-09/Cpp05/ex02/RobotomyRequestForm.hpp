/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:07:14 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 12:26:40 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

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
#include <iostream>
#include <string>
#include <cstdlib>

class RobotomyRequestForm : public AForm
{
	private:
		/* data */
	public:
		//Orthodox Canonical form
		//Default Constructor
		RobotomyRequestForm();
		//Named Constructor
		RobotomyRequestForm(std::string target);
		//Copy Constructor
		RobotomyRequestForm(const RobotomyRequestForm &copy);
		//Copy assignement operator overload
		RobotomyRequestForm &operator=(const RobotomyRequestForm &copy);
		//Destructor
		~RobotomyRequestForm();

		//Member functions
		void	executor() const;
};

#endif
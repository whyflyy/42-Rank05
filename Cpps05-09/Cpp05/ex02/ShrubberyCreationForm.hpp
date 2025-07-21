/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:23:00 by jcavadas          #+#    #+#             */
/*   Updated: 2025/07/21 12:27:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

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
#include <fstream>
#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	private:
		/* data */
	public:
		//Orthodox Canonical form
		//Default Constructor
		ShrubberyCreationForm();
		//Named Constructor
		ShrubberyCreationForm(std::string target);
		//Copy Constructor
		ShrubberyCreationForm(const ShrubberyCreationForm &copy);
		//Copy assignement operator overload
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &copy);
		//Destructor
		~ShrubberyCreationForm();

		//Member functions
		void	executor() const;
};

#endif

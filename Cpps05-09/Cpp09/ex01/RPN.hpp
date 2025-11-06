/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:26:27 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/06 16:07:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/// COLOURS ///
#include <stack>
#define RESET		"\033[0m"
#define RED			"\033[38;5;160m"
#define GREEN		"\033[38;5;76m"
#define BLUE		"\033[38;5;111m"
#define YELLOW		"\033[38;5;220m"
#define MAGENTA		"\033[38;5;183m"
#define CYAN		"\033[38;5;87m"
#define ORANGE		"\033[38;5;208m"
#define TURQUOISE	"\033[38;5;45m"
#define PEACH		"\033[38;5;217m"

#include <stack>
#include <iostream>

class RPN
{
	private:
		std::stack<long int>	_stack;
	public:
		RPN();
		RPN(const RPN& copy);
		RPN &operator=(const RPN& copy);
		~RPN();
};

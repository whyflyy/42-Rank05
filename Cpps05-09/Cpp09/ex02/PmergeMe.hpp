/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:39:44 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/15 22:48:10 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/// COLOURS ///
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

#include <iostream>
#include <ctime>
#include <vector>
#include <deque>
#include <limits>

static long int	MAXINT = std::numeric_limits<int>::max();
static long int	MININT = std::numeric_limits<int>::min();

class PmergeMe
{
	private:
		//-----------------Vector--------------------//
		std::vector<long>	_vec;
		std::vector<long>	_organizedVec;
		std::vector<std::pair<long, long> >	_vecPairs;
		bool	_oddVec;
		long	_vecLastElement;
		
		
		//-----------------Deque--------------------//
		std::deque<long>	_deq;
		std::deque<long>	_organizedDeq;
		std::deque<std::pair<long, long> >	_deqPairs;
		bool	_oddDeq;
		long	_deqLastElement;


	public:
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe &operator=(const PmergeMe& copy);
		~PmergeMe();

		//-----------------Vector--------------------//
		void	argToVec(int ac, char **av);
		void	organizeVec(void);
		void	splitVecToPair(void);
		void	organizeVecPairs(void);
		
		
		//-----------------Deque--------------------//
		void	argToDeq(int ac, char **av);
		void	organizeDeq(void);
		void	splitDeqToPair(void);
};

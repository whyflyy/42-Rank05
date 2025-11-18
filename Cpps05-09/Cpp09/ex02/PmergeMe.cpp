/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:39:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/18 16:57:37 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <utility>

PmergeMe::PmergeMe()
{
	std::cout << GREEN << "PmergeMe Default Constructor Called" << RESET << std::endl;
	_oddVec = false;
	_oddDeq = false;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	std::cout << CYAN << "PmergeMe Copy Constructor Called" << RESET << std::endl;
	*this = copy;
}

PmergeMe&	PmergeMe::operator=(const PmergeMe &copy)
{
	std::cout << CYAN << "PmergeMe Copy Assignement Operator Called" << RESET << std::endl;
	(void)copy;
	return *this;
}

PmergeMe::~PmergeMe()
{
	std::cout << PEACH << "PmergeMe Destructor Called" << RESET << std::endl;
}

//-----------------Vector--------------------//
void	PmergeMe::argToVec(int ac, char **av)
{
	long		value;

	for (int i = 1; i < ac; i++)
	{
		value = std::strtol(av[i], NULL, 0);
		if (value > MAXINT || value < MININT)
			throw std::runtime_error("Error! Number Overflow!");
		else
			_vec.push_back(value);
	}
}

void	PmergeMe::organizeVec()
{
	//TODO: Step 1: Pair numbers in the vec
	
	splitVecToPair();

	if (_vec.size() == 1)
	{
		_organizedVec.push_back(_vec[0]);
		return ;
	}

	//TODO: Step 2: Sort each pair
	
	organizeVecPairs();
	
	//TODO: Step 3: Extract all the first values from the pair and sort them
	//TODO: Step 4: Insert the small numbers using Ford Jhonson sequence (using binary search upper_bound)
}

//STEP 1
void	PmergeMe::splitVecToPair(void)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (i + 1 < _vec.size())
			_vecPairs.push_back(std::make_pair(_vec[i], _vec[i + 1]));
		else
		{
			_oddVec = true;
			_vecLastElement = _vec[i];
		}
	}
}

//STEP 2
void	PmergeMe::organizeVecPairs(void)
{
	for (size_t i = 0; i < _vecPairs.size(); i++)
	{
		if (_vecPairs[i].first < _vecPairs[i].second)
			std::swap(_vecPairs[i].first, _vecPairs[i].second);
	}
}

//STEP 3
void	PmergeMe::sortMainChain(void)
{
	std::vector<long>	mainChain;

	for (int i = 0; i < _vecPairs.size(); i++)
		mainChain.push_back(_vecPairs[i].first);

	size_t	mid = mainChain.size() / 2;
	
	
}
//TODO: Extract the large elements of each pair into a new vector(main chain)
//TODO: Sort the main chain recursively
//TODO: After sorting, _oganizedVec = mainChain



//-----------------Deque--------------------//
void	PmergeMe::argToDeq(int ac, char **av)
{
	//Nao faco a verificacao de overflow aqui porque ele faz o argtovec primeiro e verifica sempre la
	for (int i = 0; i < ac; i++)
		_deq.push_back(std::strtol(av[i], NULL, 0));
}

void	PmergeMe::organizeDeq(void)
{
	//TODO: Step 1: Pair numbers in the vec

	splitDeqToPair();
	
	//TODO: Step 2: Sort each pair
	//TODO: Step 3: Extract all the first values from the pair and sort them
	//TODO: Step 4: Insert the small numbers using Ford Jhonson sequence (using binary search upper_bound)
}

//STEP 1
void	PmergeMe::splitDeqToPair(void)
{
	for (size_t i = 0; i < _deq.size(); i++)
	{
		if (i + 1 < _deq.size())
			_deqPairs.push_back(std::make_pair(_deq[i], _deq[i + 1]));
		else
		{
			_oddDeq = true;
			_deqLastElement = _deq[i];
		}
	}
}
//-----------------Utils--------------------//

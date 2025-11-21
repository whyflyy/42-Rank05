/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:39:46 by jcavadas          #+#    #+#             */
/*   Updated: 2025/11/21 14:47:28 by jcavadas         ###   ########.fr       */
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
	//Step 1: Pair numbers in the vec
	splitVecToPair();

	/*for (size_t i = 0; i < _vecPairs.size(); i++)
	{
		std::cout << YELLOW << "_vecPairs.first: " << MAGENTA << _vecPairs[i].first << std::endl; //TODO: APAGAR?
		std::cout << YELLOW << "_vecPairs.second: " << MAGENTA << _vecPairs[i].second << std::endl;
	} */

	if (_vec.size() == 1)
	{
		_organizedVec.push_back(_vec[0]);
		return ;
	}
	else if (_vec.size() < 1)
		return ;
		
	//Step 2: Sort each pair
	organizeVecPairs();
	
	//Step 3: Extract all the first values from the pair and sort them
	sortMainChainVec();
	
	//Step 4: Insert the small numbers using Ford Jhonson sequence (using binary search upper_bound)
	insertSmallsVec();
}

//STEP 1
void	PmergeMe::splitVecToPair(void)
{
	for (size_t i = 0; i < _vec.size(); i += 2)
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
void	PmergeMe::sortMainChainVec(void)
{
	std::vector<long>	mainChain;

	for (size_t i = 0; i < _vecPairs.size(); i++)
		mainChain.push_back(_vecPairs[i].first);

	recursiveSortVec(mainChain);

	_organizedVec = mainChain;
	
	/*std::cout << YELLOW << "Organized Main chain: " << RESET << std::endl;
	for (size_t i = 0; i < _organizedVec.size(); i++)
	{
		std::cout << MAGENTA << _organizedVec[i] << RESET << " "; //TODO: APAGAR?
	} */
}

//STEP 4
void	PmergeMe::insertSmallsVec(void)
{
	std::vector<long>	smalls;
	
	for (size_t i = 0; i < _vecPairs.size(); i++)
		smalls.push_back(_vecPairs[i].second);
	
	std::vector<size_t>	order = generateVecJacobOrder(smalls.size());

	for (size_t i = 0; i < order.size(); i++)
	{
		long	value = smalls[order[i]];
		std::vector<long>::iterator	pos = std::upper_bound(_organizedVec.begin(), _organizedVec.end(), value);
		_organizedVec.insert(pos, value);
	}

	if (_oddVec)
	{
		long	v = _vecLastElement;
		std::vector<long>::iterator	pos = std::upper_bound(_organizedVec.begin(), _organizedVec.end(), v);
		_organizedVec.insert(pos, v);
	}
}


//-----------------Vector Utils--------------------//

void	PmergeMe::recursiveSortVec(std::vector<long> &v)
{
	if (v.size() <= 1)
		return;

	size_t	mid = v.size() / 2;

	std::vector<long>	top(v.begin(), v.begin() + mid);
	std::vector<long>	btm(v.begin() + mid, v.end());
	
	recursiveSortVec(top);
	recursiveSortVec(btm);

	v.clear();
	
	size_t	i = 0, j = 0;

	while (i < top.size() && j < btm.size())
	{
		if (top[i] <= btm[j])
			v.push_back(top[i++]);
		else
			v.push_back(btm[j++]);
	}

	while (i < top.size())
		v.push_back(top[i++]);
	
	while (j < btm.size())
		v.push_back(btm[j++]);
}

std::vector<size_t>	PmergeMe::generateVecJacobOrder(size_t n)
{
	std::vector<size_t>	order;
	
	if (n == 0)
		return order;
	
	std::vector<size_t>	jac;
	jac.push_back(1);
	jac.push_back(3);
	
	while (jac.back() < n)
	{
		size_t	s = jac[jac.size() - 1] + 2 * jac[jac.size() - 2];
		jac.push_back(s);
	}

	order.push_back(0); //First element is always 0
	
	// For each jac block, add indices from start-1 down to end
	for (size_t j = 1; j < jac.size(); j++)
	{
		size_t	start = jac[j] < n ? jac[j] : n;
		size_t	end = jac[j - 1] < n ? jac[j - 1] : n;

		for (size_t k = start; k > end; k--)
			order.push_back(k - 1);

		if (start == n)
			break;
	}

	return order;
}

void	PmergeMe::printOrgVec(void)
{
	for (size_t i = 0; i < _organizedVec.size(); i++)
	{
		std::cout << _organizedVec[i] << " ";
	}
	std::cout << std::endl; 
}


//-----------------Deque--------------------//
void	PmergeMe::argToDeq(int ac, char **av)
{
	//Nao faco a verificacao de overflow aqui porque ele faz o argtovec primeiro e verifica sempre la
	for (int i = 1; i < ac; i++)
		_deq.push_back(std::strtol(av[i], NULL, 0));
}

void	PmergeMe::organizeDeq(void)
{
	//Step 1: Pair numbers in the vec
	splitDeqToPair();

	//Step 2: Sort each pair
	organizeDeqPairs();
	
/* 	for (size_t i = 0; i < _deqPairs.size(); i++)
	{
		std::cout << YELLOW << "_deqPairs.first: " << MAGENTA << _deqPairs[i].first << std::endl; //TODO: APAGAR?
		std::cout << YELLOW << "_deqPairs.second: " << MAGENTA << _deqPairs[i].second << std::endl;
	} */
	
	//Step 3: Extract all the first values from the pair and sort them
	sortMainChainDeq();
	
	//Step 4: Insert the small numbers using Ford Jhonson sequence (using binary search upper_bound)
	insertSmallsDeq();
}

//STEP 1
void	PmergeMe::splitDeqToPair(void)
{
	for (size_t i = 0; i < _deq.size(); i += 2)
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

//STEP 2
void	PmergeMe::organizeDeqPairs(void)
{
	for (size_t i = 0; i < _deqPairs.size(); i++)
	{
		if (_deqPairs[i].first < _deqPairs[i].second)
			std::swap(_deqPairs[i].first, _deqPairs[i].second);
	}
}

//STEP 3
void	PmergeMe::sortMainChainDeq(void)
{
	std::deque<long>	mainChain;

	for (size_t i = 0; i < _deqPairs.size(); i++)
		mainChain.push_back(_deqPairs[i].first);

	recursiveSortDeq(mainChain);
		
	_organizedDeq = mainChain;
	
/* 	std::cout << YELLOW << "Organized Main chain: " << RESET << std::endl;
	for (size_t i = 0; i < _organizedDeq.size(); i++)
	{
		std::cout << MAGENTA << _organizedDeq[i] << RESET << " "; //TODO: APAGAR?
	} */
}

//STEP 4
void	PmergeMe::insertSmallsDeq(void)
{
	std::deque<long>	smalls;
	
	for (size_t i = 0; i < _deqPairs.size(); i++)
		smalls.push_back(_deqPairs[i].second);
	
	std::deque<size_t>	order = generateDeqJacobOrder(smalls.size());
	
	for (size_t i = 0; i < order.size(); i++)
	{
		long	value = smalls[order[i]];
		std::deque<long>::iterator	pos = std::upper_bound(_organizedDeq.begin(), _organizedDeq.end(), value);

		_organizedDeq.insert(pos, value);
	}

	if (_oddDeq)
	{
		long v = _deqLastElement;
		std::deque<long>::iterator	pos = std::upper_bound(_organizedDeq.begin(), _organizedDeq.end(), v);

		_organizedDeq.insert(pos, v);
	}
}


//-----------------Deque Utils--------------------//
void	PmergeMe::recursiveSortDeq(std::deque<long> &d)
{
	if (d.size() <= 1)
		return;

	size_t	mid = d.size() / 2;

	std::deque<long>	top(d.begin(), d.begin() + mid);
	std::deque<long>	btm(d.begin() + mid, d.end());
	
	recursiveSortDeq(top);
	recursiveSortDeq(btm);

	d.clear();
	
	size_t	i = 0, j = 0;

	while (i < top.size() && j < btm.size())
	{
		if (top[i] <= btm[j])
			d.push_back(top[i++]);
		else
			d.push_back(btm[j++]);
	}

	while (i < top.size())
		d.push_back(top[i++]);
	
	while (j < btm.size())
		d.push_back(btm[j++]);
}

std::deque<size_t>	PmergeMe::generateDeqJacobOrder(size_t n)
{
	std::deque<size_t>	order;
	
	if (n == 0)
		return order;
	
	std::deque<size_t>	jac;
	jac.push_back(1);
	jac.push_back(3);
	
	while (jac.back() < n)
	{
		size_t	s = jac[jac.size() - 1] + 2 * jac[jac.size() - 2];
		jac.push_back(s);
	}

	order.push_back(0); //First element is always 0
	
	// For each jac block, add indices from start-1 down to end
	for (size_t j = 1; j < jac.size(); j++)
	{
		size_t	start = jac[j] < n ? jac[j] : n;
		size_t	end = jac[j - 1] < n ? jac[j - 1] : n;

		for (size_t k = start; k > end; k--)
			order.push_back(k - 1);

		if (start == n)
			break;
	}

	return order;
}

void	PmergeMe::printOrgDeq(void)
{
	for (size_t i = 0; i < _organizedDeq.size(); i++)
	{
		std::cout << _organizedDeq[i] << " ";
	}
	std::cout << std::endl; 
}

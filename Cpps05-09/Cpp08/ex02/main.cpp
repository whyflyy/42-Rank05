/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:35:04 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/28 14:21:59 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.tpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int	main(void)
{
	std::cout << SEPARATOR << MAGENTA << "MutantStack Tests - Basic Operations" << SEPARATOR << RESET << std::endl;
	MutantStack<int>	mStack;
	
	mStack.push(5);
	mStack.push(17);
	
	std::cout << YELLOW << "Top Element: " << RESET << mStack.top() << std::endl;
	
	mStack.pop();

	std::cout << CYAN << "After pop, size is: " << RESET << mStack.size() << std::endl;

	mStack.push(3);
	mStack.push(5);
	mStack.push(737);
	mStack.push(0);

	
	MutantStack<int>::iterator	it = mStack.begin();
	MutantStack<int>::iterator	ite = mStack.end();
	++it;
	--it;

	std::cout << PEACH << "Mutant Stack contents (using iterators)" << RESET << std::endl;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	
	wait_for_enter();

	std::cout << SEPARATOR << MAGENTA << "MutantStack Tests - Copy and Assignment" << SEPARATOR << RESET << std::endl;
	MutantStack<int>	copy(mStack);

	std::cout << YELLOW << "Copied contents: " << RESET << std::endl;
	
	MutantStack<int>::iterator	cit = copy.begin();
	for (; cit != copy.end(); cit++)
		std::cout << *cit << std::endl;

	wait_for_enter();

	std::cout << SEPARATOR << MAGENTA << "Testing with lists" << SEPARATOR << RESET << std::endl;

	std::list<int>	lst;
	
	lst.push_back(5);
	lst.push_back(17);
	
	std::cout << YELLOW << "Top Element: " << RESET << *--lst.end() << std::endl;
	
	lst.pop_back();

	std::cout << CYAN << "After pop, size is: " << RESET << lst.size() << std::endl;

	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	
	std::list<int>::iterator	lit = lst.begin();
	std::list<int>::iterator	lite = lst.end();
	++lit;
	--lit;

	std::cout << PEACH << "List contents (using iterators)" << RESET << std::endl;
	while (lit != lite)
	{
		std::cout << *lit << std::endl;
		++lit;
	}
	
	wait_for_enter();
}

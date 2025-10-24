/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:53:38 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/17 14:58:50 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

Base*	generate(void)
{
	int random = std::rand() % 3;
	
	switch (random)
	{
		case 0:
			return (new A);
			break;
		case 1:
			return (new B);
			break;
		case 2:
			return (new C);
			break;
	}
	return (NULL);
}

void	identify(Base* p)
{
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << YELLOW << "The object's type is " << TURQUOISE << "A" << YELLOW << "!" << RESET << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << YELLOW << "The object's type is " << TURQUOISE << "B" << YELLOW << "!" << RESET << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << YELLOW << "The object's type is " << TURQUOISE << "C" << YELLOW << "!" << RESET << std::endl;
	else
		std::cout << RED << "Something went wrong with the object's type!" << RESET << std::endl;	
}

void	identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << PEACH << "The object's type is " << CYAN << "A" << PEACH << "!" << RESET << std::endl;
	}
	catch(const std::exception& e)
	{
		try
		{
			(void)dynamic_cast<B&>(p);
			std::cout << PEACH << "The object's type is " << CYAN << "B" << PEACH << "!" << RESET << std::endl;
		}
		catch(const std::exception& e)
		{
			try
			{
				(void)dynamic_cast<C&>(p);
				std::cout << PEACH << "The object's type is " << CYAN << "C" << PEACH << "!" << RESET << std::endl;
			}
			catch(const std::exception& e)
			{
						std::cout << RED << "Something went wrong with the object's type!" << RESET << std::endl;
			}
		}
	}
}

int	main()
{
	Base	*base;
	std::srand(static_cast<unsigned>(time(NULL)));
	
	base = generate();
	if (base == NULL)
		return 0;

	Base	*Brah;
	Brah = generate();
	if (Brah == NULL)
		return 0;

	std::cout << SEPARATOR << MAGENTA << "Identify with Pointer" << SEPARATOR << RESET << std::endl;
	identify(base);
	std::cout << std::endl;
	identify(Brah);

	
	std::cout << SEPARATOR << MAGENTA << "Identify with Reference" << SEPARATOR << RESET << std::endl;
	identify(*base);
	std::cout << std::endl;
	identify(*Brah);

	std::cout << SEPARATOR << MAGENTA << "Destructors separator" << SEPARATOR << RESET << std::endl;
	
	delete base;
	delete Brah;
}

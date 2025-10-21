/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:10:17 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/21 12:38:37 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Functions.hpp"

#define SEPARATOR "\033[38;5;208m\n==============================\n\033[0m"

void wait_for_enter() {
	std::cout << "\nPress ENTER to continue..." << std::endl;
	std::cin.ignore();
	std::cout << "\033[2J\033[H"; // Clear screen
}

int	main( void )
{
	std::cout << SEPARATOR << "Tests from subject" << SEPARATOR << std::endl;
	int a = 2;
	int b = 3;
	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

	wait_for_enter();

	std::cout << SEPARATOR << "Extra tests" << SEPARATOR << std::endl;
	double	da = 2.5;
	double	db = 4.2;

	std::cout << "da = " << da << ", db = " << db << std::endl;
	swap(da, db);
	std::cout << "da = " << da << ", db = " << db << std::endl;
	std::cout << "min(da, db) = " << ::min(da, db) << std::endl;
	std::cout << "max(da, db) = " << ::max(da, db) << std::endl;

	std::cout << std::endl;

	float	fa = 4.2f;
	float	fb = 6.5f;
	
	std::cout << "fa = " << fa << ", fb = " << fb << std::endl;
	swap(fa, fb);
	std::cout << "fa = " << fa << ", fb = " << fb << std::endl;
	std::cout << "min(fa, fb) = " << ::min(fa, fb) << std::endl;
	std::cout << "max(fa, fb) = " << ::max(fa, fb) << std::endl;

	return 0;
}
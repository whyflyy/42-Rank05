/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:01:54 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/30 15:13:59 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange	btc;
	if (ac == 2)
	{
		btc.loadDB("data.csv");
	}
	else
		std::cout << RED << "Wrong number of arguments. Correct usage is: " << PEACH << "./btc <filename>.txt" << RESET << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:10:38 by jcavadas          #+#    #+#             */
/*   Updated: 2025/10/10 09:54:44 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConerter.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
        std::cout << RED << "Error: no argument!" << RESET << std::endl;
    else if (ac == 2)   
        ScalarConverter::convert(av[1]);
    else
        std::cout << RED << "Error: too many arguments!" << RESET << std::endl;
}

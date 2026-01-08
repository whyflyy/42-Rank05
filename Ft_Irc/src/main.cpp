/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:53:50 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/10 22:30:20 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

const std::string ft_strtoupper(const std::string &other)
{
  std::string result = other;

  for (size_t i = 0; i < result.size(); i++) {
    result[i] = static_cast<char>(std::toupper(result[i]));
  }
  return (result);
}

static int	printErrorMsg(const char *const msg)
{
	std::cerr <<
	format::bold << color::red << msg <<
	format::reset << std::endl;
	return (EXIT_FAILURE);
}

static int	check_port(const std::string &port, int &port_number)
{
	std::string::const_iterator	it;
	std::string::const_iterator	ite;

	it = port.begin();
	ite = port.end();
	while (it != ite)
	{
		if (!isdigit(*it))
			return (EXIT_FAILURE);
		it++;
	}
	port_number = std::atoi(port.c_str());
	if (port_number < ircserv::min_port || port_number > ircserv::max_port)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	int	port;
	
	if (argc != 3)
		return (printErrorMsg(ircserv::input_args));
	port = -1;
	if (check_port(argv[1], port) == EXIT_FAILURE)
		return (printErrorMsg(ircserv::invalid_port));
	try
	{
		IrcServer	server(port, argv[2]);
		server.launch();
	}
	catch(const std::exception& e)
	{
		printErrorMsg(e.what());
	}
	return (EXIT_SUCCESS);
}

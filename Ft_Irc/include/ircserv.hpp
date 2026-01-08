/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:05:45 by antfonse          #+#    #+#             */
/*   Updated: 2025/10/14 22:09:20 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP

# include <cstdlib>				// C Standard Library (Return codes)
# include <iostream>			// Standard Input / Output Streams Library

# include "Styles.hpp"			// Output formatting
# include "IrcServer.hpp"

namespace ircserv
{
	// PORT LIMITS
	const int			min_port	= 0;
	const int			max_port	= 65535;	
	
	// ERROR MESSAGES
	const char	*const input_args	= "Usage: ./ircserv <port> <password>";
	const char	*const invalid_port	= "Invalid port number";

}

#endif
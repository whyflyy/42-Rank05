/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelModes.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:55:14 by jcavadas          #+#    #+#             */
/*   Updated: 2025/12/30 12:42:41 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"
#include <climits>

void	Channel::handleModeK(std::vector<std::string> &tokens, User &user, bool add)
{
	if (add)
	{
		if (tokens.size() >= 4)
		{
			_password = tokens[3];
			this->_modes[channel::Key] = add;
			sendModeChange("+k", tokens[3], user);
		}
		else
		{
			std::string	msg = ":ft_irc 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
			//send(user.getFd(), msg.c_str(), msg.size(), 0);
			user.appendToBuffer(msg);
			return ;
		}
	}
	else
	{
		_password = "";
		this->_modes[channel::Key] = add;
		sendModeChange("-k", "", user);
	}
}

void	Channel::handleModeL(std::vector<std::string> &tokens, User &user, bool add)
{
	if (add)
	{
		if (tokens.size() < 4)
		{
			std::string	msg = ":ft_irc 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
			//send(user.getFd(), msg.c_str(), msg.size(), 0);
			user.appendToBuffer(msg);
			return ;
		}
		else if (tokens[3].empty() || tokens[3].size() > 10)
		{
			std::string	msg = ":ft_irc 696 " + user.getNickname() + " " + _name + " l :Invalid limit parameters\r\n"; //TODO: trocar este numeric code por 461 Not enough parameters?
			//send(user.getFd(), msg.c_str(), msg.size(), 0);
			user.appendToBuffer(msg);
			return ;
		}
		
		for (size_t i = 0; i < tokens[3].size(); i++)
		{
			if (!std::isdigit(static_cast<unsigned char>(tokens[3][i])))
			{
				std::string	msg = ":ft_irc 696 " + user.getNickname() + " " + _name + " l :Invalid limit parameters\r\n"; //TODO: trocar este numeric code por 461 Not enough parameters?ou 472 Unknown mode char?
				//send(user.getFd(), msg.c_str(), msg.size(), 0);
				user.appendToBuffer(msg);
				return ;
			}
		}

		std::stringstream	ss(tokens[3]);
		long long	limit;
		ss >> limit;
		
		if (!ss.eof() || ss.fail() || limit <= 0 || limit >= INT_MAX)
		{
			std::string	msg = ":ft_irc 696 " + user.getNickname() + " " + _name + " l :Invalid limit parameters\r\n"; //TODO: trocar este numeric code por 461 Not enough parameters? ou 472 Unknown mode char?
			//send(user.getFd(), msg.c_str(), msg.size(), 0);
			user.appendToBuffer(msg);
			return ;
		}

		this->_modes[channel::Limit] = add;
		_userLimit = limit;
		sendModeChange("+l",tokens[3], user);
	}
	else
	{
		this->_modes[channel::Limit] = add;
		_userLimit = 0;
		sendModeChange("-l", "", user);
	}
}

void	Channel::handleModeO(std::vector<std::string> &tokens, User &user, bool add)
{
	if (tokens.size() < 4)
	{
		std::string msg = ":ft_irc 461 " + user.getNickname() + 
						  " MODE :Not enough parameters\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
		return ;
	}

	const std::string	&targetNick = tokens[3];

	if (!nickIsInChannel(targetNick))
	{
		std::string msg = ":ft_irc 441 " + user.getNickname() + " " + targetNick +
						  " " + _name + " :They aren't on that channel\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
		return ;
	}

	int targetFd = getFdByNickname(targetNick);
	if (targetFd == -1)
		return ;
	if (add)
	{
		if (isOperator(targetFd))
			return ; // already operator, silently ignore
		setOperator(targetFd, true);
		sendModeChange("+o", targetNick, user);
	}
	else
	{
		if (!isOperator(targetFd))
			return ; // not operator, silently ignore
		setOperator(targetFd, false);
		sendModeChange("-o", targetNick, user);
	}
}

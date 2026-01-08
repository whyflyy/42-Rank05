/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:40:56 by jcavadas          #+#    #+#             */
/*   Updated: 2025/12/30 12:43:54 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

std::vector<std::string> splitMsg(const std::string &msg)
{
	std::vector<std::string> tokens;
	std::string current;
	bool inTrailing = false;

	for (size_t i = 0; i < msg.length(); ++i)
	{
		char c = msg[i];

		if (!inTrailing && c == ':')
		{
			if (!current.empty())
			{
				tokens.push_back(current);
				current.clear();
			}
			inTrailing = true;
			continue;
		}
		else if (!inTrailing && c == ' ')
		{
			if (!current.empty())
			{
				tokens.push_back(current);
				current.clear();
			}
			while (i + 1 < msg.length() && msg[i + 1] == ' ')
				++i;
		}
		else if (c == '\r' || c == '\n')
		{
			continue;
		}
		else
		{
			current += c;
		}
	}

	if (!current.empty())
		tokens.push_back(current);

	return tokens;
}

int		IrcServer::userExists(const std::string &nickname)
{
	std::string upperNick = ft_strtoupper(nickname);
	for (size_t i = 0; i < this->_users.getPollFDCount(); i++)
	{
		User *u = this->_users.getUser(this->_users.getPollFd(i)->fd);
		if (u && ft_strtoupper(u->getNickname()) == upperNick)
			return this->_users.getPollFd(i)->fd;
	}
	return -1;
}

void	IrcServer::sendNoParams(User &user, const std::string &command)
{
	std::string msg = ":ft_irc 461 " + user.getNickname();
	msg += " " + command + " :Not enough parameters\r\n";
	//send(user.getFd(), msg.c_str(), msg.size(), 0);
	user.appendToBuffer(msg);
}

void	IrcServer::sendNoChannel(User &user, const std::string &channel)
{
	std::string msg = ":ft_irc 403 " + user.getNickname();
	msg += " " + channel + " :No such channel\r\n";
	//send(user.getFd(), msg.c_str(), msg.size(), 0);
	user.appendToBuffer(msg);
}

void	IrcServer::privMsg(const std::vector<std::string> &tokens, User &user)
{
	if (tokens.size() <= 2 || tokens[2].empty())
	{
		sendNoParams(user, "PRIVMSG");
		return ;
	}
	
	// Check if target is a user
	int recipientFd = userExists(tokens[1]);
	if (recipientFd != -1)
	{
		User *recipient = this->_users.getUser(recipientFd);
		if (recipient)
		{
			user.sendMessage(tokens[2], user.getNickname(), user.getUsername(), recipient->getNickname(), *recipient);
		}
		return ;
	}
	// Check if target is a channel
	std::string target = tokens[1];
	std::string channelKey = target;

	if (this->channelExists(channelKey))
	{
		Channel *channel = this->_channels.getChannel(channelKey);
		if (channel)
		{
			// Check if the user is in the channel
			const channel::t_users &members = channel->getUsers();
			
			// User is not in the channel
			if (members.find(user.getFd()) == members.end())
			{
				channel->sendNotInChannel(user); //TODO: trocar por 404?
				return ;
			}
			// User is in channel, send message to all other members
			channel->messageChannel(user, tokens);
		}
		return ;
	}
	// User or channel not found—send ERR_NOSUCHNICK (401)
	std::string msg = ":ft_irc 401 " + user.getNickname() + " " + tokens[1] + " :No such nick/channel\r\n";
	//send(user.getFd(), msg.c_str(), msg.size(), 0);
	user.appendToBuffer(msg);
}

void	IrcServer::kickUser(IrcServer *server, User &user, const std::string &reason)
{
	if (user.getIsRegistered())
	{
		std::string quitMessage = reason;

		// Notify all channels the user is part of
		user::t_channels &userChannels = user.getChannels();
		for (user::t_channels::iterator it = userChannels.begin(); it != userChannels.end(); ++it)
		{
			Channel *channel = it->second.first;
			if (channel)
			{
				channel->handleQuit(&user, quitMessage);
			}
		}
	}
	else
	{
		// User not authenticated - send simple ERROR message
		std::string msg = "ERROR :Closing Link: " + reason + "\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
	}
	
	(void)server;
	user.setPass(false); //TODO: precisa disto?
	user.setCapLS(false);
	// Don't delete the user here—set it to closing state and let check_poll_masks() handle cleanup
	user.setState(user::closing);
}

void	IrcServer::handleJoin(const std::vector<std::string> &tokens, User &user)
{
	if (tokens.size() < 2)
	{
		sendNoParams(user, "JOIN");
		return;
	}

	// Split channels
	std::vector<std::string> channels;
	std::istringstream chanStream(tokens[1]);
	std::string chan;
	while (std::getline(chanStream, chan, ','))
		channels.push_back(chan);

	// Split keys (optional)
	std::vector<std::string> keys;
	if (tokens.size() >= 3)
	{
		std::istringstream keyStream(tokens[2]);
		std::string key;
		while (std::getline(keyStream, key, ','))
			keys.push_back(key);
	}

	// Process each channel independently
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string channelName = channels[i];
		std::string password = (i < keys.size()) ? keys[i] : "";

		// Validate channel name
		if (channelName.empty() || channelName[0] != '#')
		{
			sendNoChannel(user, channelName);
			continue;
		}

		// Channel exists
		if (_channels.channelExists(channelName))
		{
			Channel *channel = _channels.getChannel(channelName);

			// Already in channel
			const channel::t_users &members = channel->getUsers();
			if (members.find(user.getFd()) != members.end())
				continue;

			if (channel->addUser(&user, false, password))
			{
				// Also add channel to user's channel list
				user.addChannel(channel, false);
			}
		}
		else
		{
			// Create new channel
			Channel *newChannel = _channels.addChannel(channelName, password);
			if (newChannel->addUser(&user, true, password))
			{
				// Also add channel to user's channel list (as operator)
				user.addChannel(newChannel, true);
			}
		}
	}
}

void	IrcServer::handlePart(const std::vector<std::string> &tokens, User &user)
{
	if (tokens.size() < 2)
	{
		sendNoParams(user, "PART");
		return ;
	}
	
	// Split channels by comma
	std::vector<std::string> channels;
	std::istringstream iss(tokens[1]);
	std::string channel;
	while (std::getline(iss, channel, ','))
	{
		channels.push_back(channel);
	}

	// Optional part message
	std::string partMessage = "";
	if (tokens.size() >= 3)
		partMessage = tokens[2];
	
	// Process each channel
	for (size_t i = 0; i < channels.size(); ++i)
	{
		std::string channelName = channels[i];
		std::string channelKey = channelName;

		// Check if channel exists
		if (this->channelExists(channelKey))
		{
			Channel *channel = this->_channels.getChannel(channelKey);
			if (channel)
			{
				// Check if user is in the channel
				const channel::t_users &members = channel->getUsers();
				if (members.find(user.getFd()) != members.end())
				{
					// Notify remaining members (server will handle removing user from both sides)
					channel->sendPart(&user, partMessage);
					// Remove user from channel and user's channel list; remove channel if empty
					this->removeUserChannel(user.getFd(), channelName);
					// Send PART message to the leaving user
					std::string userMsg = ":" + user.getNickname() + "!" + user.getUsername() + "@localhost PART " + channelName;
					if (!partMessage.empty())
						userMsg += " :" + partMessage;
					userMsg += "\r\n";
					//send(user.getFd(), userMsg.c_str(), userMsg.size(), 0);
					user.appendToBuffer(userMsg);
				}
				else
					channel->sendNotInChannel(user);
			}
		}
		else
			sendNoChannel(user, channelName); // Channel doesn't exist
	}
}

void	IrcServer::handleMode(std::vector<std::string> &tokens, User &user)
{
	if (tokens.size()< 3)
	{
		sendNoParams(user, "MODE");
		return;
	}
	else //MODE <target> <modes> <params> (mais que um mode -> MODE <target> +itk <params>)
	{
		if (this->channelExists(tokens[1]))
		{
			Channel *channel = this->_channels.getChannel(tokens[1]);
			if (channel)
			{
				//Checkar a syntax do mode
				if (tokens[2].c_str())
				{
					std::string	mode = tokens[2];
					if (tokens.size() >= 3 && tokens[2].size() < 2)
					{
						std::string	msg = ":ft_irc 905 " + user.getNickname() + " MODE :Mode changes need to be <sign><mode>!\r\n";
						//send(user.getFd(), msg.c_str(), msg.size(), 0);
						user.appendToBuffer(msg);
						return ;
					}
					if (tokens.size() >= 3 && tokens[2].size() > 2) //TODO: deixar isto? -> Podemos argumentar que escolhemos fazer so com um modo (nao diz em lado nenhum no subject que devia aceitar mais que um)
					{
						std::string	msg = ":ft_irc 904 " + user.getNickname() + " MODE :Too many mode changes in one call!\r\n";
						//send(user.getFd(), msg.c_str(), msg.size(), 0);
						user.appendToBuffer(msg);
						return ;		
					}
				}
				else
					return ; //TODO: isso esta certo assim? -> ignora se nao tem mode
				channel->handleChannelMode(tokens, user);
			}
			return ;
		}
		else
		{
			sendNoChannel(user, tokens[1]);
			return ;
		}
	}
}

void	IrcServer::handlePing(const std::vector<std::string> &tokens, User &user)
{
    std::string token;

    if (tokens.size() >= 2)
        token = tokens[1];
    else
        token = "ft_irc";

    std::string msg = "PONG :" + token + "\r\n";
    //send(user.getFd(), msg.c_str(), msg.size(), 0);
    user.appendToBuffer(msg);
}

void	IrcServer::handleTopic(const std::vector<std::string> &tokens, User &user)
{
	if (tokens.size() < 2)
	{
		sendNoParams(user, "TOPIC");
		return ;
	}
	
	std::string channelName = tokens[1];

	// Check if channel exists
	if (!this->channelExists(channelName))
	{
		sendNoChannel(user, channelName);
		return ;
	}

	Channel *channel = this->_channels.getChannel(channelName);
	if (!channel)
		return ;
	
	channel->handleTopic(tokens, user);
}

void	IrcServer::handleInvite(const std::vector<std::string> &tokens, User &user)
{
	if (tokens.size() < 3)
	{
		sendNoParams(user, "INVITE");
		return ;
	}
	else
	{
		int userTarget = userExists(tokens[1]);
		int channelTargets = channelExists(tokens[2]);

		if (userTarget == -1)
		{
			std::string msg = ":ft_irc 401 " + user.getNickname() + " " + tokens[1] + " :No such nick/channel\r\n";
			//send(user.getFd(), msg.c_str(), msg.size(), 0);
			user.appendToBuffer(msg);
			return ;
		}
		else if (channelTargets == 0)
		{
			sendNoChannel(user, tokens[2]);
			return ;
		}
		else
		{
			User *targetUser = _users.getUser(userTarget);
			Channel *channel = _channels.getChannel(tokens[2]);

			// Check if the inviting user is in the channel
			const channel::t_users &members = channel->getUsers();
			if (members.find(user.getFd()) == members.end())
			{
				channel->sendNotInChannel(user); //TODO: trocar por 404?
				return ;
			}

			// Send invitation
			channel->inviteUser(user, *targetUser);
		}
	}
}

void	IrcServer::handleKick(const std::vector<std::string> &tokens, User &user)
{
	if (tokens.size() < 3)
	{
		sendNoParams(user, "KICK");
		return ;
	}
	else
	{
		int	i = channelExists(tokens[1]);
		if (i == 0)
		{
			sendNoChannel(user, tokens[1]);
			return ;
		}
		else
		{
			Channel *channel = _channels.getChannel(tokens[1]);
			if (channel)
			{
				channel->handleKick(tokens, user);
			}
		}
	}
	
}

void	IrcServer::parsecommand(IrcServer *server, User &user, std::string msg)
{
	std::vector<std::string> tokens = splitMsg(msg);
	if (tokens.empty()) return;

	for (size_t i = 0; i < tokens.size(); i++)
	{
		tokens[i].erase(std::remove(tokens[i].begin(), tokens[i].end(), '\r'), tokens[i].end());
		tokens[i].erase(std::remove(tokens[i].begin(), tokens[i].end(), '\n'), tokens[i].end());
	}

	std::string command = tokens[0];  // <== COPY AFTER CLEANING

	//so pode fazer to upper do commando em si, nao quero que faca toupper da mensagem toda.
	for (size_t i = 0; i < command.size(); i++)
		command[i] = std::toupper(command[i]);

	int	authRes = 0; // Variable to track authentication result
	if (user.getIsRegistered() == false)
	{
		authRes = user.authenticate(command, tokens, getPassword(), _users);
	}
	else
	{
		if (command == "PRIVMSG")
			privMsg(tokens, user);
		else if (command == "JOIN")
			handleJoin(tokens, user);
		else if (command == "KICK")
			handleKick(tokens, user);
		else if (command == "INVITE")
			handleInvite(tokens, user);
		else if (command == "TOPIC")
			handleTopic(tokens, user);
		else if (command == "MODE")
			handleMode(tokens, user);
		else if (command == "QUIT")
			kickUser(server, user, tokens.size() >= 2 ? tokens[1] : "Client Quit");
		else if (command == "PART")
			handlePart(tokens, user);
		else if (command == "PING")
			handlePing(tokens, user);
		else if (command == "CAP")
		{}
		else
		{
			std::string msg = ":ft_irc 421 " + user.getNickname() + " " + command + " :Unknown command\r\n";
			//send(user.getFd(), msg.c_str(), msg.size(), 0);
			user.appendToBuffer(msg);
		}
	}
	if (authRes == 1)
		kickUser(server, user, "Authentication failed");
}

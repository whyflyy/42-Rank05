/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:29:33 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/30 12:40:34 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"

Channel::Channel(const std::string &name, const std::string &password): _name(name), _modes(5, false), _topic(""), _password(password), _userLimit(0)
{
	if (!password.empty())
		this->_modes[channel::Key] = true;
}

Channel::~Channel(void)
{}

/* ************************************************************************** */

void	Channel::addPassword(const std::string &password)
{
	this->_password = password;
}

void	Channel::addTopic(const std::string &topic)
{
	this->_topic = topic;
}

std::string		Channel::getName(void) const
{
	return (this->_name);
}

std::string		Channel::getTopic(void) const
{
	return (this->_topic);
}

size_t			Channel::getNumberUsers(void) const
{
	return (this->_users.size());
}

channel::t_users	Channel::getUsers(void) const
{
	return (this->_users);
}

bool	Channel::hasUser(const int &fd) const
{
	return (this->_users.find(fd) != this->_users.end());
}

bool	Channel::nickIsInChannel(const std::string &nickname) const
{
	for (channel::t_users::const_iterator it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		User *member = it->second.first;
		if (member && member->getNickname() == nickname)
			return true;
	}
	return false;
}

int	Channel::getFdByNickname(const std::string &nickname) const
{
	for (channel::t_users::const_iterator it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		User *member = it->second.first;
		if (member && member->getNickname() == nickname)
			return it->first;
	}
	return -1;
}

bool	Channel::getMode(const int &mode) const
{
	return (this->_modes[mode]);
}

bool	Channel::isUserInvited(const int &fd) const
{
	return (std::find(_invitedUsers.begin(), _invitedUsers.end(), fd) != _invitedUsers.end());
}

void	Channel::sendCantJoin(User *user, char mode_char, const std::string &err_code)
{
	std::string msg = ":ft_irc " + err_code + " " + user->getNickname();
	msg += " " + _name + " :Cannot join channel (+" + mode_char + ")\r\n";
	//send(user->getFd(), msg.c_str(), msg.size(), 0);
	user->appendToBuffer(msg);
}

void	Channel::sendJoinMessage(User *user)
{
	std::string msg = ":" + user->getNickname() + "!" + user->getUsername();
	msg += "@host JOIN :" + _name + "\r\n";
	//send(user->getFd(), msg.c_str(), msg.size(), 0);
	user->appendToBuffer(msg);

	// Notify all users in the channel about the new user

	sendTopic(user, user);
	sendUserList(user, user);
	sendEndNameList(user, user);

	for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		int memberFd = it->first;
		if (memberFd != user->getFd())
		{
			User *member = it->second.first;
			if (member)
			{
				sendTopic(user, member);
				sendUserList(user, member);
				sendEndNameList(user, member);
			}
		}
	}
}

bool	Channel::addUser(User *user, const bool &user_mode, std::string password)
{
	channel::t_user	us;
	int fd = user->getFd();

	// Check if user is already in the channel
	if (this->_users.find(fd) != this->_users.end())
		return (false);

	// Check password if channel is key-protected (mode k)
 	if (this->_modes[channel::Key])
	{
		if (this->_password != password)
		{
			sendCantJoin(user, 'p', "475"); // ERR_BADCHANNELKEY
			return (false);
		}
	}

	// Check if channel is invite-only (mode i) and user is not invited
	if (this->_modes[channel::Invite] && !isUserInvited(user->getFd()))
	{
		// Note: Invitation checking should be implemented with an invite list
		sendCantJoin(user, 'i', "473"); // ERR_INVITEONLYCHAN
		return (false);
	}

	// Check user limit (mode l)
	if (this->_modes[channel::Limit] && (int)this->_users.size() >= _userLimit)
	{
		sendCantJoin(user, 'l', "471"); // ERR_CHANNELISFULL
		return (false);
	}

	// Add user to channel
	us.first = user;
	us.second = user_mode; // true for operator, false for regular user
	this->_users.insert(std::make_pair(fd, us));

	sendJoinMessage(user); // Notify all users about the new user
	return (true);
}

void	Channel::removeUser(const int &fd)
{
	channel::t_users::iterator	it;

	it = this->_users.find(fd);
	if (it != this->_users.end())
		this->_users.erase(it);
}

void	Channel::setMode(const int &mode)
{
	this->_modes[mode] = true;
}
void	Channel::removeMode(const int &mode)
{
	this->_modes[mode] = false;
}

void	Channel::printChannel(void) const
{
	std::cout <<
	format::bold << color::magenta << "[ " <<
	format::reset << this->_name << ", " <<
	this->_password << ", " <<
	this->_topic <<
	format::bold << color::magenta << " ]" <<
	format::reset << std::endl;
}

void	Channel::sendTopic(User *user, User *member)
{
	std::string msg;
	if (this->_topic.empty())
	{
		msg = ":ft_irc 331 " + user->getNickname() + " " + this->_name + " :No topic is set\r\n";
	}
	else
	{
		msg = ":ft_irc 332 " + user->getNickname() + " " + this->_name + " :" + this->_topic + "\r\n";
	}
	//send(member->getFd(), msg.c_str(), msg.size(), 0);
    member->appendToBuffer(msg);
}

void	Channel::sendUserList(User *user, User *member)
{
	//bool first = true;
	std::string msg = ":ft_irc 353 " + user->getNickname() + " = " + this->_name + " :";
	for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		User *member = it->second.first;
		if (member)
		{
			if (it->second.second) // If user is an operator
				msg += "@" + member->getNickname() + " ";
			else
				msg += member->getNickname() + " ";
		}
	}
	msg += "\r\n";
	//send(member->getFd(), msg.c_str(), msg.size(), 0);
    member->appendToBuffer(msg);
}

void	Channel::sendEndNameList(User *user, User *member)
{
	std::string msg = ":ft_irc 366 " + user->getNickname() + " " + this->_name + " :End of /NAMES list\r\n";
	//send(member->getFd(), msg.c_str(), msg.size(), 0);
    member->appendToBuffer(msg);
}

void	Channel::sendQuit(User *user, const std::string &quitMessage) const
{
	for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		int memberFd = it->first;
		if (memberFd != user->getFd())
		{
			User *member = it->second.first;
			if (member)
			{
				std::string msg = ":" + user->getNickname() + "!" + user->getUsername() + "@localhost QUIT";
				if (!quitMessage.empty())
					msg += " :" + quitMessage;
				msg += "\r\n";
				//send(member->getFd(), msg.c_str(), msg.size(), 0);
                member->appendToBuffer(msg);
			}
		}
	}
}

void	Channel::handleQuit(User *user, const std::string &quitMessage) const
{
	for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		int memberFd = it->first;
		if (memberFd != user->getFd())
		{
			// Check if member has already been notified about this quit
			if (user->_notifiedQuitFds.find(memberFd) == user->_notifiedQuitFds.end())
			{
				User *member = it->second.first;
				if (member)
				{
					std::string msg = ":" + user->getNickname() + "!" + user->getUsername() + "@localhost QUIT";
					if (!quitMessage.empty())
						msg += " :" + quitMessage;
					msg += "\r\n";
					//send(member->getFd(), msg.c_str(), msg.size(), 0);
                    member->appendToBuffer(msg);
					
					// Mark this user as notified
					user->_notifiedQuitFds.insert(memberFd);
				}
			}
		}
	}
}

void	Channel::sendPart(User *user, const std::string &partMessage) const
{
	for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		int memberFd = it->first;
		if (memberFd != user->getFd())
		{
			User *member = it->second.first;
			if (member)
			{
				std::string msg = ":" + user->getNickname() + "!" + user->getUsername() + "@localhost PART " + _name;
				if (!partMessage.empty())
					msg += " :" + partMessage;
				msg += "\r\n";
				//send(member->getFd(), msg.c_str(), msg.size(), 0);
                member->appendToBuffer(msg);
			}
		}
	}
}

void	Channel::sendNotInChannel(User &user)
{
	std::string	msg = ":ft_irc 442 " + user.getNickname() + " " + _name + " :You're not on that channel\r\n";
	//send(user.getFd(), msg.c_str(), msg.size(), 0);
	user.appendToBuffer(msg);
	return ;
}

bool	Channel::isOperator(const int &fd)
{
	channel::t_users::const_iterator it = this->_users.find(fd);
	if (it == this->_users.end())
		return false; // not present => not operator
	return it->second.second; // second.second is the bool user_mode (true == operator)
}

void	Channel::setOperator(const int &fd, bool isOp)
{
	channel::t_users::iterator it = this->_users.find(fd);
	if (it != this->_users.end())
		it->second.second = isOp;
}

void	Channel::handleChannelMode(std::vector<std::string> &tokens, User &user)
{
	if (tokens.size() < 3)
		return ;

	//Ver se o user esta no channel
	if (!hasUser(user.getFd()))
	{
		sendNotInChannel(user);
		return ;
	}
	else if (!isOperator(user.getFd())) //Checkar se o user e operator do channel para poder fazer o mode
	{
		std::string	msg = ":ft_irc 482 " + user.getNickname() + " " + _name + " :You're not channel operator\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
		return ;
	}

	//Verifica os chars do mode token
	std::string	mode = tokens[2];
	if (mode.at(0) != '+' && mode.at(0) != '-')
	{
		std::string	msg = ":ft_irc 472 " + user.getNickname() + " " + mode.at(0) + " :is unkown mode char to me for for " + _name + "\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
		return ;
	}
	else if (mode.at(1) != 'i' && mode.at(1) != 't' &&
			 mode.at(1) != 'k' && mode.at(1) != 'l' &&
			 mode.at(1) != 'o')
	{
		std::string	msg = ":ft_irc 472 " + user.getNickname() + " " + mode.at(1) + " :is unkown mode char to me for " + _name + "\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
		return ;
	}
	
	bool	add = (mode.at(0) == '+');
	//Se o primeiro for um mais, e para dar add, se for para tirar fica falso,
	//Depois facilita para mudanca no vetor.
	if (mode.at(1) == 'i')
	{
		this->_modes[channel::Invite] = add;
		if (add)
			sendModeChange("+i", "", user);
		else
			sendModeChange("-i", "", user);
	}
	else if (mode.at(1) == 't')
	{
		this->_modes[channel::Topic] = add;
		if (add)
			sendModeChange("+t", "", user);
		else
			sendModeChange("-t", "", user);
	}
	else if (mode.at(1) == 'k')
	{
		handleModeK(tokens, user, add);
	}
	else if (mode.at(1) == 'l')
	{
		handleModeL(tokens, user, add);
	}
	else if (mode.at(1) == 'o')
	{
		handleModeO(tokens, user, add);
	}
}

void	Channel::sendModeChange(const std::string &mode, const std::string &params, User &user)
{
	std::string	msg = ":" + user.getNickname() + "!" + user.getUsername() +
						"@localhost MODE " + _name + " " + mode;
	if (!params.empty())
		msg += " " + params;
	msg += "\r\n";

	// Send MODE change message to all members of the channel
	for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		User *member = it->second.first;
		if (member)
		{
			//send(member->getFd(), msg.c_str(), msg.size(), 0);
			member->appendToBuffer(msg);
		}
	}
}

void	Channel::messageChannel(User &user, const std::vector<std::string> &tokens)
{
	if (!hasUser(user.getFd()))
		sendNotInChannel(user);
	else
	{
		std::string	msg = ":" + user.getNickname() + "!" + user.getUsername() + 
						  "@localhost PRIVMSG " + _name + " :" + tokens[2] + "\r\n";
						  
		for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
		{
			User *member = it->second.first;
			if (member)
				if (member->getFd() != user.getFd())
					member->appendToBuffer(msg);	
				//send(member->getFd(), msg.c_str(), msg.size(), 0);
		}
	}
}

void	Channel::handleTopic(const std::vector<std::string> &tokens, User &user)
{
	const channel::t_users &members = getUsers();
	if (members.find(user.getFd()) == members.end())
	{
		sendNotInChannel(user);
		return ;
	}
	if (tokens.size() == 2)
	{
		sendTopic(&user, &user);
		return ;
	}

	//User wants to set a new topic
	if (this->_modes[channel::Topic] && !isOperator(user.getFd()))
	{
		std::string	msg = ":ft_irc 482 " + user.getNickname() + " " + _name + " :You're not channel operator\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
		return ;
	}
	else
	{
		_topic = tokens[2];
		//Notify all users in the channel about the new topic
		for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
		{
			User *member = it->second.first;
			if (member)
				sendTopic(&user, member);
				
		}
	}
}

void	Channel::inviteUser(User &inviter, User &invitee)
{
	if (!hasUser(inviter.getFd()))
	{
		sendNotInChannel(inviter);
		return ;
	}
	else if (!isOperator(inviter.getFd()))
	{
		std::string	msg = ":ft_irc 482 " + inviter.getNickname() + " " + _name + " :You're not channel operator\r\n";
		//send(inviter.getFd(), msg.c_str(), msg.size(), 0);
		inviter.appendToBuffer(msg);
		return ;
	}
	else if (hasUser(invitee.getFd()))
	{
		std::string	msg = ":ft_irc 443 " + inviter.getNickname() + " " + invitee.getNickname() + " " + _name + " :is already on channel\r\n";
		//send(inviter.getFd(), msg.c_str(), msg.size(), 0);
		inviter.appendToBuffer(msg);
		return ;
	}
	else 
	{
		_invitedUsers.push_back(invitee.getFd());
		std::string	msg = ":" + inviter.getNickname() + "!" + inviter.getUsername() +
							"@localhost INVITE " + invitee.getNickname() + " " + _name + "\r\n";
		//send(invitee.getFd(), msg.c_str(), msg.size(), 0);
		invitee.appendToBuffer(msg);
		msg = ":ft_irc 341 " + inviter.getNickname() + " " + invitee.getNickname() + " " + _name + "\r\n";
		//send(inviter.getFd(), msg.c_str(), msg.size(), 0);
		inviter.appendToBuffer(msg);
	}
}

void	Channel::handleKick(const std::vector<std::string> &tokens, User &user)
{
	if (!hasUser(user.getFd()))
	{
		sendNotInChannel(user);
		return ;
	}
	else if (!isOperator(user.getFd()))
	{
		std::string	msg = ":ft_irc 482 " + user.getNickname() + " " + _name + " :You're not channel operator\r\n";
		//send(user.getFd(), msg.c_str(), msg.size(), 0);
		user.appendToBuffer(msg);
		return ;
	}
	else 
	{
		int targetFd = getFdByNickname(tokens[2]);
		if (targetFd == -1 || !hasUser(targetFd))
		{
			std::string	msg = ":ft_irc 441 " + user.getNickname() + " " + tokens[2] + " " + _name + " :They aren't on that channel\r\n";
			//send(user.getFd(), msg.c_str(), msg.size(), 0);
			user.appendToBuffer(msg);
			return ;
		}
		else
		{
			// Get the target user object before removing
			User *targetUser = _users[targetFd].first;
			
			std::string msg = ":" + user.getNickname() + "!" + user.getUsername() +
								"@localhost KICK " + _name + " " + tokens[2];
			if (tokens.size() >= 4)
				msg += " :" + tokens[3];
			msg += "\r\n";
			// Notify all users in the channel about the kick
			for (channel::t_users::const_iterator it = _users.begin(); it != _users.end(); ++it)
			{
				User *member = it->second.first;
				if (member)
					member->appendToBuffer(msg);	
				//send(member->getFd(), msg.c_str(), msg.size(), 0);
			}
			// Remove the user from the channel
			removeUser(targetFd);
			// Remove the channel from the user's channel list
			if (targetUser)
				targetUser->removeChannel(_name);
			//Find in the invited list and remove if present
			std::vector<int>::iterator it = std::find(_invitedUsers.begin(), _invitedUsers.end(), targetFd);
			if (it != _invitedUsers.end())
				_invitedUsers.erase(it);
		}
	}
}
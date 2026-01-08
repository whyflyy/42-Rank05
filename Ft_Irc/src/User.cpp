/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:05:28 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/30 12:47:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "UserList.hpp"

User::User(const int &fd, const int &type): _fd(fd), _type(type),
_state(user::awaiting_pass), _server(NULL), _f_read(NULL), _f_write(NULL), _isRegistered(false), _capLS(false), _pass(false), _notifiedQuitFds()
{}

User::~User(void)
{}

/* ************************************************************************** */

void	User::setState(const int &state)
{
	this->_state = state;
}

void	User::setNickname(const std::string &nickname)
{
	this->_nickname = nickname;
}

void	User::setUsername(const std::string &username)
{
	this->_username = username;
}

bool	User::addChannel(Channel *channel, const bool &user_mode)
{
	user::t_channel	ch;

	if (this->_channels.find(channel->getName()) != this->_channels.end())
		return (false);
	ch.first = channel;
	ch.second = user_mode;
	this->_channels.insert(std::make_pair(channel->getName(), ch));
	return (true);
}

void	User::removeChannel(const std::string &channel)
{
	user::t_channels::iterator	it;

	it = this->_channels.find(channel);
	if (it != this->_channels.end())
		this->_channels.erase(it);
}

void	User::setServer(IrcServer *server)
{
	if (server)
		this->_server = server;
}

void	User::setReadf(user::t_iofunc f)
{
	this->_f_read = f;	
}

void	User::setWritef(user::t_iofunc f)
{
	this->_f_write = f;
}

void	User::callReadf(void)
{
	if (this->_f_read && this->_server)
		this->_f_read(this->_server, *this);
}

void	User::callWritef(void)
{
	if (this->_f_write && this->_server)
		this->_f_write(this->_server, *this);
}

int		User::getFd(void) const
{
	return (this->_fd);
}

int		User::getType(void) const
{
	return (this->_type);
}

int		User::getState(void) const
{
	return (this->_state);
}

std::string			User::getNickname(void) const
{
	return (this->_nickname);
}

std::string			User::getUsername(void) const
{
	return (this->_username);
}
user::t_channels	&User::getChannels(void)
{
	return (this->_channels);
}

IrcServer			*User::getServer(void) const
{
	return (this->_server);
}

char				*User::prepareBufferRecv(void)
{
	size_t	previous_size;
	
	previous_size = this->_read_buffer.size();
	if (previous_size + user::BufferSize > user::BufferMaxSize)
	{
		this->_read_buffer.clear();
		return (NULL);
	}
	this->_read_buffer.resize(previous_size + user::BufferSize);
	return (&this->_read_buffer[previous_size]);
}

void				User::shrinkBufferAfterRecv(ssize_t &bytes_read)
{
	size_t	new_size;
	
	new_size = this->_read_buffer.size() - user::BufferSize + bytes_read;
	this->_read_buffer.resize(new_size);
}

bool				User::getBufferMessage(std::string &msg)
{
	const std::string		irc_token = "\r\n";
	const std::string		short_token = "\n";	
	std::string::size_type	pos;
	
	pos = this->_read_buffer.find(irc_token);
	if (pos != std::string::npos)
	{
		msg = this->_read_buffer.substr(0, pos) + irc_token;
		this->_read_buffer.erase(0, pos + irc_token.length());
		if (msg.length() > user::msg_size) //Check message size limit
		{
			msg = ":ft_irc 417 " + this->_nickname + " :Message too long\r\n";
			appendToBuffer(msg);
			//send(this->_fd, msg.c_str(), msg.size(), 0);
			return false;
		}
		return (true);		
	}
	pos = this->_read_buffer.find(short_token);
	if (pos != std::string::npos)
	{
		msg = this->_read_buffer.substr(0, pos) + irc_token;
		this->_read_buffer.erase(0, pos + short_token.length());
		if (msg.length() > user::msg_size) //Check message size limit
		{
			msg = ":ft_irc 417 " + this->_nickname + " :Message too long\r\n";
			appendToBuffer(msg);
			//send(this->_fd, msg.c_str(), msg.size(), 0);
			return false;
		}
		return (true);		
	}
	return (false);	
}

std::string			&User::getReadBuffer(void)
{
	return (this->_read_buffer);
}

bool				User::checkWriteBuffer(void) const
{
	return (!this->_write_buffer.empty());
}

void				User::appendToBuffer(const std::string &msg)
{ 
	this->_write_buffer += msg;
}

char				*User::prepareBufferSend(void)
{
	return (&this->_write_buffer[0]);
}

size_t				User::writeBufferSize(void)
{
	return (this->_write_buffer.size());
}

void				User::removeSentBytes(const ssize_t &bytes_sent)
{
	if (bytes_sent > 0)
		this->_write_buffer.erase(0, bytes_sent);
}

void	User::printUser(void) const
{
	std::cout <<
	format::bold << color::cyan << "[ " <<
	format::reset << this->_fd << ", " <<
	this->_type << ", " <<
	this->_nickname << ", " <<
	this->_username <<
	format::bold << color::cyan << " ]" <<
	format::reset << std::endl;
}

//-------------------------------------------------------------------------- JOAO - AUTH METHODS ------------------------------------------------------------------

bool	User::authCapLS(const std::vector<std::string> &tokens)
{
	if (tokens.size() == 3 && ft_strtoupper(tokens[0]) == "CAP" &&
		ft_strtoupper(tokens[1]) == "LS" && tokens[2] == "302")
	{
		this->_capLS = true;
		std::string msg = ":server CAP * LS :\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return (true);
	}
	else
	{
		std::string msg = ":ft_irc 461 ";
		if (_nickname.empty())
			msg += "* ";
		else
			msg += this->_nickname;
		msg += " CAP :Not enough parameters\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return (false); // Unsupported CAP subcommand
	}
}

bool	User::authPass(const std::vector<std::string> &tokens, const std::string &password)
{
	if (tokens.size() != 2 || ft_strtoupper(tokens[0]) != "PASS")
	{
		std::string msg = "ERROR :Invalid PASS command format\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return false; // Invalid PASS command
	}

	if (tokens[1] == password)
	{
		_pass = true;
		return true; // Password accepted
	}
	else
	{
		std::string msg = "ERROR :Bad password\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return false; // Incorrect password
	}
}

bool	User::authNick(const std::vector<std::string> &tokens, UserList &userList)
{
	if (tokens.size() < 2 || ft_strtoupper(tokens[0]) != "NICK")
	{
		std::string msg = ":ft_irc 461 ";
		if (_nickname.empty())
			msg += "* ";
		else
			msg += this->_nickname;
		msg += " NICK :Not enough parameters\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return true; // not fatal error, just need to resend NICK
	}
	if (!_pass)
	{
		std::string msg = ":server 464 * :Password required\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return false; // Must send PASS first
	}
	if (tokens[1].empty())
	{
		std::string msg = ":server 431 * :No nickname given\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return false; // fatal: invalid nickname

	}

	const std::string &new_nick = tokens[1];
	//Check for invalid characters
	if (new_nick.length() > 9 || new_nick.at(0) == '#' || new_nick.at(0) == '&')
	{
		std::string msg = ":server 432 * " + new_nick + " :Erroneous nickname\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return false; // fatal: invalid nickname
	}

	// Check if nickname is already in use
	if (userList.isNicknameInUse(new_nick))
	{
		std::string msg = ":server 433 * " + new_nick + " :Nickname is already in use\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return true; // Nickname already taken - not fatal, can try another
	}

	_nickname = new_nick;
	if (!_nickname.empty() && !_username.empty())
	{
		_isRegistered = true;
		sendWelcomeMessage();
	}
	return true;
}

bool	User::authUser(const std::vector<std::string> &tokens)
{
	if (tokens.size() < 5)
	{
		std::string msg = ":ft_irc 461 ";
		if (_nickname.empty())
			msg += "*";
		else
			msg += this->_nickname;
		msg += " USER :Not enough parameters\r\n";
		appendToBuffer(msg); //TODO: TROCAR TODOS PARA APPENDTOBUFFER?
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		return true; // not fatal error, just need to resend USER
	}
	if (!_pass)
	{
		std::string msg = ":server 464 * :Password required\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return false; // Must send PASS first
	}

	_username = tokens[1];

	if (!_nickname.empty() && !_username.empty())
	{
		_isRegistered = true;
		sendWelcomeMessage();
	}
	return true;
}

void	User::sendWelcomeMessage(void)
{
	//RPL_WELCOME 001
	std::string welcome = ":server 001 " + _nickname + " :Welcome to the IRC Server " + _nickname + "!" + _username + "@host\r\n";
	//send(this->_fd, welcome.c_str(), welcome.size(), 0);
	appendToBuffer(welcome);

	//RPL_YOURHOST 002
	std::string yourhost = ":server 002 " + _nickname + " :Your host is server, running version 1.0\r\n";
	//send(this->_fd, yourhost.c_str(), yourhost.size(), 0);
	appendToBuffer(yourhost);

	//RPL_CREATED 003
	std::string created = ":server 003 " + _nickname + " :This server was created today\r\n";
	//send(this->_fd, created.c_str(), created.size(), 0);
	appendToBuffer(created);

	//RPL_MYINFO 004
	std::string myinfo = ":server 004 " + _nickname + " server 1.0 o o\r\n";
	//send(this->_fd, myinfo.c_str(), myinfo.size(), 0);
	appendToBuffer(myinfo);
}

int		User::authenticate(const std::string &command, const std::vector<std::string> &tokens, const std::string &password, UserList &userList)
{
	if (this->_isRegistered)
		return (0); // Already registered

	//Step 1: Handle CAP LS (optional but expected by modern clients)
	if (!_capLS)
	{
		if (command == "CAP")
			return authCapLS(tokens) ? 0 : 1;
	}
	
	//Step 2: Handle PASS command
	if (!_pass)
	{
		if (command == "PASS")
			return authPass(tokens, password) ? 0 : 1;
		else
		{
			std::string msg = ":ft_irc 464 * :Password required\r\n";
			//send(this->_fd, msg.c_str(), msg.size(), 0);
			appendToBuffer(msg);
			return 1; // Must send PASS first
		}
	}

	//Step 3: Handle NICK and USER commands (can be in any order)
	if (command == "NICK")
		return authNick(tokens, userList) ? 0 : 1;
	else if (command == "USER")
		return authUser(tokens) ? 0 : 1; //fatal on any user error
	else if (command == "PASS")
	{
		//Password already provided
		std::string msg = ":ft_irc 901 ";
		if (_nickname.empty())
			msg += "*";
		else
			msg += this->_nickname;
		msg += " :Password already set\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return 0; // Ignore redundant PASS
	}
	else if (command == "CAP")
	{
		//CAP already negotiated
		std::string msg = ":ft_irc 902 ";
		if (_nickname.empty())
			msg += "*";
		else
			msg += this->_nickname;
		msg += " :CAP already set\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return 0; // Ignore redundant CAP
	}
	else
	{
		std::string msg = ":ft_irc 421 ";
		if (_nickname.empty())
			msg += "*";
		else
			msg += this->_nickname;
		msg += " " + command + " :Unknown command\r\n";
		//send(this->_fd, msg.c_str(), msg.size(), 0);
		appendToBuffer(msg);
		return 0; //FATAL: Unknown command before registration //TODO: DEVE SER FATAL OU NAO?
	}
}

void	User::sendMessage(const std::string &message, const std::string &from_nick, const std::string &from_user, const std::string &recipient, User &to_user)
{
	std::string msg = ":" + from_nick + "!" + from_user + "@localhost PRIVMSG " + recipient + " :" + message + "\r\n";
	//send(to_fd, msg.c_str(), msg.size(), 0);
	to_user.appendToBuffer(msg);
}

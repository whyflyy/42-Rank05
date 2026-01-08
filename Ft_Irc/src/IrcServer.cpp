/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:20:54 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/29 15:35:02 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

const char	*IrcServer::FailCreateLogFile::what(void) const throw()
{
	return ("Failed to create log file!");
}

IrcServer::IrcServer(const int &port, const std::string &password): _port(port),
_password(password), _quitflag(false)
{
	this->_logfile.open(server::log_file, std::fstream::out);
	if (!this->_logfile.good())
		throw FailCreateLogFile();
}

IrcServer::~IrcServer(void)
{
	this->_logfile.close();
}

/* ************************************************************************** */

static std::string	get_time_stamp(void)
{
	std::time_t			now;
    std::tm				*local_time;
	std::ostringstream	time;

	now = std::time(0);
	local_time = std::localtime(&now);
	time	<< 1900 + local_time->tm_year << "-"
    		<< 1 + local_time->tm_mon << "-"
            << local_time->tm_mday << " "
        	<< local_time->tm_hour << ":"
            << local_time->tm_min << ":"
        	<< local_time->tm_sec;
    return (time.str());
}

static void	write_log(IrcServer *server, std::string level, std::string msg)
{
	server->getLogFile() << get_time_stamp() << "	" << level << "	" << msg <<
	std::endl;
}

static void		check_server(IrcServer *server, const int &state)
{
	if (state == server::server_init)
	{
		std::cout <<
		format::bold << color::green << server::server_start <<
		format::reset << std::endl;
		write_log(server, server::info, server::server_start);
	}
	else if (state == server::server_end)
	{
		std::cout <<
		format::bold << color::blue << server::server_quit <<
		format::reset << std::endl;
		write_log(server, server::info, server::server_quit);
	}
}

static User		*check_user(IrcServer *server, User *user)
{
	if (!user)
		write_log(server, server::error, server::new_user_error);
	else
		write_log(server, server::info, server::new_user);
	return (user);
}

static Channel		*check_channel(IrcServer *server, Channel *channel)
{
	if (!channel)
		write_log(server, server::error, server::new_channel_error);
	else
		write_log(server, server::info, server::new_channel);
	return (channel);
}

static bool		check_blocking(IrcServer *server, const bool &flag)
{
	if (!flag)
		write_log(server, server::error, server::set_block_error);
	else
		write_log(server, server::info, server::set_block);
	return (flag);
}

static struct protoent	*check_protocol(IrcServer *server, struct protoent *pe)
{
	if (!pe)
		write_log(server, server::error, server::get_proto_error);
	else
		write_log(server, server::info, server::get_proto);
	return (pe);
}

static int		check_socket(IrcServer *server, const int &socket)
{
	if (socket < 0)
		write_log(server, server::error, server::socket_error);
	else
		write_log(server, server::info, server::socket);
	return (socket);
}

static int		check_socket_options(IrcServer *server, const int &socket_opt)
{
	if (socket_opt < 0)
		write_log(server, server::error, server::socket_opt_error);
	else
		write_log(server, server::info, server::socket_opt);
	return (socket_opt);
}

static int		check_bind(IrcServer *server, const int &bind)
{
	if (bind < 0)
		write_log(server, server::error, server::bind_error);
	else
		write_log(server, server::info, server::bind);
	return (bind);
}

static int		check_listen(IrcServer *server, const int &listen)
{
	if (listen < 0)
		write_log(server, server::error, server::listen_error);
	else
		write_log(server, server::info, server::listen);
	return (listen);
}

static int		check_poll(IrcServer *server, const int &poll)
{
	if (poll < 0)
		write_log(server, server::error, server::poll_error);
	else
		write_log(server, server::info, server::poll);
	return (poll);
}

static std::istream		&check_getline(IrcServer *server, std::istream &str,
const std::string &msg, User &user)
{
	std::ostringstream	output_msg;
	
	if (!str)
		write_log(server, server::error, server::getline_error);
	else
	{
		output_msg << server::getline << ": Read " << msg.length() <<
		" characters from user: " << user.getFd();
		write_log(server, server::info, output_msg.str());
	}
	return (str);
}

static void		check_read(IrcServer *server, ssize_t &bytes_read, User &user)
{
	std::ostringstream	output_msg;

	if (bytes_read < 0)
		write_log(server, server::error, server::read_error);
	else
	{
		output_msg << server::read << ": Read " << bytes_read <<
		" bytes from user: " << user.getFd();
		write_log(server, server::info, output_msg.str());
	}
}

static void		check_write(IrcServer *server, ssize_t &bytes_sent, User &user)
{
	std::ostringstream	output_msg;

	if (bytes_sent < 0)
		write_log(server, server::error, server::write_error);
	else
	{
		output_msg << server::write << ": Wrote " << bytes_sent <<
		" bytes to user: " << user.getFd();
		write_log(server, server::info, output_msg.str());
	}
}

static void		check_connection(IrcServer *server, const int &socket,
const struct sockaddr_in &csin)
{
	std::ostringstream	output_msg;
	
	if (socket < 0)
		write_log(server, server::error, server::connection_error);
	else
	{
		output_msg << server::connection << socket << " from " <<
		inet_ntoa(csin.sin_addr) << ":" << ntohs(csin.sin_port);
		std::cout <<
		format::bold << color::yellow << output_msg.str() <<
		format::reset << std::endl;
		write_log(server, server::info, output_msg.str());
	}
}

static void		check_close(IrcServer *server, const int &close, const int &fd)
{
	std::ostringstream	output_msg;

	if (close < 0)
		write_log(server, server::error, server::close_error);
	else
	{
		output_msg << server::close << fd << " gone away";
		std::cout <<
		format::bold << color::red << output_msg.str() <<
		format::reset << std::endl;
		write_log(server, server::info, output_msg.str());
	}
}

static std::string	check_irc_msg(IrcServer *server, const std::string &msg)
{
	if (msg == "")
		write_log(server, server::error, server::irc_msg_error);
	return (msg);
}

static char	*check_irc_buffer(IrcServer *server, char *buffer)
{
	if (!buffer)
		write_log(server, server::error, server::irc_buffer_error);
	return (buffer);
}

User			*IrcServer::addUser(const int &fd, const int &type)
{
	return (this->_users.addUser(fd,type));
}

void			IrcServer::removeUser(const int &fd)
{
	user::t_channels			channels;
	user::t_channels::iterator	it;
	user::t_channels::iterator	ite;

	channels = this->_users.getUser(fd)->getChannels();
	it = channels.begin();
	ite = channels.end();
	while (it != ite)
	{
		it->second.first->removeUser(fd);
		it++;
	}
	this->_users.removeUser(fd);
}

User			*IrcServer::getUser(const int &fd)
{
	return (this->_users.getUser(fd));
}

Channel		*IrcServer::addUserChannel(const int &fd, const std::string &name)
{
	Channel	*channel;

	channel = this->_channels.getChannel(name);
	if (channel)
	{
		channel->addUser(this->_users.getUser(fd), false, "");
		this->_users.getUser(fd)->addChannel(channel, false);
	}
	else
	{
		channel = check_channel(this, this->_channels.addChannel(name, ""));
		if (!channel)
			return (NULL);
		channel->addUser(this->_users.getUser(fd), true, "");
		this->_users.getUser(fd)->addChannel(channel, true);
	}
	return (channel);
}

void		IrcServer::removeUserChannel(const int &fd, const std::string &name)
{
	this->_users.getUser(fd)->removeChannel(name);
	this->_channels.getChannel(name)->removeUser(fd);
	if (this->_channels.getChannel(name)->getNumberUsers() < 1)
		this->_channels.removeChannel(name);
}

Channel		*IrcServer::getChannel(const std::string &name)
{
	return (this->_channels.getChannel(name));
}

int				IrcServer::channelExists(const std::string &channel)
{
	return (this->_channels.channelExists(channel) ? 1 : 0);
}

struct pollfd	*IrcServer::getPollFd(const int &fd)
{
	return (this->_users.getPollFd(fd));
}

size_t			IrcServer::getPollFDCount(void) const
{
	return (this->_users.getPollFDCount());
}

int				IrcServer::getPort(void) const
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	return (this->_port);
}

bool			IrcServer::getQuitFlag(void) const
{
	return (this->_quitflag);
}

void			IrcServer::setQuitFlag(const bool &flag)
{
	this->_quitflag = flag;
}

std::ofstream	&IrcServer::getLogFile(void)
{
	return (this->_logfile);
}

ChannelList		*IrcServer::getChannels(void)
{
	return (&(this->_channels));
}

static bool		set_non_blocking(const int &fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	return (true);
}

static void		close_connection(IrcServer *server, const int &fd)
{
	check_close(server, close(fd), fd);
	server->removeUser(fd);
}

static void		read_server(IrcServer *server, User &user)
{
	std::string	server_input;

	if (check_getline(server, std::getline(std::cin, server_input),
	server_input, user))
	{
		if (server_input == server::quit_msg)
			server->setQuitFlag(true);
	}
}

static void		read_client(IrcServer *server, User &user)
{
	ssize_t			bytes_read;
	char			*buffer;
	std::string		msg;

	buffer = check_irc_buffer(server, user.prepareBufferRecv());
	if (!buffer)
		return ;
	bytes_read = recv(user.getFd(), buffer, user::BufferSize, 0);
	check_read(server, bytes_read, user);
	if (bytes_read <= 0)
		user.setState(user::closing);
	else
	{
		user.shrinkBufferAfterRecv(bytes_read);
		msg = "";
		while(user.getBufferMessage(msg) && user.getState() != user::closing)
		{
			if (check_irc_msg(server, msg) != "")
				server->parsecommand(server, user, msg);
		}
	}
}

static void		write_client(IrcServer *server, User &user)
{
	ssize_t	bytes_sent;

	static_cast<void>(server);
	bytes_sent = send(user.getFd(), user.prepareBufferSend(),
	user.writeBufferSize(), 0);
	check_write(server, bytes_sent, user);
	if (bytes_sent > 0)
		user.removeSentBytes(bytes_sent);
}

static User		*set_new_user(IrcServer *server, const int &fd, const int &type,
user::t_iofunc f_read, user::t_iofunc f_write)
{
	User	*user;
	
	user = check_user(server, server->addUser(fd, type));
	if (!user)
		return (NULL);
	if (!check_blocking(server, set_non_blocking(fd)))
		return (NULL);
	user->setServer(server);
	user->setReadf(f_read);
	user->setWritef(f_write);
	return (user);
}

static void		accept_connection(IrcServer *server, User &user)
{
	int					new_fd;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	new_fd = accept(user.getFd(), (struct sockaddr*)&csin, &csin_len);
	check_connection(server, new_fd, csin);
	if (new_fd < 0)
		return ;
	if (!set_new_user(server, new_fd, user::FdClient, &read_client,
		&write_client))
		check_close(server, close(new_fd), new_fd);
}

static User		*set_fd_listen(IrcServer *server)
{
	int					s;
	int					opt;
	struct sockaddr_in	sin;
	struct protoent		*pe;

	pe = check_protocol(server, getprotobyname(server::proto_name));
	if (!pe)
		return (NULL);
	s = check_socket(server, socket(PF_INET, SOCK_STREAM, pe->p_proto));
	if (s < 0)
		return (NULL);
	opt = 1;
	if (check_socket_options(server, setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
	&opt, sizeof(opt))) < 0)
		return (NULL);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(server->getPort());
	if (check_bind(server, bind(s, (struct sockaddr*)&sin, sizeof(sin))) < 0)
		return (NULL);
	if (check_listen(server, listen(s, server::listen_backlog)) < 0)
		return (NULL);
	return (set_new_user(server, s, user::FdListen, &accept_connection, NULL));
}

static void		set_poll_masks(IrcServer *server)
{
	size_t	i;

	i = 0;
	while (i < server->getPollFDCount() && !server->getQuitFlag())
	{
		if (server->getUser(server->getPollFd(i)->fd)->checkWriteBuffer())
			server->getPollFd(i)->events |= POLLOUT;
		else
			server->getPollFd(i)->events &= ~POLLOUT;
		i++;
	}
}

static void		check_poll_masks(IrcServer *server)
{
	size_t	i;
	User	*user;

	i = 0;
	while (i < server->getPollFDCount() && !server->getQuitFlag())
	{
		user = server->getUser(server->getPollFd(i)->fd);
		if (server->getPollFd(i)->revents & POLLIN) 
			user->callReadf();
		if (server->getPollFd(i)->revents & POLLOUT)
			user->callWritef();
		if (server->getPollFd(i)->revents & (POLLERR | POLLHUP | POLLNVAL))
			user->setState(user::closing);
		server->getPollFd(i)->revents = 0;
		if (user->getState() == user::closing && !user->checkWriteBuffer())
			close_connection(server, user->getFd());
		else
			i++;
	}
}

void			IrcServer::launch(void)
{
	check_server(this, server::server_init);
	if (!set_new_user(this, STDIN_FILENO, user::FdServer, &read_server, NULL))
		return ;
	if (!set_fd_listen(this))
		return ;
	while (!this->_quitflag)
	{
		set_poll_masks(this);
		if (check_poll(this, poll(this->_users.getPollFd(0),
		static_cast<nfds_t>(this->getPollFDCount()), server::polltimeout)) < 0)
			return ;
		check_poll_masks(this);
	}
	check_server(this, server::server_end);
}

std::string IrcServer::getPassword(void) const
{
	return (this->_password);
}

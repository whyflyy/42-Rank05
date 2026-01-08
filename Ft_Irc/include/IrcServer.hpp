/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:18:25 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/22 15:22:50 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

/// COLOURS ///
#define RESET		"\033[0m"
#define RED			"\033[38;5;160m"
#define GREEN		"\033[38;5;76m"
#define BLUE		"\033[38;5;111m"
#define YELLOW		"\033[38;5;220m"
#define MAGENTA		"\033[38;5;183m"
#define CYAN		"\033[38;5;87m"
#define ORANGE		"\033[38;5;208m"
#define TURQUOISE	"\033[38;5;45m"
#define PEACH		"\033[38;5;217m"

# include <fstream>				// STDIN_FILENO close
# include <sstream>				// ostringstream
# include <netdb.h>				// getprotobyname
# include <arpa/inet.h>			// inet_ntoa...
# include <sys/socket.h>		// socket
# include <poll.h>				// poll
# include <fcntl.h>				// fcntl
# include <exception>			// exception
# include <ctime>				// time

# include "UserList.hpp"
# include "ChannelList.hpp"
# include "Styles.hpp"


namespace server
{
	// Timeout for poll
	const int	polltimeout				= 1000;
	const int	listen_backlog			= 50;

	const char	*const proto_name		= "tcp";
	const char	*const quit_msg			= "quit";
	const char	*const server_name		= "IrcServer";
	const char	*const log_file			= "irc_log";

	// OUTPUT MESSAGES
	const int	server_init				= 0;
	const int	server_end				= 1;
	const char	*const info				= "INFO";
	const char	*const error			= "ERROR";
	const char	*const server_start		= "Server Start";
	const char	*const server_quit		= "Server Quit";
	const char	*const new_user			= "Create new user";
	const char	*const new_user_error	= "Failed to create new user";
	const char	*const new_channel		= "Create new channel";
	const char	*const new_channel_error= "Failed to create new channel";
	const char	*const set_block		= "Set file descriptor to non-blocking";
	const char	*const set_block_error	= "Failed to set file descriptor to non-blocking";
	const char	*const get_proto		= "Retrieve protocol struct";
	const char	*const get_proto_error	= "Failed to retrieve protocol struct";
	const char	*const socket			= "Create socket";
	const char	*const socket_error		= "Failed to create socket";
	const char	*const socket_opt		= "Set socket options";
	const char	*const socket_opt_error	= "Failed to set socket options";
	const char	*const bind				= "Assign address to socket (bind)";
	const char	*const bind_error		= "Failed to assign address to socket (bind)";
	const char	*const listen			= "Set socket to passive (listen)";
	const char	*const listen_error		= "Failed to set socket to passive (listen)";
	const char	*const poll				= "Run poll";
	const char	*const poll_error		= "Error running poll";
	const char	*const getline			= "Reading from server (getline)";
	const char	*const getline_error	= "Error reading from server (getline)";
	const char	*const read				= "Reading from client (recv)";
	const char	*const read_error		= "Error reading from client (recv)";
	const char	*const write			= "Writing to client (send)";
	const char	*const write_error		= "Error writing to client (send)";
	const char	*const connection		= "New connection: New client #";
	const char	*const connection_error	= "Error accepting new connection";
	const char	*const close			= "Close connection: Client #";
	const char	*const close_error		= "Error closing connection";
	const char	*const irc_msg_error	= "Ignoring IRC message (longer than 512 bytes)";
	const char	*const irc_buffer_error	= "Read buffer limit reached - Flush buffer";
}

class IrcServer
{
	private:
		int						_port;
		std::string				_password;
		UserList				_users;
		ChannelList				_channels;
		bool					_quitflag;
		std::ofstream			_logfile;

		IrcServer(void);
		IrcServer(const IrcServer &server);

		IrcServer		&operator = (const IrcServer &server);

		class FailCreateLogFile: public std::exception
		{
			private:
			protected:
			public:
				const char *what(void) const throw();
		};

	protected:

	public:
		IrcServer(const int &port, const std::string &password);
		~IrcServer(void);

		User			*addUser(const int &fd, const int &type);
		void			removeUser(const int &fd);
		User			*getUser(const int &fd);
		Channel			*addUserChannel(const int &fd, const std::string &name);
		void			removeUserChannel(const int &fd, const std::string &name);
		Channel			*getChannel(const std::string &name);
		struct pollfd	*getPollFd(const int &fd);
		size_t			getPollFDCount(void) const;
		int				getPort(void) const;
		bool			getQuitFlag(void) const;
		void			setQuitFlag(const bool &flag);
		std::ofstream	&getLogFile(void);
		ChannelList		*getChannels(void);
		void			launch(void);
		std::string		getPassword(void) const;

		//PARSE.CPP
		void			sendNoParams(User &user, const std::string &command);
		void			sendNoChannel(User &user, const std::string &channel);
		int				userExists(const std::string &nickname);
		int				channelExists(const std::string &channel);

		void			privMsg(const std::vector<std::string> &tokens, User &user);
		
		void			kickUser(IrcServer *server, User &user, const std::string &reason);

		void			handleJoin(const std::vector<std::string> &tokens, User &user);

		void			handlePart(const std::vector<std::string> &tokens, User &user);

		void			handleMode(std::vector<std::string> &tokens, User &user);

		void			handlePing(const std::vector<std::string> &tokens, User &user);
		
		void			handleTopic(const std::vector<std::string> &tokens, User &user);

		void			handleInvite(const std::vector<std::string> &tokens, User &user);

		void			handleKick(const std::vector<std::string> &tokens, User &user);

		void			parsecommand(IrcServer *server, User &user, std::string msg);



};

#endif

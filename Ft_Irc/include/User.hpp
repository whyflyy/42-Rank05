/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:05:10 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/20 17:38:09 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <map>					// map container
# include <vector>				// vector container
# include <unistd.h>			// ssize_t
# include <sys/socket.h>		// recv, send
# include <set>					// set container

# include "Styles.hpp"
# include "Channel.hpp"

const std::string ft_strtoupper(const std::string &other);

class UserList;
class IrcServer;

namespace user
{
	// CONST VARIABLES
	const int	FdServer				= 0;
	const int	FdListen				= 1;
	const int	FdClient				= 2;
	const int	awaiting_pass			= 3;
	const int	awaiting_registration	= 4;
	const int	registered				= 5;
	const int	closing					= 6;
	const int	msg_size				= 512;
	const int	BufferSize				= 4096;
	const int	BufferMaxSize			= 64 * BufferSize;

	typedef std::pair< Channel *, bool >		t_channel;
	typedef std::map< std::string, t_channel >	t_channels;
	typedef	void (*t_iofunc)(IrcServer *, User &);
}

class User
{
	private:
		int					_fd;
		int					_type;
		int					_state;
		std::string			_nickname;
		std::string			_username;
		user::t_channels	_channels;
		std::string			_read_buffer;
		std::string			_write_buffer;
		IrcServer			*_server;
		user::t_iofunc		_f_read;
		user::t_iofunc		_f_write;

		bool				_isRegistered;

		User(void);
		User(const User &user);

		User				&operator = (const User &user);

		bool				_capLS; // Capability for IRCv3.2 LS command
		bool				_pass; // Password accepted
	protected:

	public:
		User(const int &fd, const int &type);
		~User(void);

		std::set<int>	_notifiedQuitFds;

		void				setState(const int &state);
		void				setNickname(const std::string &nickname);
		void				setUsername(const std::string &username);
		bool				addChannel(Channel *channel, const bool &user_mode);
		void				removeChannel(const std::string &channel);
		void				setServer(IrcServer *server);
		void				setReadf(user::t_iofunc f);
		void				setWritef(user::t_iofunc f);
		void				callReadf(void);
		void				callWritef(void);
		int					getFd(void) const;
		int					getType(void) const;
		int					getState(void) const;
		std::string			getNickname(void) const;
		std::string			getUsername(void) const;
		user::t_channels	&getChannels(void);
		IrcServer			*getServer(void) const;

		void				setPass(bool val) { this->_pass = val; }
		void				setCapLS(bool val) { this->_capLS = val; }
		// Read Buffer
		char				*prepareBufferRecv(void);
		void				shrinkBufferAfterRecv(ssize_t &bytes_read);
		bool				getBufferMessage(std::string &msg);
		std::string			&getReadBuffer(void);
		// Write Buffer
		bool				checkWriteBuffer(void) const;
		void				appendToBuffer(const std::string &msg);
		char				*prepareBufferSend(void);
		size_t				writeBufferSize(void);
		void				removeSentBytes(const ssize_t &bytes_sent);
		//!
		void				printUser(void) const;
		// Parse
		bool				getIsRegistered(void) const { return this->_isRegistered; }
		
		bool				authCapLS(const std::vector<std::string> &tokens);
		bool				authPass(const std::vector<std::string> &tokens, const std::string &password);
		bool				authNick(const std::vector<std::string> &tokens, UserList &userList);
		bool				authUser(const std::vector<std::string> &tokens);

		void				sendWelcomeMessage(void);

		int					authenticate(const std::string &command, const std::vector<std::string> &tokens, const std::string &password, UserList &userlist);

		void				sendMessage(const std::string &message, const std::string &from_nick, const std::string &from_user, const std::string &recipient, User &to_user);
};

#endif

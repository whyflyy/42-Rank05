/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:29:18 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/30 12:36:39 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <map>
# include <vector>
# include <sstream>
# include <algorithm>


# include "Styles.hpp"

class User;

namespace channel
{
	// CHANNEL MODES
	enum e_chmodes
	{
		Invite,
		Topic,
		Key,
		Operator,
		Limit
	};

	typedef std::pair< User *, bool >	t_user;
	typedef std::map< int, t_user > 	t_users;
}

class Channel
{
	private:
		std::string			_name;
		std::vector<bool>	_modes;
		std::string			_topic;
		std::string			_password;
		channel::t_users	_users;
		int					_userLimit;
		std::vector<int>	_invitedUsers;

		Channel(void);
		Channel(const Channel &channel);

		Channel				&operator = (const Channel &channel);

	protected:

	public:
		Channel(const std::string &name, const std::string &password);
		~Channel(void);

		void				addPassword(const std::string &password);
		void				addTopic(const std::string &topic);
		std::string			getName(void) const;
		std::string			getTopic(void) const;
		size_t				getNumberUsers(void) const;
		channel::t_users	getUsers(void) const;
		// Check if a user (by fd) is present in the channel
		bool				hasUser(const int &fd) const;
		// Check if a user (by nickname) is present in the channel
		bool				nickIsInChannel(const std::string &nickname) const;
		// Return file descriptor for given nickname, or -1 if not found
		int					getFdByNickname(const std::string &nickname) const;
		bool				getMode(const int &mode) const;
		// Check if a user (by fd) is invited to the channel
		bool				isUserInvited(const int &fd) const;
		bool				addUser(User *user, const bool &user_mode, std::string password);
		void				removeUser(const int &fd);
		void				setMode(const int &mode);
		void				removeMode(const int &mode);
		//!
		void				printChannel(void) const;

		bool				isOperator(const int &fd);
		// Set or unset operator status for a user by fd
		void				setOperator(const int &fd, bool isOp);

		// Send a QUIT message to all channel members except the quitting user
		void				sendQuit(User *user, const std::string &quitMessage) const;

		void				handleQuit(User *user, const std::string &quitMessage) const;

		// Send a PART message to all channel members except the leaving user
		void				sendPart(User *user, const std::string &partMessage) const;

		void				sendNotInChannel(User &user);

		void				sendCantJoin(User *user, char mode_char, const std::string &err_code);
		void				sendJoinMessage(User *user);

		void				sendTopic(User *user, User *member);
		void				sendUserList(User *user, User *member);
		void				sendEndNameList(User *user, User *member);

		void				handleChannelMode(std::vector<std::string> &tokens, User &user);

		void				sendModeChange(const std::string &mode, const std::string &params, User &user);

		void				messageChannel(User &user, const std::vector<std::string> &tokens);

		void				handleModeK(std::vector<std::string> &tokens, User &user, bool add);
		void				handleModeL(std::vector<std::string> &tokens, User &user, bool add);
		void				handleModeO(std::vector<std::string> &tokens, User &user, bool add);

		void				handleTopic(const std::vector<std::string> &tokens, User &user);

		void				inviteUser(User &inviter, User &invitee);

		void				handleKick(const std::vector<std::string> &tokens, User &user);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserList.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:47:56 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/11 10:29:04 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERLIST_HPP
# define USERLIST_HPP

# include <cstdlib>				// C Standard Library (Return codes)
# include <unistd.h>			// close
# include <poll.h>				// poll
# include <map>					// map container
# include <vector>				// vector container
# include <algorithm>			// Container algorithms

# include "User.hpp"

namespace ulist
{
	typedef std::map< int, User * >				t_users;
	typedef	std::vector< struct pollfd >		t_pollfd;
}

class UserList
{
	private:
		ulist::t_users				_user_list;
		ulist::t_pollfd				_pollfd_list;

		UserList(const UserList &ulist);

		UserList					&operator = (const UserList &ulist);

	protected:

	public:
		UserList(void);
		~UserList(void);

		User						*addUser(const int &fd, const int &type);
		void						removeUser(const int &fd);
		User						*getUser(const int &fd);
		struct pollfd				*getPollFd(const int &fd);
		size_t						getUserCount(void) const;
		size_t						getPollFDCount(void) const;
		bool						isNicknameInUse(const std::string &nickname) const;

		void						printList(void) const;
};

#endif

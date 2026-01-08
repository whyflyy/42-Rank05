/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserList.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:48:38 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/19 13:41:23 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserList.hpp"
#include "User.hpp"

UserList::UserList(void)
{}

static void	deleteUser(std::pair < int, User *> pair)
{
	delete (pair.second);
}

UserList::~UserList(void)
{
	if (this->_user_list.size() > 0)
		std::for_each(this->_user_list.begin(), this->_user_list.end(), deleteUser);
}

/* ************************************************************************** */

User		*UserList::addUser(const int &fd, const int &type)
{
	struct pollfd	polluser;
	User			*user;

	user = new User(fd, type);
	if (!user)
		return (NULL);
	this->_user_list.insert(std::make_pair(fd, user));
	polluser.fd = fd;
	polluser.events = POLLIN;
	polluser.revents = 0;
	this->_pollfd_list.push_back(polluser);
	return (this->_user_list[fd]);
}

void		UserList::removeUser(const int &fd)
{
	ulist::t_pollfd::iterator	it;
	ulist::t_pollfd::iterator	ite;

	it = this->_pollfd_list.begin();
	ite = this->_pollfd_list.end();
	while (it != ite)
	{
		if (it->fd == fd)
		{
			this->_pollfd_list.erase(it);
			break;
		}
		it++;
	}
	if (this->_user_list.find(fd) != this->_user_list.end())
	{
		delete (this->_user_list[fd]);
		this->_user_list.erase(fd);
	}
}

User		*UserList::getUser(const int &fd)
{	
	ulist::t_users::iterator	it;

	it = this->_user_list.find(fd);
	if (it != this->_user_list.end())
		return (it->second);
	else
		return (NULL);
}

struct pollfd	*UserList::getPollFd(const int &fd)
{
	return (&this->_pollfd_list[fd]);
}

size_t			UserList::getUserCount(void) const
{
	return (this->_user_list.size());
}

size_t			UserList::getPollFDCount(void) const
{
	return (this->_pollfd_list.size());
}

bool			UserList::isNicknameInUse(const std::string &nickname) const
{
	ulist::t_users::const_iterator	it;
	ulist::t_users::const_iterator	ite;
	std::string	upperNick = ft_strtoupper(nickname);

	it = this->_user_list.begin();
	ite = this->_user_list.end();
	while (it != ite)
	{
		if (ft_strtoupper(it->second->getNickname()) == upperNick)
			return (true);
		it++;
	}
	return (false);
}

static void	printUser(std::pair < int, User *> pair)
{
	pair.second->printUser();
}

void		UserList::printList(void) const
{
	std::cout <<
	format::bold << color::cyan << "Number fds: " <<
	color::yellow << this->_user_list.size() <<
	format::reset << std::endl;
	std::for_each(this->_user_list.begin(), this->_user_list.end(), printUser);
}

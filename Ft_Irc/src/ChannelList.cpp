/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:14:21 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/19 13:40:46 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelList.hpp"

ChannelList::ChannelList(void)
{}

static void	deleteChannel(const std::pair< const std::string, Channel * > &pair)
{
	delete (pair.second);
}

ChannelList::~ChannelList(void)
{
	std::for_each(this->_channel_list.begin(), this->_channel_list.end(), deleteChannel);
}

/* ************************************************************************** */

Channel		*ChannelList::addChannel(const std::string &name, const std::string &password)
{
	Channel	*channel;

	if (this->_channel_list.find(name) != this->_channel_list.end())
		return (NULL); 
	if (password.empty())
		channel = new Channel(name, "");
	else
		channel = new Channel(name, password);
	if (!channel)
		return (NULL);
	this->_channel_list.insert(std::make_pair(channel->getName(), channel));
	return (this->_channel_list[name]);
}

void		ChannelList::removeChannel(const std::string &name)
{
	chlist::t_channels::iterator	it;
	
	it = this->_channel_list.find(name);
	if (it != this->_channel_list.end())
	{
		delete (it->second);
		this->_channel_list.erase(it);
	}
}

Channel		*ChannelList::getChannel(const std::string &name)
{
	if (name.empty() || name.at(0) != '#')
		return NULL;
	
	// Case-insensitive search (skip the # prefix)
	std::string upperName = ft_strtoupper(name.substr(1));
	for (chlist::t_channels::iterator it = this->_channel_list.begin(); it != this->_channel_list.end(); ++it)
	{
		std::string channelName = it->first;
		if (!channelName.empty() && channelName.at(0) == '#')
		{
			if (ft_strtoupper(channelName.substr(1)) == upperName)
				return it->second;
		}
	}
	return NULL;
}

chlist::t_channels	&ChannelList::getChannels (void)
{
	return (this->_channel_list);
}

bool	ChannelList::channelExists(const std::string &name) const
{
	if (name.empty() || name.at(0) != '#')
		return false;
	
	// Case-insensitive search (skip the # prefix)
	std::string upperName = ft_strtoupper(name.substr(1));
	for (chlist::t_channels::const_iterator it = this->_channel_list.begin(); it != this->_channel_list.end(); ++it)
	{
		std::string channelName = it->first;
		if (!channelName.empty() && channelName.at(0) == '#')
		{
			if (ft_strtoupper(channelName.substr(1)) == upperName)
				return true;
		}
	}
	return false;
}

static void	printChannel( const std::pair< const std::string, Channel * > &pair)
{
	pair.second->printChannel();
}

void		ChannelList::printList(void) const
{
	std::cout <<
	format::bold << color::magenta << "Number channels: " <<
	color::yellow << this->_channel_list.size() <<
	format::reset << std::endl;
	std::for_each(this->_channel_list.begin(), this->_channel_list.end(), printChannel);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 01:40:32 by antfonse          #+#    #+#             */
/*   Updated: 2025/12/19 13:42:15 by jcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELLIST_HPP
# define CHANNELLIST_HPP

# include <map>
# include <algorithm>			// Container algorithms

# include "Channel.hpp"

const std::string ft_strtoupper(const std::string &other);

namespace chlist
{
	typedef std::map< std::string, Channel * >	t_channels;
}

class ChannelList
{
	private:
		chlist::t_channels	_channel_list;

		ChannelList(const ChannelList &chlist);

		ChannelList			&operator = (const ChannelList &chlist);

	protected:

	public:
		ChannelList(void);
		~ChannelList(void);

		Channel				*addChannel(const std::string &name, const std::string &password);
		void				removeChannel(const std::string &name);
		Channel				*getChannel(const std::string &name);		bool					channelExists(const std::string &name) const;		chlist::t_channels	&getChannels (void);
		//!
		void				printList(void) const;
};

#endif

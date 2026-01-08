/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Styles.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:00:13 by antfonse          #+#    #+#             */
/*   Updated: 2025/07/29 23:31:39 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STYLES_H
# define STYLES_H

namespace format
{
	// TEXT reset #
	const char	*const reset			= "\033[0m";

	// TEXT FORMATTING #
	const char	*const bold				= "\033[1m";
	const char	*const thin				= "\033[2m";
	const char	*const italic			= "\033[3m";
	const char	*const underline		= "\033[4m";
	const char	*const blinking			= "\033[5m";
	const char	*const inverse			= "\033[7m";
	const char	*const strikethrough	= "\033[9m";
}

namespace color
{
	// TEXT COLOR #
	const char	*const black			= "\033[30m";
	const char	*const red				= "\033[31m";
	const char	*const green			= "\033[32m";
	const char	*const yellow			= "\033[33m";
	const char	*const blue				= "\033[34m";
	const char	*const magenta			= "\033[35m";
	const char	*const cyan				= "\033[36m";
	const char	*const white			= "\033[37m";

	// BACKGROUND COLOR #
	const char	*const b_black			= "\033[40m";
	const char	*const b_red			= "\033[41m";
	const char	*const b_green			= "\033[42m";
	const char	*const b_yellow			= "\033[43m";
	const char	*const b_blue			= "\033[44m";
	const char	*const b_magenta		= "\033[45m";
	const char	*const b_cyan			= "\033[46m";
	const char	*const b_white			= "\033[47m";
}

#endif

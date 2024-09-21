/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atkaewse <atkaewse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:13:11 by atkaewse          #+#    #+#             */
/*   Updated: 2024/09/21 14:20:57 by atkaewse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl[MAX_FD];
	char			*next_line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl[fd].head)
		initial_gnl(&gnl[fd], fd);
	gnl[fd].buff = 0;
	if (!read_next_line(&gnl[fd]))
		return (NULL);
	if (gnl[fd].last->buff == -1 || !gnl[fd].buff)
	{
		free_all(&gnl[fd]);
		return (NULL);
	}
	next_line = duplicate_line(&gnl[fd]);
	return (next_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atkaewse <atkaewse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:13:11 by atkaewse          #+#    #+#             */
/*   Updated: 2024/09/19 15:28:36 by atkaewse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl[MAX_FD];
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!gnl->head || fd != gnl->fd)
		initial_gnl(gnl, fd);
	gnl->buff = 0;
	read_next_line(gnl);
	if (gnl->head->buff == -1 || !gnl->buff)
	{
		gnl->stop = 1;
		free_line(gnl);
		return (NULL);
	}
	next_line = duplicate_line(gnl);
	if (gnl->head)
	{
		if (!gnl->buff)
			free(gnl->head);
	}
	return (next_line);
}

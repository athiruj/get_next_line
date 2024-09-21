/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atkaewse <atkaewse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:13:11 by atkaewse          #+#    #+#             */
/*   Updated: 2024/09/21 14:19:50 by atkaewse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl.head)
		initial_gnl(&gnl, fd);
	gnl.buff = 0;
	if (!read_next_line(&gnl))
		return (NULL);
	if (gnl.last->buff == -1 || !gnl.buff)
	{
		free_all(&gnl);
		return (NULL);
	}
	next_line = duplicate_line(&gnl);
	return (next_line);
}

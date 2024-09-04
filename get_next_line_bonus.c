/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athi <athi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:12:21 by athi              #+#    #+#             */
/*   Updated: 2024/09/04 18:33:23 by athi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	! define static line linker
	! define line for return
	! handle Error fd, BUFFER_SIZE, read
*/

char	*get_next_line(int fd)
{
	static t_static_v	static_v[4096];
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0
		|| (static_v[fd].eof && static_v[fd].stop))
		return (NULL);
	if (!static_v[fd].link)
	{
		static_v[fd].eof = False;
		static_v[fd].offset = (size_t) NULL;
	}
	ft_get_line(&static_v[fd], fd);
	if (!static_v[fd].buffer || static_v[fd].link->buffer == (size_t) -1)
	{
		free(static_v[fd].link);
		static_v[fd].stop = True;
		return (NULL);
	}
	line = (char *)malloc(static_v[fd].buffer + 1);
	if (!line)
		return (NULL);
	ft_line_cpy(line, &static_v[fd]);
	return (line);
}

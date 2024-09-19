/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athi <athi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:12:21 by athi              #+#    #+#             */
/*   Updated: 2024/09/09 13:34:00 by athi             ###   ########.fr       */
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
	static t_static_v	static_v;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (static_v.eof && static_v.stop))
		return (NULL);
	if (!static_v.link)
	{
		static_v.stop = 0;
		static_v.eof = 0;
		static_v.offset = 0;
	}
	ft_get_line(&static_v, fd);
	if (!static_v.buffer || static_v.link->buffer == -1)
	{
		free(static_v.link);
		static_v.stop = 1;
		return (NULL);
	}
	line = (char *)malloc(static_v.buffer + 1);
	if (!line)
		return (NULL);
	ft_line_cpy(line, &static_v);
	line[static_v.buffer] = '\0';
	return (line);
}

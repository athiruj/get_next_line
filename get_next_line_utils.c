/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atkaewse <atkaewse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:13:03 by atkaewse          #+#    #+#             */
/*   Updated: 2024/09/21 14:19:44 by atkaewse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	initial_gnl(t_gnl *gnl, int fd)
{
	gnl->head = NULL;
	gnl->last = NULL;
	gnl->fd = fd;
	gnl->eof = 0;
	gnl->buff = 0;
	gnl->offset = 0;
}

t_bool	read_file(t_gnl *gnl)
{
	if (!gnl->head)
	{
		gnl->head = (t_link *)malloc(sizeof(t_link));
		if (!gnl->head)
			return (False);
		gnl->last = gnl->head;
		gnl->last->buff = 0;
		gnl->last->next = NULL;
	}
	else if (!gnl->eof)
	{
		gnl->last->next = (t_link *)malloc(sizeof(t_link));
		if (!gnl->last->next)
			return (!free_all(gnl));
		gnl->last = gnl->last->next;
		gnl->last->buff = 0;
		gnl->last->next = NULL;
	}
	else
		return (1);
	gnl->last->buff = read(gnl->fd, gnl->last->content, BUFFER_SIZE);
	if (gnl->last->buff <= 0)
		gnl->eof = 1;
	return (True);
}

// read next line return False when read fail
t_bool	read_next_line(t_gnl *gnl)
{
	t_link	*tmp;
	int		i;

	if (!gnl->head)
		if (!read_file(gnl))
			return (False);
	if (gnl->last->buff == -1)
		return (True);
	tmp = gnl->head;
	while (tmp->buff)
	{
		i = (gnl->buff + gnl->offset) % BUFFER_SIZE;
		if (i > tmp->buff - 1)
			return (True);
		gnl->buff++;
		if (tmp->content[i] == '\n')
			return (1);
		if (i == BUFFER_SIZE - 1)
		{
			if (!read_file(gnl))
				return (False);
			tmp = tmp->next;
		}
	}
	return (True);
}

char	*duplicate_line(t_gnl *gnl)
{
	t_link	*tmp;
	char	*next_line;
	int		i;

	next_line = (char *)malloc(sizeof(char) * (gnl->buff + 1));
	if (!next_line)
	{
		free_all(gnl);
		return (NULL);
	}
	i = 0;
	while (i < gnl->buff)
	{
		next_line[i++] = gnl->head->content[gnl->offset++];
		if ((ssize_t)gnl->offset == gnl->head->buff)
		{
			tmp = gnl->head;
			gnl->head = gnl->head->next;
			free(tmp);
			gnl->offset = 0;
		}
	}
	next_line[gnl->buff] = '\0';
	return (next_line);
}

t_bool	free_all(t_gnl *gnl)
{
	t_link	*tmp;

	while (gnl->head)
	{
		tmp = gnl->head->next;
		free(gnl->head);
		gnl->head = tmp;
	}
	initial_gnl(gnl, 0);
	return (True);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atkaewse <atkaewse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:13:03 by atkaewse          #+#    #+#             */
/*   Updated: 2024/09/19 15:22:07 by atkaewse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	initial_gnl(t_gnl *gnl, int fd)
{
	gnl->head = NULL;
	gnl->last = NULL;
	gnl->fd = fd;
	gnl->stop = 0;
	gnl->eof = 0;
	gnl->buff = 0;
	gnl->offset = 0;
}

void	read_file(t_gnl *gnl)
{
	if (!gnl->head)
	{
		gnl->head = malloc(sizeof(t_link));
		if (!gnl->head)
			return ;
		gnl->last = gnl->head;
		gnl->last->buff = 0;
		gnl->last->next = NULL;
	}
	else if (!gnl->eof)
	{
		gnl->last->next = malloc(sizeof(t_link));
		if (!gnl->last->next)
			return ;
		gnl->last = gnl->last->next;
		gnl->last->buff = 0;
		gnl->last->next = NULL;
	}
	else
		return ;
	gnl->last->buff = read(gnl->fd, gnl->last->content, BUFFER_SIZE);
	if (gnl->last->buff <= 0)
		gnl->eof = 1;
}

void	read_next_line(t_gnl *gnl)
{
	t_link	*tmp;
	int		i;

	if (!gnl->head)
		read_file(gnl);
	if (gnl->last->buff == -1)
		return ;
	tmp = gnl->head;
	gnl->buff = 0;
	while (tmp->buff)
	{
		i = (gnl->buff + gnl->offset) % BUFFER_SIZE;
		if (i > tmp->buff - 1)
			return ;
		gnl->buff++;
		if (tmp->content[i] == '\n')
			return ;
		if (i == BUFFER_SIZE - 1)
		{
			read_file(gnl);
			tmp = tmp->next;
		}
	}
}

char	*duplicate_line(t_gnl *gnl)
{
	t_link	*tmp;
	char	*next_line;
	int		i;

	next_line = (char *)malloc(sizeof(char) * (gnl->buff + 1));
	if (!next_line)
		return (NULL);
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

void	free_line(t_gnl *gnl)
{
	t_link	*tmp;

	if (!gnl->head)
		return ;
	while (gnl->head)
	{
		tmp = gnl->head->next;
		free(gnl->head);
		gnl->head = tmp;
	}
	if (gnl->head)
		free(gnl->head);
}

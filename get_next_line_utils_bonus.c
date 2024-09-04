/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athi <athi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:12:53 by athi              #+#    #+#             */
/*   Updated: 2024/09/04 18:08:14 by athi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	read file with a buffer size
		first line link_list is null
			allocate link with a sizeof [t_link]
			set null default
			set last_link as link
		if static_v is not null and file for read is not end
			allocate for a next link with size0f [t_link]
			set the last to the next link
			and set null default for new allocate
		else (at the end or something error)
			stop and return nothing
		read file store at the last_link (first time last_link same head_link)
		check if read at the end set eof is True
*/
void	ft_read_file(t_static_v *s_v, int fd)
{
	if (!s_v->link)
	{
		s_v->link = (t_link *)malloc(sizeof(t_link));
		s_v->link->next = NULL;
		s_v->link->buffer = (size_t) NULL;
		s_v->last_link = s_v->link;
	}
	else if (!s_v->eof)
	{
		s_v->last_link->next = (t_link *)malloc(sizeof(t_link));
		s_v->last_link = s_v->last_link->next;
		s_v->last_link->next = NULL;
		s_v->last_link->buffer = (size_t) NULL;
	}
	else
		return ;
	s_v->last_link->buffer = read(fd, s_v->last_link->context, BUFFER_SIZE);
	if (!s_v->last_link->buffer)
		s_v->eof = True;
}

/* 
	create line link_list
		first if static_link is null 
			read_file with buffer_size store at static_v
		check if read fail be returned
		set tmp_link same as head_link
		loop for check read file is enough for the first line with buffer size
			idx is head_link_buffer plus previous offset mod with BUFFER_SIZE
			check if idx position more then head_buffer size (mean end)
			set line size ++
			check if at the newline should stop
			if read file not enough 
			(not found newline when idx equal BUFFER_SIZE)
				re read again and store at the next link
				re loop with next link
*/
void	ft_get_line(t_static_v *s_v, int fd)
{
	size_t	idx;
	t_link	*tmp_link;

	if (!s_v->link)
		ft_read_file(s_v, fd);
	if (s_v->last_link->buffer == (size_t) -1)
		return ;
	tmp_link = s_v->link;
	s_v->buffer = (size_t) NULL;
	while (tmp_link->buffer)
	{
		idx = (s_v->buffer + s_v->offset) % BUFFER_SIZE;
		if (idx > tmp_link->buffer - 1)
			return ;
		s_v->buffer++;
		if (tmp_link->context[idx] == '\n')
			return ;
		if (idx == BUFFER_SIZE - 1)
		{
			ft_read_file(s_v, fd);
			tmp_link = tmp_link->next;
		}
	}
}

void	ft_line_cpy(char *dst, t_static_v *s_v)
{
	size_t	idx;
	t_link	*tmp;

	idx = 0;
	while (idx < s_v->buffer)
	{
		dst[idx++] = s_v->link->context[s_v->offset++];
		if (s_v->offset == s_v->link->buffer)
		{
			tmp = s_v->link;
			s_v->link = s_v->link->next;
			free(tmp);
			s_v->offset = (size_t) NULL;
		}
	}
	dst[idx] = '\0';
}

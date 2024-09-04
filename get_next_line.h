/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athi <athi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:12:51 by athi              #+#    #+#             */
/*   Updated: 2024/09/04 18:02:14 by athi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
// # include <limits.h>

/* define enum boolean */
typedef enum e_bool
{
	True = 1,
	False = 0
}	t_bool;

/*	define line linker structure */
typedef struct s_link
{
	char			context[BUFFER_SIZE];
	size_t			buffer;
	struct s_link	*next;
}	t_link;

/*	define static variable structure */
typedef struct s_static_v
{
	struct s_link	*link;
	struct s_link	*last_link;
	t_bool			eof;
	t_bool			stop;
	size_t			buffer;
	size_t			offset;
}	t_static_v;

char	*get_next_line(int fd);
void	ft_read_file(t_static_v *s_v, int fd);
void	ft_get_line(t_static_v *s_v, int fd);
void	ft_line_cpy(char *dst, t_static_v *s_v);

#endif
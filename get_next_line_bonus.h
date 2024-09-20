/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atkaewse <atkaewse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:13:19 by atkaewse          #+#    #+#             */
/*   Updated: 2024/09/20 23:52:53 by atkaewse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <unistd.h>

/*	define link list structure */
typedef struct s_link
{
	char			content[BUFFER_SIZE + 1];
	ssize_t			buff;
	struct s_link	*next;
}	t_link;

/*	define static variable structure */
typedef struct s_gnl
{
	struct s_link	*head;
	struct s_link	*last;
	int				fd;
	int				eof;
	ssize_t			buff;
	size_t			offset;
}	t_gnl;

/* Main Function Get_next_line */
char	*get_next_line(int fd);

/* Use for Initialize GetNextLine Structure */
void	initial_gnl(t_gnl *gnl, int fd);

/* Use for read the next line in file store in gnl structure */
int		read_next_line(t_gnl *gnl);

/* Use for read file and allocate line */
int		read_file(t_gnl *gnl);

/* Use for duplicate line get ready for return */
char	*duplicate_line(t_gnl *gnl);

/* Use for free every link list in gnl structure */
int		free_all(t_gnl *gnl);

#endif
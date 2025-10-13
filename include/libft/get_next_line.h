/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:31:56 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/05 15:56:00 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

// GNL

char	*get_next_line(int fd);

// UTILS

int		assemble_line(char **line, char buffer[]);
int		ft_strlen_nl(char const *s1);
char	*ft_strjoin_nl(char const *s1, char const *s2);
void	buffer_clear(char *buffer);
char	*free_line(char **line);

#endif
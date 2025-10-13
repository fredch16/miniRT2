/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:32:00 by fredchar          #+#    #+#             */
/*   Updated: 2025/03/16 19:55:57 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_line(char **line)
{
	if (*line)
		free(*line);
	return (NULL);
}

int	assemble_line(char **line, char buffer[])
{
	char	*join;
	int		i;

	join = ft_strjoin_nl(*line, buffer);
	free(*line);
	if (join == NULL)
		return (-1);
	*line = join;
	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_nl(char const *s1)
{
	int	i;

	if (s1 == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoin_nl(char const *s1, char const *s2)
{
	char	*s3;
	int		j;
	int		i;

	s3 = (char *)malloc(ft_strlen_nl(s1) + ft_strlen_nl(s2) + 1);
	if (!s3)
		return (s3);
	j = 0;
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
		s3[j++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
	{
		s3[j++] = s2[i++];
		if (s2[i - 1] == '\n')
			break ;
	}
	s3[j] = '\0';
	return (s3);
}

void	buffer_clear(char *buffer)
{
	int	buffer_len;
	int	nr_cases;
	int	i;

	buffer_len = 0;
	while (buffer[buffer_len] != '\0')
		buffer_len++;
	nr_cases = ft_strlen_nl(buffer);
	i = 0;
	while (i < buffer_len)
	{
		if (nr_cases + i < buffer_len)
		{
			buffer[i] = buffer[nr_cases + i];
			buffer[nr_cases + i] = '\0';
		}
		else
			buffer[i] = '\0';
		i++;
	}
}

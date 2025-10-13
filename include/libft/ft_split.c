/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:12:50 by fredchar          #+#    #+#             */
/*   Updated: 2025/03/18 19:25:55 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	total_len(const char *s, char c)
{
	size_t	result;

	result = 0;
	while (*s)
	{
		if (*s != c)
		{
			result++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		index;
	size_t		len;

	if (!s)
		return (NULL);
	index = 0;
	result = (char **)malloc(sizeof(char *) * (total_len(s, c) + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			result[index++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	result[index] = 0;
	return (result);
}

// Hello,Bye
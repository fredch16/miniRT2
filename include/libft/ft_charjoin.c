/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:33:55 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/17 02:25:07 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char const *s1, char const s2)
{
	size_t	s1_len;
	char	*result;

	if (!s1)
	{
		result = (char *)malloc(sizeof(char) * 2);
		result[0] = s2;
		result[1] = '\0';
		return (result);
	}
	s1_len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	result[s1_len] = s2;
	result[s1_len + 1] = '\0';
	return (result);
}

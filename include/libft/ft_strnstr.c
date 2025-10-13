/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:00:41 by fredchar          #+#    #+#             */
/*   Updated: 2025/03/17 19:17:09 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*big1;
	const char	*likkle1;
	size_t		remaining;

	if (big == NULL && len == 0)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	while (*big != '\0' && len > 0)
	{
		big1 = big;
		likkle1 = little;
		remaining = len;
		while (*likkle1 != '\0' && *big1 == *likkle1 && remaining > 0)
		{
			big1++;
			likkle1++;
			remaining--;
		}
		if (*likkle1 == '\0')
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

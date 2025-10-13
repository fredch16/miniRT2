/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:31:53 by fredchar          #+#    #+#             */
/*   Updated: 2025/03/10 19:57:31 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		totallen;
	char	*new;

	totallen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	if (totallen == 0)
		return (ft_strdup(""));
	new = (char *)malloc(sizeof (char) * totallen + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, (char *)s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(new, (char *)s2, totallen + 1);
	return (new);
}

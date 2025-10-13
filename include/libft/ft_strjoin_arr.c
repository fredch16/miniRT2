/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:05:40 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/17 02:34:38 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Join an array of strings with spaces in between
 * @param array NULL-terminated array of strings
 * @return New concatenated string or NULL if error
 */
char	*ft_strjoin_arr(char **array)
{
	char	*result;
	char	*temp;
	int		i;

	if (!array || !array[0])
		return (ft_strdup(""));
	result = ft_strdup(array[0]);
	if (!result)
		return (NULL);
	i = 1;
	while (array[i])
	{
		temp = result;
		result = ft_strjoin(temp, " ");
		free(temp);
		if (!result)
			return (NULL);
		temp = result;
		result = ft_strjoin(temp, array[i]);
		free(temp);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

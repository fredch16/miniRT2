/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:17:36 by fredchar          #+#    #+#             */
/*   Updated: 2025/03/13 15:33:33 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	fillit(int nb, char *out, int *i)
{
	if (nb < 0)
	{
		out[*i] = '-';
		*i = *i + 1;
		nb = -nb;
	}
	if (nb > 9)
	{
		fillit(nb / 10, out, i);
	}
	out[*i] = (nb % 10) + '0';
	*i = *i + 1;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*out;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	len = get_num_len(n);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	fillit(n, out, &i);
	out[i] = '\0';
	return (out);
}

// 0123 >> 1234
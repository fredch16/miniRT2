/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:06:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/07 13:17:35 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static void	skip_ws_and_sign(char **s, double *sign)
{
	if (!s || !*s)
		return ;
	while (((**s >= 9 && **s <= 13) || (**s == 32)) && **s)
		(*s)++;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*sign = -1.0;
		(*s)++;
	}
}

static double	parse_fraction_part(char **s)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (!s || !*s)
		return (0.0);
	if (**s != '.')
		return (0.0);
	(*s)++;
	while (**s >= '0' && **s <= '9')
	{
		fraction = fraction * 10.0 + (**s - '0');
		divisor *= 10.0;
		(*s)++;
	}
	return (fraction / divisor);
}

double	ft_atod(char *str)
{
	double	nb;
	double	sign;

	nb = 0.0;
	sign = 1.0;
	skip_ws_and_sign(&str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10.0 + (*str - '0');
		str++;
	}
	nb += parse_fraction_part(&str);
	return (nb * sign);
}

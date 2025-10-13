/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:24:11 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/24 17:34:09 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	print_nbr_base(int nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr == -2147483648)
	{
		count += print_char('-');
		count += print_nbr_base(-(nbr / ft_strlen(base)), base);
		count += print_nbr_base(-(nbr % ft_strlen(base)), base);
		return (count);
	}
	else if (nbr < 0)
	{
		count += print_char('-');
		nbr = -nbr;
	}
	if (nbr >= (int)ft_strlen(base))
	{
		count += print_nbr_base(nbr / ft_strlen(base), base);
		count += print_nbr_base(nbr % ft_strlen(base), base);
	}
	else
		count += print_char(base[nbr]);
	return (count);
}

int	print_nbr_base_u(unsigned int nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr >= (unsigned int)ft_strlen(base))
	{
		count += print_nbr_base(nbr / ft_strlen(base), base);
		count += print_nbr_base(nbr % ft_strlen(base), base);
	}
	else
		count += print_char(base[nbr]);
	return (count);
}

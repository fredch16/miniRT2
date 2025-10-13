/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:53:07 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/22 15:38:44 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(void *ptr)
{
	unsigned long	addr;
	char			hex[17];
	char			*base;
	int				i;
	int				count;

	if (!ptr)
		return (print_str("0x0"));
	addr = (unsigned long)ptr;
	base = "0123456789abcdef";
	i = 16;
	hex[i] = '\0';
	while (i > 0)
	{
		hex[--i] = base[addr % 16];
		addr /= 16;
	}
	count = print_str("0x");
	while (hex[i] == '0')
		i++;
	count += print_str(&hex[i]);
	return (count);
}

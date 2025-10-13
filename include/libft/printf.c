/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:24:55 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/22 15:38:54 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	post_percent(char c, va_list ap)
{
	if (c == 'c')
		return (print_char(va_arg(ap, int)));
	else if (c == 's')
		return (print_str(va_arg(ap, char *)));
	else if (c == 'd' || c == 'i')
		return (print_nbr_base(va_arg(ap, int), "0123456789"));
	else if (c == 'u')
		return (print_nbr_base_u(va_arg(ap, unsigned int), "0123456789"));
	else if (c == 'x')
		return (print_nbr_base_u(va_arg(ap, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (print_nbr_base_u(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	else if (c == 'p')
		return (print_pointer(va_arg(ap, void *)));
	else if (c == '%')
		return (print_char('%'));
	return (0);
}

int	ft_printf(const char *text, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, text);
	while (*text)
	{
		if (*text == '%')
		{
			count += post_percent(*(text + 1), ap);
			text += 2;
		}
		else
			count += print_char(*text++);
	}
	va_end(ap);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:42:13 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/07 16:35:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minimath.h"

t_colour atocol(char *str)
{
	t_colour	col;
	double		mul;

	mul = 0.00392156863;
	col.red = mul * ft_atoi(str);
	while (*str != ',')
		str++;
	col.green = mul * ft_atoi(++str);
	while (*str != ',')
		str++;
	col.blue = mul * ft_atoi(++str);
	return (col);
}

char	*skip_spaces(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char	*move_to_space(char *str)
{
	while (*str && *str != ' ')
		str++;
	return (str);
}
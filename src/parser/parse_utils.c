/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:42:13 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 17:32:25 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minimath.h"

t_colour atocol(char *str)
{
	t_colour	col;
	double		mul;

	str = skip_spaces(str);
	if (!(*str))
		return (default_light());
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

t_vec	ato3dcrds(char *str)
{
	t_vec	res;

	res.x = ft_atod(str);
	while (*str != ',')
		str++;
	res.y = ft_atod(++str);
	while (*str != ',')
		str++;
	res.z = ft_atod(++str);
	res.w = 0;
	return (res);
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

int	allowed_chars(char *str)
{
	while (*str)
	{
		if (!(ft_isdigit(*str) || *str == '.' || *str == ',' || *str == '-' || ft_isspace(*str)))
			return (0);
		str++;
	}
	return (1);
}

char *move_next(char *str)
{
	str = skip_spaces(str);
	str = move_to_space(str);
	str = skip_spaces(str);
	return (str);
}

char *move_skip(char *str)
{
	str = move_to_space(str);
	str = skip_spaces(str);
	return (str);
}

int	parse_error(t_world *w, int error_code, char *err_msg)
{
	printf("Error: %s\n", err_msg);
	w->parser.error_flag++;
	return (error_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by swied            #+#    #+#             */
/*   Updated: 2025/12/15 15:30:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/libft/libft.h"
#include <stdlib.h>

void	parser_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
}

int	skip_whitespace(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
	return (0);
}

/* Parse a vector in format "x,y,z" */
int	parse_vector(char *str, t_vec *vec)
{
	char	**parts;
	int		count;

	parts = ft_split(str, ',');
	if (!parts)
		return (-1);
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_free_array(parts);
		return (-1);
	}
	vec->x = ft_atod(parts[0]);
	vec->y = ft_atod(parts[1]);
	vec->z = ft_atod(parts[2]);
	vec->w = 0.0;
	ft_free_array(parts);
	return (0);
}

/* Parse RGB colour in format "R,G,B" where each is 0-255 */
int	parse_colour(char *str, t_colour *colour)
{
	char	**parts;
	int		count;
	int		r;
	int		g;
	int		b;

	parts = ft_split(str, ',');
	if (!parts)
		return (-1);
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_free_array(parts);
		return (-1);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	ft_free_array(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	colour->red = r / 255.0;
	colour->green = g / 255.0;
	colour->blue = b / 255.0;
	return (0);
}

/* Parse a double value from string */
int	parse_double(char *str, double *value)
{
	if (!str || !*str)
		return (-1);
	*value = ft_atod(str);
	return (0);
}

/* Split string by whitespace and commas for easier parsing */
char	**ft_split_whitespace(char *str)
{
	int		i;
	int		count;
	char	**result;
	char	*start;
	int		len;

	if (!str)
		return (NULL);
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
		{
			count++;
			while (str[i] && !ft_isspace(str[i]))
				i++;
		}
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
		{
			start = &str[i];
			len = 0;
			while (str[i] && !ft_isspace(str[i]))
			{
				len++;
				i++;
			}
			result[count] = ft_substr(start, 0, len);
			if (!result[count])
			{
				ft_free_array(result);
				return (NULL);
			}
			count++;
		}
	}
	result[count] = NULL;
	return (result);
}

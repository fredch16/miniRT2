/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_line_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:32:58 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/06 13:32:40 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	verify_ambient(t_parse_node *n)
{
	char	*p;
	char	*trim_end;
	char	**cols;
	int	i;
	long	val;
	double	ratio;
	char	*endptr;

	if (!n || !n->content)
		return (-1);

	/* move past identifier 'A' */
	p = n->content;
	if (*p != 'A')
		return (-1);
	p++;

	/* skip whitespace before ratio */
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	if (!*p)
		return (-1);

	ratio = strtod(p, &endptr);
	if (endptr == p)
		return (-1);
	if (ratio < 0.0 || ratio > 1.0)
		return (-1);

	/* move to start of colour token */
	p = endptr;
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	if (!*p)
		return (-1);

	/* trim trailing whitespace from the colour substring */
	trim_end = p + ft_strlen(p) - 1;
	while (trim_end > p && (*trim_end == ' ' || *trim_end == '\t'))
	{
		*trim_end = '\0';
		trim_end--;
	}

	/* split on commas and validate three integer channels 0-255 */
	cols = ft_split(p, ',');
	if (!cols)
		return (-1);

	i = 0;
	while (cols[i])
		i++;
	if (i != 3)
	{
		ft_free_array(cols);
		return (-1);
	}

	for (i = 0; cols[i]; i++)
	{
		/* empty component invalid */
		if (cols[i][0] == '\0')
		{
			ft_free_array(cols);
			return (-1);
		}
		/* ensure all chars are digits */
		int j = 0;
		while (cols[i][j])
		{
			if (!ft_isdigit((int)cols[i][j]))
			{
				ft_free_array(cols);
				return (-1);
			}
			j++;
		}
		val = ft_atoi(cols[i]);
		if (val < 0 || val > 255)
		{
			ft_free_array(cols);
			return (-1);
		}
	}

	ft_free_array(cols);
	return (0);
}

int	verify_light(t_parse_node *n)
{
	(void)n;
	return (0);
}

int	verify_camera(t_parse_node *n)
{
	(void)n;
	return (0);
}

int full_empty(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!(content[i] == ' ' || content[i] == '\t'))
			return (-1);
		i++;
	}
	return (0);
}
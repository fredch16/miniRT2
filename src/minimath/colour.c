/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:12:15 by swied             #+#    #+#             */
/*   Updated: 2025/12/21 20:36:06 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	clamp_colour(double value)
{
	int	result;

	result = (int)(value * 255);
	if (result > 255)
		result = 255;
	if (result < 0)
		result = 0;
	return (result);
}

inline t_colour	colour(double r, double g, double b)
{
	return ((t_colour){r, g, b});
}

t_colour	colour_mul(t_colour c1, t_colour c2)
{
	t_colour	result;

	result.red = c1.red * c2.red;
	result.green = c1.green * c2.green;
	result.blue = c1.blue * c2.blue;
	return (result);
}

t_colour	colour_scm(double scalar, t_colour c)
{
	t_colour	result;

	result.red = scalar * c.red;
	result.green = scalar * c.green;
	result.blue = scalar * c.blue;
	return (result);
}

t_colour	colour_add(t_colour c1, t_colour c2)
{
	t_colour	result;

	result.red = c1.red + c2.red;
	result.green = c1.green + c2.green;
	result.blue = c1.blue + c2.blue;
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:12:15 by swied             #+#    #+#             */
/*   Updated: 2025/11/02 21:16:32 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	clamp_colour(double value)
{
	int	result;

	result = (int)(value * 255);
	if (result > 255)
		result = 255;
	if (result < 0)
		result = 0;
	return (result);
}

uint32_t	colour_to_rgba(t_colour color)
{
	int	red;
	int	green;
	int	blue;

	red = clamp_colour(color.red);
	green = clamp_colour(color.green);
	blue = clamp_colour(color.blue);
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

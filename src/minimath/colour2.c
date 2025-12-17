/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:36:48 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/17 16:36:58 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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
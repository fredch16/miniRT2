/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:52:10 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 14:07:35 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	else
		return (false);
}

bool equal_tuple(t_tuple a, t_tuple b)
{
	if (!equal(a.x, b.x))
		return (false);
	if (!equal(a.y, b.y))
		return (false);
	if (!equal(a.z, b.z))
		return (false);
	if (!equal(a.w, b.w))
		return (false);
	return (true);
	
}

bool equal_matrix(t_matrix4 a, t_matrix4 b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(equal_tuple(a.c[i], b.c[i])))
			return (false);
		i++;
	}
	return (true);
}

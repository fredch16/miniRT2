/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:34:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 18:13:27 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline double	tuple_mag(const t_tuple a)
{
	return ((double){sqrt((a.x * a.x) + (a.y * a.y)
			+ (a.z * a.z) + (a.w * a.w))});
}

inline t_tuple	tuple_norm(const t_tuple a)
{
	double	mag;
	double	inv;

	mag = tuple_mag(a);
	inv = 1.0 / mag;
	return ((t_tuple){a.x * inv, a.y * inv, a.z * inv, a.w * inv});
}

inline double	tuple_dot(const t_tuple a, const t_tuple b)
{
	return ((double){a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w});
}

inline t_tuple	tuple_cro(const t_tuple a, const t_tuple b)
{
	return ((t_tuple){a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x, 0});
}

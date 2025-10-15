/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_ops1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:20:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 17:40:29 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// THE SAME CODE
// inline t_tuple	tuple_sub(t_tuple *a, t_tuple *b)
// {
// 	t_tuple	c;

// 	c.x = a.x - b.x;
// 	c.y = a.y - b.y;
// 	c.z = a.z - b.z;
// 	c.w = a.w - b.w;
// 	return (c);
// }

inline t_tuple	tuple_sub(const t_tuple a, const t_tuple b)
{
	return ((t_tuple){a.x - b.x, a.y - b.y,	a.z - b.z, a.w - b.w});
}

inline t_tuple	tuple_add(const t_tuple a, const t_tuple b)
{
	return ((t_tuple){a.x + b.x, a.y + b.y,	a.z + b.z, a.w + b.w});
}

inline t_tuple	tuple_neg(const t_tuple a)
{
	return ((t_tuple){-a.x, -a.y, -a.z, -a.w});
}

inline t_tuple	tuple_scm(const double k, const t_tuple a)
{
	return ((t_tuple){k * a.x, k * a.y, k * a.z, k * a.w});
}

// USE SCM WHEN POSSIBLE SCD IS SLOWER
inline t_tuple	tuple_scd(const t_tuple a, const double k)
{
	return ((t_tuple){a.x / k, a.y / k, a.z / k, a.w / k});
}
